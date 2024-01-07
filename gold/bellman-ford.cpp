#include<bits/stdc++.h>
using namespace std;

template<typename T>
class Graph{
    unordered_map<T, list<pair<T,int> > > m;
public:
    void addEdge(T u,T v,int dist,bool bidir=true){
        m[u].push_back(make_pair(v,dist));
        if(bidir)
            m[v].push_back(make_pair(u,dist));
    }

    void printAdj(){
        for(auto j:m){
            cout<<j.first<<"->";
            for(auto l: j.second)
          cout<<"("<<l.first<<","<<l.second<<")";
            cout<<endl;
        }
    }


    void bellman-fold(T src){

    }
};

int main(){
    Graph<int> g;
    g.addEdge(1,2,1);
    g.addEdge(1,3,4);
    g.addEdge(2,3,1);
    g.addEdge(3,4,2);
    g.addEdge(1,4,7);
    g.printAdj();
    g.dijkstra(1);

    return 0;
}
