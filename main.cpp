#include <iostream>
#include "Graph.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <stack>
#include <limits.h>
using namespace std;

// Load data function and find the best paths functions here
// for each graph, vertices are city +state, e.g. Los Angeles CA and the weight is the distance
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

//the function returns a map<string,int> that contains the shortest path from the source vertex to all vertices in the directed graph.
void dijkstra(Graph& graph, string start, string end)
{
    map<string,int> output;
    map<string,bool> set;
    map<string,string> p;
    stack<string> results;
    results.push(end);

    auto itr = graph.graph.begin();

    for (; itr!= graph.graph.end(); itr++ )
    {
        output[itr->first]= INT_MAX;
        set[itr->first] = false;
        p[itr->first] = "None";

    }

    output[start] =0;
    for (int i=0; i<output.size()-1; i++)
    {
        int min = INT_MAX;
        string min_index;
        auto itr = output.begin();

        for (; itr!=output.end(); itr++)
        {
            if(set[itr->first] == false && output[itr->first]<=min) {
                min = output[itr->first], min_index = itr->first;
            }
        }

        set[min_index] = true;
        itr = output.begin();
        for (; itr != output.end(); itr++)
        {
            for (int j =0; j<graph.graph[min_index].size();j++)
            {
                if(graph.graph[min_index].at(j).first == itr->first && !set[itr->first]&& output[min_index] != INT_MAX)
                {
                    if (output[min_index] +graph.graph[min_index].at(j).second < output[itr->first])
                    {

                        output[itr->first] = output[min_index] +  graph.graph[min_index].at(j).second;
                        p[itr->first] = min_index;
                    }

                }
            }

        }
    }

    while(results.top()!= start)
    {
        results.push(p[results.top()]);
    }

    while (!results.empty())
    {
        cout<<results.top()<<" ->";
        results.pop();
    }
    cout<<"Arrived!"<<endl;
    
}
//vector<string> bellmanFord(Graph& graph, string start);

int main() {
//<<<<<<< Updated upstream

//=======
//>>>>>>> Stashed changes
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
        bool valid = false;
        cout<<"What day of the month would you like to travel (pick a number from 1-31)?"<<endl;
        getline(cin,day);
        
        //make sure it is a number and between 1-31
        while(!valid)
        {
            for(int i = 0 ; i < day.length(); i++)
            {
            //33 - 64 is special charaters 
            //91-96
            //48-57 digits
            //123-126
                if(isdigit(day[i]))
                {// && day[i] <= 47 || day[i] >= 58 && day[i] <= 64 || day[i] >=91 && day[i]<=96 || day[i] >= 123) {//all invalid inputs
                    valid = true;
                    //break;
                }
                else
                    valid = false;
            }
        int date = 0;
        if(valid)
        {
            date = stoi(day);
            if(date < 1 || date > 31)
            {
                day = "";
                valid = false;
            }
        }
        
        //format dates into 1/1/2021 style
       /* string jan = "1/";
        string year = "/2021";
        */

       /*  if(valid){
            graph = flights[date];
            day = jan + day + year;
        }
        */
        if(!valid)
        {
            cout << "Invalid input. Please enter a number from 1-31" << endl;
            getline(cin,day);
            valid = true;
        }
        }
        

        cout<<"What is your starting location? (e.g. Los Angeles CA)"<<endl;
        getline(cin,start);
        for(int j = 0 ; j < start.length(); j++){
            //33 - 64 is special charaters and digits 
            //91-96
            //123-126
            if(start[j] >= 33 && start[j] <= 64 || start[j] >=91 && start[j]<=96 || start[j] >= 123) {//all invalid inputs
                start = "";
                break;
            }
        }
        //if(graph.graph.find())
       /* auto iter = graph.graph.begin();
        for(; iter != graph.graph.end(); ++iter){
            if(start != iter->first){
                valid = false;
            }
        }
        */
        //make sure the city, state exists by going throuhg the csv file and making sure the city/state is present in it 
        //make sure it is not a number or some shit but I think that can be done with 
        cout<<"What is your destination? (e.g. Los Angeles CA)"<<endl;
        getline(cin, des);
        for(int k = 0 ; k < des.length(); k++){
            //33 - 64 is special charaters 
            //91-96
            //123-126
            if(des[k] >= 33 && des[k] <= 64 || des[k] >=91 && des[k]<=96 || des[k] >= 123) {//all invalid inputs
                des = "";
                break;
            }
        }
      /*  auto iter2 = graph.graph.begin();
        for(; iter2 != graph.graph.end(); ++iter2){
            if(des != iter2->first){
                valid = false;
            }
        }
        */
        //same thing for the destination check against the csv file
        /*if(!graph.isEdge(start, des)){
            valid = false;
        }*/
        // if valid, call find the best flights functions
//<<<<<<< Updated upstream

        // ....... Testing code for dijkstra, delete later ........
        // dijkstra(flights[0], "Los Angeles CA", "Detroit MI");
        // ..........Testing code for dijkstra ........

//=======
        //call two functions
        //which date is being used and then pass in graphs into two functions and takes in graph and starting positon
        //print out the best flights based on the vector given regular for loop reading
        
       /* if(valid){
            dijkstra(graph, start, des);
            //bellmanFord(graph, start);
            //graph.printGraph();
        }
        else{
            cout<< "Invalid input. Try again.";
        }


        */
//>>>>>>> Stashed changes

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
