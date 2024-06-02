#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int n;
vector<int> graph[200001];
ll dp[200001], ans[200001];

// First DFS to calculate the answer for node 1 and the size
// of each node's subtree
void dfs1(int node = 1, int parent = 0, ll depth = 0)
{
    // Add depth to the answer for node 1
    ans[1] += depth;

    // Initialize the size of the subtree rooted at node to
    // 1
    dp[node] = 1;

    // For each child of node
    for (int i : graph[node])

        // If the child is not the parent
        if (i != parent) {

            // Recurse on the child
            dfs1(i, node, depth + 1);

            // Add the size of the child's subtree to
            // dp[node]
            dp[node] += dp[i];
            cout<<"dp["<<node<<"]"<<dp[node]<<", dp["<<i<<"]"<<dp[i]<<endl;
        }
}

// Second DFS to calculate the answer for all nodes
void dfs2(int node = 1, int parent = 0)
{

    // For each child of node
    for (int i : graph[node])

        // If the child is not the parent
        if (i != parent) {

            // Calculate the answer for the child
            ans[i] = ans[node] + n - 2 * dp[i];

            // Recurse on the child
            dfs2(i, node);
        }
}

// Driver code
int main()
{

    n = 5;
    vector<pair<int, int> > edges
        = { { 1, 2 }, { 1, 3 }, { 3, 4 }, { 3, 5 } };

    // Build the graph
    for (auto edge : edges) {
        int a = edge.first, b = edge.second;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    // Run the first DFS
    dfs1();

    cout<<"dp1:"<<endl;
    for (int i = 1; i <= n; ++i) {
        cout<<dp[i]<<" ";
    }
    cout<<endl;

    // Run the second DFS
    dfs2();

    // Print the answer for each node
    for (int i = 1; i <= n; i++)
        cout << ans[i] << ' ';

    return 0;
}
