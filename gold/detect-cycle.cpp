#include <iostream>
#include <map>
#include <queue>
#include <list>
using namespace std;

template <typename T>
class Graph
{
  map<T, list<T>> adjList;
  public:
  Graph()
  {
  }

  void addEdge(T u, T v, bool bidir = true)
  {
    adjList[u].push_back(v);
    if (bidir)
      adjList[v].push_back(u);
  }

  bool isCyclicBFS(T src)
  {
    map<T, bool> visited;
    map<T, int> parent;
    queue<T> q;
    q.push(src);
    visited[src] = true;
    parent[src] = src;

    while (!q.empty())
    {
      T node = q.front();
      q.pop();
      //Iterate over the neighbors of that node leaving the parent node
      for (T neighbor : adjList[node])
      {
        if (visited[neighbor] == true && parent[node] != neighbor)
          return true;
        else if (!visited[neighbor])
        {
          visited[neighbor] = true;
          parent[neighbor] = node;
          q.push(neighbor);
        }
      }
    }
    return false;
  }
};

int main()
{
  Graph<int> g;
  g.addEdge(1, 2);
  g.addEdge(1, 4);
  g.addEdge(4, 3);
  g.addEdge(2, 3);
  if (g.isCyclicBFS(1))
    cout << "Cyclic Graph\n";
  else
    cout << "Non cyclic\n";
}
