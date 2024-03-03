//https://cses.fi/problemset/task/1667
#include <unordered_map>
#include <list>
#include <iostream>
#include <algorithm>
#include <queue>
#include <map>

using namespace std;


class Graph {
    map<int, list<int>> adjList;
public:
    Graph() {
    }
    void addEdge(int u, int v, bool bidir = true) {
        adjList[u].push_back(v);
        if (bidir)
            adjList[v].push_back(u);
    }
    void bfs(int source_node, int dst_node, int n) {
        queue<int> q;

        map<int, bool> visited;
        q.push(source_node);
        visited[source_node] = true;

        bool hasPath = false;

        int anyValidPath[n];
        for (int i = 1; i <= n; ++i) {
            anyValidPath[i] = 0;
        }

        vector<int> solutions;

        while (!q.empty() && !hasPath)
        {
            int node = q.front();
            // cout << node << "  ";
            q.pop();

            for (int neighbor : adjList[node])
            {
                if (!visited[neighbor])
                {
                    q.push(neighbor);
                    visited[neighbor] = true;
                    anyValidPath[neighbor]  = node;


                    if (neighbor == dst_node) {
                        //todo: print path
                        hasPath = true;
                        solutions.push_back(dst_node);
                        while(anyValidPath[dst_node] != source_node) {
                            dst_node = anyValidPath[dst_node];
                            solutions.push_back(dst_node);
                        }
                        solutions.push_back(source_node);
                        std::reverse(solutions.begin(), solutions.end());
                        cout<<solutions.size()<<endl;
                        for (int i = 0; i < solutions.size(); ++i) {
                            cout<<solutions[i]<<" ";
                        }

                        break;
                    }
                }
            }
        }

        if (!hasPath) {
            cout<<"IMPOSSIBLE"<<endl;
        }
    }
};

int main(int argc, char *argv[])
{
    Graph g;
    int m, n;
    cin>>n>>m;

    for (int i = 0; i < m; ++i) {
        int u,v;
        cin>>u>>v;
        g.addEdge(u, v);
    }

    g.bfs(1, n, n+1);

    return 0;
}
