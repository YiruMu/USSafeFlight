#include <iostream>
#include "Graph.h"
#include <vector>
#include <string>
#include <stack>
using namespace std;
using namespace chrono;


int main() {

    // create a vector that contains 31 graphs/travel information of 31 days of the month
    vector<Graph> flights (31, Graph());
    cout<<"Welcome to US Safe Flight! We are here to help you find the best flight(s)"<<endl;
    cout<<"Loading Data ..."<<endl;
    LoadData(flights,"Data.csv");

    // Store new random data in CSV file
    //StoreData(flights);
    //return 0;
    // Random Speed Testing (uncomment the section when testing is needed; comment out the section when testing is not needed)
   /* int iterations = 1;
    for (int i = 0; i < iterations; i++)
    {
        Testing(flights);
    }
    return 0;
    */

    // Specific Speed Testing
    //"Great Falls MT", "Pierre SD"
    /*specificTesting(flights[1], "King Salmon AK", "Manchester NH");
    return 0;*/

    string command = "Yes";
    string day ="";
    string start = "";
    string des = "";

    while(command=="Yes")
    {
        bool valid = false;
        cout<<"What day of the month would you like to travel (pick a number from 1-31)?"<<endl;
        getline(cin,day);
        bool isValid = checkDay(day);
        while (!isValid) {
            cout << "Invalid input. Please enter a number from 1-31" << endl;
            getline(cin, day);
            isValid = checkDay(day);
        }
        int date = stoi(day)-1;

        cout << "What is your starting location? (e.g. Los Angeles CA)" << endl;
        getline(cin, start);
        isValid = checkLocation(flights[date], start);
        while (!isValid) {
            cout << "Starting location not found. Please try another location." << endl;
            getline(cin, start);
            isValid = checkLocation(flights[date], start);
        }

        cout << "What is your destination? (e.g. Los Angeles CA)" << endl;
        getline(cin, des);
        isValid = checkLocation(flights[date], des);
        while (!isValid) {
            cout << "Destination not found. Please try another location." << endl;
            getline(cin, des);
            isValid = checkLocation(flights[date], des);
        }

        bool reachable = bfsReachable(flights[date], start,des);
        if(!reachable)
        {
            cout<<"Sorry, the destination is not reachable."<<endl;
        }

        if (isValid && reachable) {
            cout<<"Flights recommendation according to Dijkstra Algorithm: "<<endl;
            dijkstra(flights[date], start, des);
            cout<<"Flights recommendation according to Bellman-Ford Algorithm: "<<endl;
            string temp = bellmanFord(flights[date].graph, start, des);

        }

        // Ask users if they want to continue with the program
        cout<<"Would you like to continue (Yes/No)?"<<endl;
        getline(cin,command);
        for (int i = 0; i < command.length(); i++)
        {
            command.at(i) = tolower(command.at(i));
        }
        while (command != "yes" && command != "no")
        {
            cout<<"Invalid input. Try again."<<endl;
            getline(cin,command);
        }

    }

    return 0;
}
