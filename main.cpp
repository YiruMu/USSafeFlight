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
       // cout<<start<<endl;

        getline(s, temp, ',');
        end = end+temp.substr(1,temp.length());
        getline(s, temp, ',');
        end = end+temp.substr(0,temp.length()-1);
       // cout<<end<<endl;

        getline(s,distance);
        //cout<<distance<<endl;

        for (int i =0; i<30; i++)
        {    string d = to_string(i+1);
            if (day == "1/"+d+"/2021")
            {
                flights[i].insertEdge(start,end,stoi(distance));
            }

        }

        start ="";
        end ="";

       // break;
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
    cout<<"Welcome to US Safe Flight! We are here to help you find the best flight(s)"<<endl;
    cout<<"Loading Data ..."<<endl;
    LoadData(flights,"Data.csv");


    string command = "Yes";
    string day ="";
    string start = "";
    string des = "";
    while(command=="Yes")
    {
        

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
