#include <bits/stdc++.h>

using namespace std;

const int MAX = 1e5 + 1;

int root[MAX];

int n, m;

void initialize()
{
    for (int i = 0; i < n; ++i) {
        root[i] = -1;
    }
}

int get(int x)
{
    return root[x] < 0 ? x : root[x] = get(root[x]);
}

bool isSame(int a, int b)
{
    return get(a) == get(b);
}

bool unit(int a, int b)
{
    int x = get(a);
    int y = get(b);
    if (x == y)  {
        return false;
    }

    if (root[x] > root[y]) {
        swap(x, y);
    }
    root[x] += root[y];
    root[y] = x;
    return true;
}

int size(int x)
{
    return -root[get(x)];
}



int main(int argc, char *argv[])
{

    cin>>n>>m;

    vector<pair<long long, pair<int, int>>> edges;
	for (int i = 0; i < m; i++) {
		int a, b;
		long long c;
		cin >> a >> b >> c;
		edges.push_back({c, {a, b}});
	}

    //kruskal
    sort(edges.begin(), edges.end());

    initialize();
    long long ans = 0;

    for (auto&& e : edges) {
        if (unit(e.second.first, e.second.second)) {
            ans += e.first;
        }
    }

    // for (int i = 0; i < n; ++i) {
    //     cout<<"root "<< i<< "=" << root[i]<<endl;
    // }

    // int dstRoot = 0;
    // for (int i = 0; i < n; ++i) {
    //     if (root[i] == -1) {
    //         dstRoot++;
    //     }
    // }

    if (size(1) != n) {
        cout<<"IMPOSSIBLE\n";
    }
    else {
        cout<<ans<<"\n";
    }



    return 0;
}
