#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll MOD = 2019201997LL;
const ll FACTOR1 = 2019201913LL;
const ll FACTOR2 = 2019201949LL;

/**
 * @return the number of miles cow a + 1 and b + 1 are willing to walk to see
 * each other
 */
ll calc_length(ll a, ll b) {
	a++, b++;
	return (a * FACTOR1 + b * FACTOR2) % MOD;
}

/**
 * Prim's Algorithm for dense graph to build the MST by scanning
 * @return the edge lengths in the MST
 */
vector<ll> prim(int N) {
	vector<ll> dist(N, MOD);
	vector<bool> visited(N, false);
	ll total_weight = 0;

	for (int i = 0; i < N; i++) {
		// find the nearest node to the current MST
		int min_dist_node = -1;
		for (int j = 0; j < N; j++) {
			if (!visited[j] &&
			    (min_dist_node < 0 || dist[j] < dist[min_dist_node])) {
				min_dist_node = j;
			}
		}

		// add this node to the MST
		visited[min_dist_node] = true;
		if (dist[min_dist_node] != MOD)
			total_weight += dist[min_dist_node];

		// update the distances between the MST and other unconnected nodes
		for (int j = 0; j < N; j++) {
			if (!visited[j]) {
				dist[j] = min(dist[j], calc_length(min(min_dist_node, j),
				                                   max(min_dist_node, j)));
			}
		}
	}
	return dist;
}

int main() {
	freopen("walk.in", "r", stdin);
	freopen("walk.out", "w", stdout);

	int N, K;
	cin >> N >> K;

	vector<ll> mst = prim(N);
	sort(mst.begin(), mst.end());
	cout << mst[N - K] << endl;
}
