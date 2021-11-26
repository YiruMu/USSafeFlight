#include <iostream>
#include "Graph.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

// Load data function and find the best paths functions here
void LoadData(vector<Graph>& flights, string path)
{
    fstream file;
    file.open(path, ios::in);
    string line, day, start, end, distance;

    while (getline(file,line))
    {

        stringstream s(line);
        getline(s, day, ',');
        cout<<day<<endl;
        getline(s,start,',');
        cout<<start<<endl;
        getline(s, end,',');
        cout<<end<<endl;
        getline(s,distance,',');
        cout<<distance<<endl;

        for (int i =0; i<30; i++)
        {    string d = to_string(i+1);
            if (day == "1/"+d+"/2021")
            {
                flights[i].insertEdge(start,end,stoi(distance));
            }

        }

    }


}
vector<string> dijkstra(const Graph& graph, string start);
vector<string> bellmanFord(const Graph& graph, string start);

int main() {
    /* create a vector of 31 graphs using load data function
     contains a while loop, it will keep running until the user inputs -1
     command prompt:
        Welcome to US Safe Flight, enter 'No' to terminate the program
        What day of the month do you intent to travel?
        What is your starting location?
        What is your destination?
     output:
        Your recommended flight(s) are shown below
     */
    vector<Graph> flights (31, Graph());
    LoadData(flights,"Data.csv");

    string command = "Yes";
    string day ="";
    string start = "";
    string des = "";
    while(command=="Yes")
    {
        cout<<"Welcome to US Safe Flight! We are here to help you find the best flight(s)"<<endl;
        /*
         * Take in commands and make sure they are valid; If they are valid, we can change the string to
         * match the data in csv, e.g. 'Los Angeles, CA'
         */
        cout<<"Would you like to continue (Yes/No)?"<<endl;
        cin>>command;
        while (command != "Yes" && command != "No")
        {
            cout<<"Invalid input. Try again."<<endl;
            cin>>command;
        }



    }

    return 0;
}
