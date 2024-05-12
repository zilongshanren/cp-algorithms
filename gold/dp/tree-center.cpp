#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

const int N=20010;
int n,a,b,c,ans=2e9;
struct edge{int v,w;};
vector<edge> e[N];
int d1[N],d2[N],path[N],up[N];

void dfs_d(int x,int fa){
    for(auto ed : e[x]){
        int y=ed.v, z=ed.w;
        if(y==fa) continue;
        dfs_d(y, x);
        if(d1[y]+z>d1[x])
            d2[x]=d1[x],d1[x]=d1[y]+z,path[x]=y;
        else if(d1[y]+z>d2[x]) d2[x]=d1[y]+z;
        printf("回%d d1=%d d2=%d\n",x,d1[x],d2[x]);
    }
}
void dfs_up(int x,int fa){
    for(auto ed : e[x]){
        int y=ed.v, z=ed.w;
        if(y==fa) continue;
        if(y==path[x])up[y]=max(up[x],d2[x])+z;
        else up[y]=max(up[x],d1[x])+z;
        printf("下%d up=%d\n",y,up[y]);
        dfs_up(y, x);
    }
}
int main(){
    cin>>n;
    for(int i=1; i<n; i++){
        cin>>a>>b>>c;
        e[a].push_back({b,c});
        e[b].push_back({a,c});
    }
    dfs_d(1, 0);
    dfs_up(1, 0);
    for(int i=1; i<=n; i++)
        ans=min(ans,max(d1[i],up[i]));
    cout << ans << endl;
    return 0;
}
