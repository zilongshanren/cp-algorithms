#include <bits/stdc++.h>

using namespace std;

struct Edge {
    int a, b, cost;
};

int n, m;
vector<Edge> edges;
const int INF = 1000000000;

void solve()
{
    vector<int> d(n);
    vector<int> p(n, -1);
    int x;
    for (int i = 0; i < n; ++i) {
        x = -1;
        for (Edge e : edges) {
            if(d[e.a] < INF){
                if (d[e.a] + e.cost < d[e.b]) {
                    d[e.b] = max(-INF, d[e.a] + e.cost);
                    p[e.b] = e.a;
                    x = e.b;
                }
            }
        }
    }

    // for (int i = 0; i < n; i++) {
    //     cout<<"p:"<<i<<" "<<p[i]<<endl;
    // }

    if (x == -1) {
        cout << "No negative cycle found.";
    } else {
        cout<<"x = "<<x<<endl;
        for (int i = 0; i < n; ++i)
            x = p[x];

        cout<<"x = "<<x<<endl;
        vector<int> cycle;
        for (int v = x;; v = p[v]) {
            // cout<<"v = "<<v<<endl;
            cycle.push_back(v);
            if (v == x && cycle.size() > 1)
                break;
        }
        reverse(cycle.begin(), cycle.end());

        cout << "Negative cycle: ";
        for (int v : cycle)
            cout << v << ' ';
        cout << endl;
    }
}

int main(int argc, char *argv[])
{
// 5 5
// 1 2 3
// 1 3 5
// 3 2 2
// 2 4 1
// 4 3 -7

    cin>>n>>m;

    for (int i = 0; i < m; ++i) {
        Edge e;
        cin>>e.a>>e.b>>e.cost;
        edges.push_back(e);
    }

    solve();
    return 0;
}
