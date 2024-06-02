#include<bits/stdc++.h>

using namespace std;

const int N = 101;

int root;
int n,m;
int b[N];
int a[N][N];
int f[N][N];
int v[N];
int w[N];

int dfs(int u) {
    for (int i = v[u]; i <= m; ++i) {
        f[u][i] = w[u];
    }
    for (int i = 0; i < b[u]; ++i) {
        int s=a[u][i];
        dfs(s);
        for (int j = m; j >= v[u]; j--) {
            for (int k = 0; k <= j - v[u]; k++) {
                f[u][j] = max(f[u][j], f[u][j-k] + f[s][k]);
            }
        }
    }
    return 0;

}



int main(int argc, char *argv[])
{
    cin>>n>>m;

    for (int i = 1; i <= n; ++i) {
        int p;
        cin>>v[i]>>w[i]>>p;
        if (p == -1) {
            root = i;
        }
        else {
            a[p][b[p]++] = i;
        }
    }
    dfs(root);
    cout<<f[root][m]<<endl;

    return 0;
}
