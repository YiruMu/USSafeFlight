#include <string>
#include<vector>
#include <fstream>
#include <sstream>
#include <map>
#include <set>
#include <stack>
#include <limits.h>
#include <queue>
#include <random>
#include <chrono>

using namespace std;
using namespace chrono;

class Graph{
public:
    map<string, vector<pair<string,int>>> graph;
    void insertEdge(string from, string to, int weight);
    bool isEdge(string from, string to);
    int getWeight(string from, string to);
    vector<string> getAdjacent(string vertex);
    void printGraph();
    int getIndegree(string vertex);
    int getOutdegree(string vertex);
    int costliestEdge();

};

void Graph::insertEdge(string from, string to, int weight)
{
    /*
         insertEdge() adds a new edge between the from and to vertex.
    */
    graph[from].push_back(make_pair(to, weight));
    if (graph.find(to) == graph.end())
        graph[to]={};
}

bool Graph::isEdge(string from, string to)
{
    /*
        if there is an edge between the from and to vertex
    */
    if (graph.find(from)!= graph.end())
    {
        for (int i =0; i<graph[from].size();i++)
        {
            if(graph[from].at(i).first==to)
                return true;
        }
    }
    return false;
}

int Graph::getWeight(string from, string to)
{
    int weight =0;
    if (graph.find(from)!= graph.end())
    {
        for (int i =0; i<graph[from].size();i++)
        {
            if(graph[from].at(i).first==to)
                weight = graph[from].at(i).second ;
        }
    }

    return weight ;
}

vector<string> Graph::getAdjacent(string vertex)
{

    vector<string> adjacent;
    if (graph.find(vertex) != graph.end())
    {  for (int i =0; i<graph[vertex].size();i++)
        {
            adjacent.push_back(graph[vertex].at(i).first);
        }


        // sort the vector; not needed for strings/our project
      /*  for (int i =1;i<adjacent.size(); i++)
        {
            string key = adjacent.at(i);
            int j = i-1;
            while (key<adjacent.at(j)&& j>=0)
            {
                adjacent.at(j+1) = adjacent.at(j);
                j--;
            }
            adjacent.at(j+1) = key;
        }
        */
    }
    return adjacent;
}

void Graph::printGraph()
{
    auto itr = graph.begin();
    for (; itr != graph.end(); ++ itr)
    {
        vector<string> temp = getAdjacent(itr->first);
        cout<<itr->first;
        if (temp.size()!=0)
            cout<<" ";
        for (int i =0; i<temp.size();i++)
        {
            cout<<temp.at(i);
            if (i!= temp.size()-1)
                cout<<" ";
        }
        cout<<endl;
    }
}

int Graph::getIndegree(string vertex)
{

    int degree = 0;
    auto itr = graph.begin();
    for (; itr != graph.end(); ++ itr)
    {

        for (int i =0; i<graph[itr->first].size();i++)
        {
            if (graph[itr->first].at(i).first == vertex )
            {
                degree++;
            }
        }
    }

    return degree;
}

int Graph::getOutdegree(string vertex)
{

    int degree = 0;
    if (graph.find(vertex) != graph.end())
    {
        degree = graph[vertex].size();
    }

    return degree;
}

int Graph::costliestEdge()
{

    auto itr = graph.begin();
    int largest = graph[itr->first].at(0).second ;
    for (; itr != graph.end(); ++ itr)
    {

        for (int i =0; i<graph[itr->first].size();i++)
        {
            if (graph[itr->first].at(i).second > largest )
            {
                largest = graph[itr->first].at(i).second;
            }
        }
    }
    return largest;

}

