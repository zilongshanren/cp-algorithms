// C++ code to find the maximum path sum
#include <bits/stdc++.h>
using namespace std;

vector<int> dp;

// function for dfs traversal and to store the
// maximum value in dp[] for every node till the leaves
void dfs(int a[], vector<int> v[], int u, int parent)
{
	// initially dp[u] is always a[u]
	dp[u] = a[u - 1];

	// stores the maximum value from nodes
	int maximum = 0;

	// traverse the tree
	for (int child : v[u]) {

		// if child is parent, then we continue
		// without recursing further
		if (child == parent)
			continue;

		// call dfs for further traversal
		dfs(a, v, child, u);

		// store the maximum of previous visited node
		// and present visited node
		maximum = max(maximum, dp[child]);
	}

	// add the maximum value returned to the parent node
	dp[u] += maximum;
}

// function that returns the maximum value
int maximumValue(int a[], vector<int> v[])
{
	dfs(a, v, 1, 0);
	return dp[1];
}

// Driver Code
int main()
{
	// number of nodes
	int n = 14;

	// adjacency list
	vector<int> v[n + 1];

	// create undirected edges
	// initialize the tree given in the diagram
	v[1].push_back(2), v[2].push_back(1);
	v[1].push_back(3), v[3].push_back(1);
	v[1].push_back(4), v[4].push_back(1);
	v[2].push_back(5), v[5].push_back(2);
	v[2].push_back(6), v[6].push_back(2);
	v[3].push_back(7), v[7].push_back(3);
	v[4].push_back(8), v[8].push_back(4);
	v[4].push_back(9), v[9].push_back(4);
	v[4].push_back(10), v[10].push_back(4);
	v[5].push_back(11), v[11].push_back(5);
	v[5].push_back(12), v[12].push_back(5);
	v[7].push_back(13), v[13].push_back(7);
	v[7].push_back(14), v[14].push_back(7);

	// values of node 1, 2, 3....14
	int a[] = { 3, 2, 1, 10, 1, 3, 9, 1, 5, 3, 4, 5, 9, 8 };
	// initialise dp
	dp = vector<int>(n+1,0);
	// function call
	cout << maximumValue(a, v)<<endl;

	return 0;
}
