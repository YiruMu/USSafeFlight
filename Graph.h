#include <string>
#include <map>
#include<vector>
using namespace std;

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


        // sort the vector; might not needed for strings
        for (int i =1;i<adjacent.size(); i++)
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


