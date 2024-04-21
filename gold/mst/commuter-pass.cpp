#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

vector<pair<ll, ll>> graph[100001];
ll du[100001], dv[100001], ds[100001], dp[2][100001], ans;
bool visited[100001];

void dijkstra1(ll start, ll arr[]) {
	fill(visited, visited + 100001, false);

	priority_queue<pair<ll, ll>> pq;
	//cost-node
	pq.push({0, start});
	while (!pq.empty()) {
		ll c, node;
		tie(c, node) = pq.top();
		pq.pop();

		if (!visited[node]) {
			arr[node] = -c;
			visited[node] = true;
			for (auto &i : graph[node]){
				//why minus cost?
				pq.push({c - i.second, i.first});
			}
		}
	}
}

void dijkstra2(ll start, ll end) {
	fill(dp[0], dp[0] + 100001, LLONG_MAX / 2);
	fill(dp[1], dp[1] + 100001, LLONG_MAX / 2);
	fill(visited, visited + 100001, false);

	priority_queue<pair<ll, pair<ll, ll>>> pq;
	pq.push({0, {start, 0}});
	dp[0][0] = dp[1][0] = LLONG_MAX / 2;

	//traverse to store the parent node
	while (!pq.empty()) {
		ll c, node, par;
		pair<ll, ll> p;
		tie(c, p) = pq.top();
		tie(node, par) = p;
		pq.pop();

		// cout<<"visit node:"<<node<<", parent "<<par<<", c = "<<-c<<",ds[node]"<<ds[node]<<endl;

		if (!visited[node]) {
			visited[node] = true;
			ds[node] = -c;
			cout<<"visit "<<node<<",parent="<<par<<endl;
			dp[0][node] = min(du[node], dp[0][par]);
			dp[1][node] = min(dv[node], dp[1][par]);
			for (auto i : graph[node]) {
				pq.push({c - i.second, {i.first, node}});
			}
		} else if (-c == ds[node]) {
			cout<<"visit same c="<<c<<",node="<<node<<endl;
			if (min(du[node], dp[0][par]) + min(dv[node], dp[1][par]) <= dp[0][node] + dp[1][node]) {
				dp[0][node] = min(du[node], dp[0][par]);
				dp[1][node] = min(dv[node], dp[1][par]);
			}
		}
	}

	ans = min(ans, dp[0][end] + dp[1][end]);
	cout<<"ans = "<<ans<<endl;
}

int main() {
	iostream::sync_with_stdio(false);
	cin.tie(0);
	ll n, m, s, t, u, v;
	cin >> n >> m >> s >> t >> u >> v;
	for (int i = 0; i < m; i++) {
		ll a, b, c;
		cin >> a >> b >> c;
		graph[a].push_back({b, c});
		graph[b].push_back({a, c});
	}

	dijkstra1(u, du);
	cout<<"du:\n"<<endl;
	for(int i = 1; i <= n; ++i) {
		cout<<du[i]<<" ";
	}
	cout<<endl;

	dijkstra1(v, dv);

	cout<<"dv:\n"<<endl;
	for(int i = 1; i <= n; ++i) {
		cout<<dv[i]<<" ";
	}
	cout<<endl;

	ans = du[v];
	// cout<<"ans = "<<ans<<endl;

	dijkstra2(s, t);

	int end = 8;

	for (int i = 1; i <= end; ++i) {
		cout<<"dp[u]:"<<dp[0][i]<<' ';
	}

	cout<<"\n===================="<<endl;

	for (int i = 1; i <= end; ++i) {
		cout<<"dp[v]:"<<dp[1][i]<<' ';
	}

	cout<<"\n===================="<<endl;

	// cout<<"ds:\n"<<endl;
	// for(int i = 0; i <= n; ++i) {
	// 	cout<<ds[i]<<" ";
	// }
	// cout<<endl;

	dijkstra2(t, s);

	for (int i = 1; i <= end; ++i) {
		cout<<"dp[u]:"<<dp[0][i]<<' ';
	}
	cout<<"\n===================="<<endl;

	for (int i = 1; i <= end; ++i) {
		cout<<"dp[v]:"<<dp[1][i]<<' ';
	}
	cout<<"\n===================="<<endl;

	// cout<<"ds:\n"<<endl;
	// for(int i = 0; i <= n; ++i) {
	// 	cout<<ds[i]<<" ";
	// }
	// cout<<endl;

	cout << ans << '\n';
	return 0;
}
