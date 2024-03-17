// https://cses.fi/problemset/task/1672
#include <bits/stdc++.h>
#include <vector>
using namespace std;

struct Edge {
    int a;
    int b;
    int w;
};



int main() {
    vector<Edge> edges;

    int INF = 0x3f3f3f3f;
    set<int> cities;

    int n,m,q;
    cin>>n>>m>>q;
    for (int i = 0; i < m; ++i) {
        Edge e;
        cin>>e.a>>e.b>>e.w;
        cities.insert(e.a);
        cities.insert(e.b);
        edges.push_back(e);
    }

    vector<int> distance[n];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            distance[i][j] = INF;
        }
    }


    for (auto node : cities) {
        //only need n-1 round
        for (int i = 0; i < n-1; ++i) {
            for(auto&& e : edges)  {
                // if (distance[e.a] < INF) {
                //     distance[e.b] = min(distance[e.b], distance[e.a] + e.w);
                // }
            }
        }
    }



    for (int i = 0; i < q; ++i) {
        int a, b;
        cin>>a>>b;
        if (a == 1) {
            if (distance[b] < INF) {
                cout<<distance[b]<<endl;
            }
            else {
                cout<<-1<<endl;
            }
        }
    }


    return 0;
}
