#include <string>
#include <map>
using namespace std;

class Graph{
private:
    // Graph ADJACENCY LIST data structure here
    map<string, vector<pair<string,int>>> graph;
public:
    void insertEdge(string from, string to, int weight);
    bool isEdge(int from, int to);
    int getWeight(int from, int to);
    vector<int> getAdjacent(int vertex);
    void printGraph();
    int getIndegree(string vertex);
    int getOutdegree(string vertex);
    int costliestEdge();
    vector<string> dijkstra(string originState, string destState);
    vector<string> bellmanFord(string origin, string destState);

};


