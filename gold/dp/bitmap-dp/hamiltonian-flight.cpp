#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int MAX_N = 20;
const ll MOD = (ll)1e9 + 7;

ll dp[1 << MAX_N][MAX_N];
// come_from[i] contains the cities that can fly to i
vector<int> come_from[MAX_N];

int main() {
	int city_num;
	int flight_num;
	cin >> city_num >> flight_num;
	for (int f = 0; f < flight_num; f++) {
		int start, end;
		cin >> start >> end;
		come_from[--end].push_back(--start);
	}

	dp[1][0] = 1;
	for (int s = 2; s < (1 << city_num); s++) {
		// only consider subsets that have the first city
		if ((s & (1 << 0)) == 0) continue;
		// also only consider subsets with the last city if it's the full subset
        // last city 1 << (city_num - 1)
        // full subset  s != ((1 << city_num) - 1)
		if ((s & (1 << (city_num - 1))) && s != ((1 << city_num) - 1)) continue;

		for (int end = 0; end < city_num; end++) {
            //不包含终点直接跳过
			if ((s & (1 << end)) == 0) continue;

            // cout<<"s="<<s<<endl;

			// the subset that doesn't include the current end
			int prev = s - (1 << end);
			for (int j : come_from[end]) {
				if ((s & (1 << j))) {
                    // cout<<"s = "<<s<<", end="<<end<<",dp[s][end]="<<dp[s][end]<<", prev "<<prev<<", j = "<<j<<", dp[prev][j]="<<dp[prev][j]<<endl;
					dp[s][end] += dp[prev][j];
					dp[s][end] %= MOD;
				}
			}
		}
	}

	cout << dp[(1 << city_num) - 1][city_num - 1] << '\n';
}
