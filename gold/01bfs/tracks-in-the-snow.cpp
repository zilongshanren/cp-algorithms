// https://oj.uz/problem/view/BOI13_tracks

#include<iostream>
#include<map>
#include<list>
#include<vector>
#include<algorithm>
#include<queue>

using namespace std;

class Graph {
    map<int, list<int> > adjList;
public:
    Graph() {

    }

    void addEdge(int u, int v, bool bi) {
        adjList[u].push_back(v);
        if (bi) {
            adjList[v].push_back(u);
        }
    }

    void bfs()




};




int main(int argc, char *argv[])
{

    return 0;
}
