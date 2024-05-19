#include<bits/stdc++.h>
using namespace std;
typedef long ll;

#define N 100005
ll n;
ll f[N][2];//f[][0]--不选 f[][1]-- 选
ll tot,p[N],h[N],ne[N<<1];


void dfs(int u,int fa){
    f[u][0]=0;
    f[u][1]=1;
    for(int i=h[u];i;i=ne[i]) {
        if(p[i]!=fa) {
            int v=p[i];
            dfs(p[i],u);

            f[u][1]+=f[v][0];
            f[u][0]+=max(f[v][0],f[v][1]);
        }
    }
}

void add(int u,int v){
    p[++tot]=v;
    ne[tot]=h[u];
    h[u]=tot;
}
int main()
{
    int s;
    cin>>n>>s;
    for(int i=0;i<n;++i){
        int u,v;
        cin>>u>>v;
        add(u,v);
        add(v,u);
    }
    dfs(s,0);
    cout<<f[s][1];
}
