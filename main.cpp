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
    file.open(path,ios::in | ios::out);
    string line, day, start, end, distance, temp;

    while ( getline(file,line))
    {
        stringstream s(line);
        getline(s,day,',');
        getline(s, temp, ',');
        start = start+temp.substr(1,temp.length());
        getline(s, temp, ',');
        start = start+temp.substr(0,temp.length()-1);
        //cout<<start<<endl;

        getline(s, temp, ',');
        end = end+temp.substr(1,temp.length());
        getline(s, temp, ',');
        end = end+temp.substr(0,temp.length()-1);
        //cout<<end<<endl;

        getline(s,distance);
       // cout<<distance<<endl;

        for (int i =0; i<30; i++)
        {    string d = to_string(i+1);
            if (day == "1/"+d+"/2021")
            {
                flights[i].insertEdge(start,end,stoi(distance));
            }

        }
        start ="";
        end ="";

    }

}

vector<string> dijkstra(Graph& graph, string start)
{

}
vector<string> bellmanFord(const Graph& graph, string start);

int main() {
    cout << "Mason is testing GitHub - delete this" << endl;
    cout<<"Yiru is testing"<<endl;
    cout<<"samy is testing !!"<<endl;
    // create a vector that contains 31 graphs/travel information of 31 days of the month
    vector<Graph> flights (31, Graph());
    cout<<"Welcome to US Safe Flight! We are here to help you find the best flight(s)"<<endl;
    cout<<"Loading Data ..."<<endl;
    LoadData(flights,"Data.csv");


    string command = "Yes";
    string day ="";
    string start = "";
    string des = "";

    while(command=="Yes")
    {
        cout<<"What day of the month would you like to travel (pick a number from 1-31)?"<<endl;
        getline(cin,day);

        cout<<"What is your starting location? (e.g. Los Angeles CA)"<<endl;
        getline(cin,start);
        cout<<"What is your destination? (e.g. Los Angeles CA)"<<endl;
        getline(cin, des);
        /*
         * need to double check if the inputs are valid
         */

        // if valid, call find the best flights functions


        // Ask users if they want to continue with the program
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
