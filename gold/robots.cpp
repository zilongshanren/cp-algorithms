#include<bits/stdc++.h>
using namespace std;
typedef long long ll;


const int N=5e5+10,INF=1e9+10;

int n,m,k;
struct Edge{
	int v,c,w;
};

vector <Edge> G[N];
int U[N],V[N],C[N],W[N];

struct Node{
	int u; ll d;
	bool operator < (const Node __) const {
		return d>__.d;
	}
};

priority_queue <Node> que;
ll dis[N],S[N];


map <int,int> st[N];

void AddEdge(int u,int v,int c,int w){
    //没有这个颜色
	if(!st[u].count(c)) {
        //添加虚点
		st[u][c]=++k;
		G[u].push_back((Edge){k,0,0});
	}
	int t=st[u][c];

	G[t].push_back((Edge){v,c,w});

    S[t]+=w;
}

void Upd(int u,ll d){
    // cout<<"Ppd u="<<u<<", d = "<<d<<",dist[u]= "<<dis[u]<<endl;
	if(dis[u] <= d) return;

	dis[u]=d;
    // cout<<"update dist "<<u<<", dist = "<<dis[u]<<endl;
    que.push((Node){u,d});
}

void Dijkstra(){
	memset(dis,63,sizeof dis);

	dis[1]=0;
    que.push((Node){1,0});

	while(!que.empty()) {
		int u=que.top().u;
        ll d=que.top().d;
        que.pop();
        // cout<<"pop u = "<<u<<", d = "<<d<<endl;

		if(dis[u]<d) continue;

		if(u<=n) {
			for(Edge dd : G[u]) {
				int t=dd.v;

				for(Edge i : G[t]) {
                    //策略1 or 策略2，选择最短路径
					Upd(i.v, d + min((ll)i.w, S[t]-i.w));
                    //更新虚点的距离
					Upd(st[i.v][i.c], d);
				}
			}
		} else {
            //走虚点
            for(Edge i : G[u]) {
                //case 2
                //走虚点，使用策略2，虚点距离-i.w
                Upd(i.v, d + S[u] - i.w);
            }
        }
	}
	printf("%lld\n",dis[n]<1e17?dis[n]:-1);
}

int main(){
	freopen("robot.in","r",stdin),freopen("robot.out","w",stdout);
    cin>>n>>m;
	k=n;

	for (int i = 1; i <= m; ++i) {
		int u,v,c,w;
        cin>>u>>v>>c>>w;
		AddEdge(u,v,c,w);
        AddEdge(v,u,c,w);
	}



	Dijkstra();
}