// Other Functions
// Load Data Function loads the flights data from a given csv
void LoadData(vector<Graph>& flights, string path)
{
    fstream file;
    file.open(path,ios::in | ios::out);
    if(!file.is_open()){
        throw std::invalid_argument("File not found");
    }

    string line, day, start, end, distance, temp;

    while ( getline(file,line))
    {
        stringstream s(line);
        getline(s,day,',');
        getline(s, temp, ',');
        start = start+temp.substr(1,temp.length());
        getline(s, temp, ',');
        start = start+temp.substr(0,temp.length()-1);

        getline(s, temp, ',');
        end = end+temp.substr(1,temp.length());
        getline(s, temp, ',');
        end = end+temp.substr(0,temp.length()-1);

        getline(s,distance);

        for (int i =0; i<31; i++)
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

//the Function prints out the shortest path starting from location A and ends at loation B
void dijkstra(Graph& graph, string start, string end)
{
    if (start == end)
    {
        cout << start + " -> Arrived!" << endl;
        return;
    }
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
        cout<<results.top()<<" -> ";
        results.pop();
    }
    cout<<"Arrived!"<<endl;

}
string bellmanFord(map<string, vector<pair<string,int>>>& g, string src, string dest)
{
    // check if src/dest is a valid input in main()
    if (src == dest)
    {
        cout << src + " -> Arrived!" << endl;
        return src + " -> Arrived!";
    }
    // Note: Why distMap and strVec? A vector is used to allow me to iterate
    // through src first, before other vertices. The map allows faster accesses.

    // initialize distance map and get number of edges
    map<string,pair<int,string>> distMap; // value, (distance, parent)
    vector<string> strVec;
    distMap[src] = pair<int,string>(0,""); // val=src,d=0,p=""
    strVec.push_back(src);
    for (auto iter = g.begin(); iter != g.end(); ++iter)
    {
        // if value does not already exist in distMap, insert it
        if (distMap.count(iter->first) == 0)
        {
            distMap[iter->first] = pair<int,string>(INT_MAX,""); // val, d = 'infinity', p = null
            strVec.push_back(iter->first);
        }
    }

    int distU = 0;
    int distV = 0;
    int edgeWeight = 0;
    string strVal = "";
    set<string> found;
    found.insert(src);
    for (int i = 0; i < g.size()-1; i++) // |V|-1 iterations
    {
        // iterate through every vertex in distMap
        for (int j = 0; j < strVec.size(); j++)
        {
            strVal = strVec.at(j);
            if (found.count(strVal) > 0)
            {
                // iterate through edges: relax edges
                for (int k = 0; k < g[strVal].size(); ++k)
                {
                    if (found.count(g[strVal].at(k).first) == 0); // if vertex was not found, mark found
                    found.insert(g[strVal].at(k).first);
                    // Used pseudocode for relaxing edges (from discussion slides)
                    distU = distMap[strVal].first;
                    edgeWeight = g[strVal].at(k).second;
                    distV = distMap[g[strVal].at(k).first].first;
                    if (distU + edgeWeight < distV)
                    {
                        int newDistV = distU + edgeWeight;
                        string newPre = strVal;
                        distMap[g[strVal].at(k).first].first = distU + edgeWeight; // distV = ...
                        distMap[g[strVal].at(k).first].second = strVal; // predecessorV = ...
                    }
                }
            }
        }
    }
    // not necessary to check for negative-weight values, since all of
    // our data uses positive values for distance

    // return shortest path from src->dest
    bool foundSrc = false;
    string path = "";
    stack<string> stk;
    stk.push(dest);
    while (!foundSrc)
    {
        stk.push(distMap[stk.top()].second); // push parent on stack
        if (stk.top() == src)
            foundSrc = true;
    }
    while(!stk.empty())
    {
        path += stk.top();
        if (stk.size() > 1)
            path += " -> ";
        stk.pop();
    }
    cout << path << " -> Arrived!"<<endl;
    return path;
}
// Functions for checking
// This function checks whether the input day is valid (i.e. between 1 and 31)
bool checkDay(string day){
    bool valid = true;
    for (int i = 0; i < day.length(); i++)
    {
        //33 - 64 is special charaters
        //91-96
        //48-57 digits
        //123-126
        if (isdigit(day[i]))
        {
            valid = true;

        }
        else {
            valid = false;
            break;
        }
    }
    int date = 0;
    if (valid)
    {
        date = stoi(day);
        if (date < 1 || date > 31)
        {
            day = "";
            valid = false;
        }
    }

    return valid;
}
// This function checks whether the input location is valid
bool checkLocation(Graph& graph, string stend) {
    bool valid = true;
    auto it = graph.graph.find(stend);
    if (it == graph.graph.end()) {
        //not found
        valid = false;
    }
    return valid;
}
// This function checks whether the a destination is reachable from a given starting location using BFS
bool bfsReachable(Graph& graph, string src, string dest)
{
    set<string> visited;
    queue<string> s;
    visited.insert(src);
    s.push(src);
    while(!s.empty())
    {
        string u = s.front();
        s.pop();
        for (auto v: graph.getAdjacent(u))
        {
            if(v==dest)
                return true;
            if(visited.find(v)==visited.end())
            {
                visited.insert(v);
                s.push(v);
            }
        }
    }
    return false;
}

// For Testing
void Testing(vector<Graph>& flights)
{
    srand(time(0));
    int day = rand() % 31;
    string start, end = "";
    int size = flights[day].graph.size();
    int s1 = rand()% size;
    int s2 = rand()% size;
    int counter = 0;
    while (s2 == s1)
    {
        s2 = rand()% size;
    }
    auto itr = flights[day].graph.begin();
    for (; itr!= flights[day].graph.end(); itr++)
    {
        if (counter == s1)
        {
            start = itr->first;
        }
        if (counter == s2)
        {
            end = itr ->first;
        }
        counter ++;
    }

    cout<<"Speed Testing for Dijkstra Algorithm: "<<endl;
    auto begin = high_resolution_clock::now();
    dijkstra(flights[day], start, end);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<seconds>(stop - begin);
    cout <<"Time: "<< duration.count() <<" seconds"<<endl;

    cout<<"Speed Testing for Bellman-Ford Algorithm: "<<endl;
    auto b = high_resolution_clock::now();
    string temp = bellmanFord(flights[day].graph, start, end);
    auto s = high_resolution_clock::now();
    auto d = duration_cast<seconds>(s - b);
    cout <<"Time: "<< d.count() <<" seconds"<< endl;


}