#include <bits/stdc++.h>
using namespace std;

int dx[4]{1, -1, 0, 0}, dy[4]{0, 0, 1, -1};

int n, m, depth[4000][4000], ans = 1;
string snow[4000];

bool inside(int x, int y) {
	return (x > -1 && x < n && y > -1 && y < m && snow[x][y] != '.');
}

int main() {
	iostream::sync_with_stdio(false);
	cin.tie(0);

	cin >> n >> m;
	for (int i = 0; i < n; i++) cin >> snow[i];

	deque<pair<int, int>> q;
	q.push_back({0, 0});
	depth[0][0] = 1;

	while (q.size()) {
		pair<int, int> c = q.front();
        cout<<"process:"<<c.first<<", "<<c.second<<endl;
		q.pop_front();
		ans = max(ans, depth[c.first][c.second]);

		for (int i = 0; i < 4; i++) {
			int x = c.first + dx[i], y = c.second + dy[i];
			if (inside(x, y) && depth[x][y] == 0) {
                //相同的雪
				if (snow[x][y] == snow[c.first][c.second]) {
                    //copy depth to the new patch
					depth[x][y] = depth[c.first][c.second];
					q.push_front({x, y});
				} else {
					depth[x][y] = depth[c.first][c.second] + 1;
                    // cout<<"x = "<<x<<", y = "<<y<<", depth = "<<depth[x][y]<<endl;
					q.push_back({x, y});
				}
			}
		}
	}

	cout << ans;
	return 0;
}
