#include <bits/stdc++.h>
using namespace std;

class Graph {
    unordered_map<int, list<pair<int, int>>> m;

public:
    void addEdge(int u, int v, int dist, bool bidir = true) {
        m[u].push_back(make_pair(v, dist));
        if (bidir)
            m[v].push_back(make_pair(u, dist));
    }

    void printAdj() {
        for (auto j : m) {
            cout << j.first << "->";
            for (auto l : j.second)
                cout << "(" << l.first << "," << l.second << ")";
            cout << endl;
        }
    }

    void bellman_fold(int src) {}
};

int main() {
    Graph g;
    g.addEdge(1, 2, 1);
    g.addEdge(1, 3, 4);
    g.addEdge(2, 3, 1);
    g.addEdge(3, 4, 2);
    g.addEdge(1, 4, 7);
    g.printAdj();
    g.bellman_fold(1);

    return 0;
}
