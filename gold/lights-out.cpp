#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll P = 31;
const ll MOD = 1e9 + 7;
// maximum vertical/horizontal distance
const int MX = 2e5;

struct Coord {
	int x, y;
};

int main() {
	freopen("lightsout.in", "r", stdin);
	freopen("lightsout.out", "w", stdout);

	int n;
	cin >> n;

	vector<Coord> dt(n);
	for (int i = 0; i < n; i++) { cin >> dt[i].x >> dt[i].y; }

	function<int(int i, int j)> calc_dist = [&](int i, int j) {
		return abs(dt[i].x - dt[j].x) + abs(dt[i].y - dt[j].y);
	};

	vector<vector<vector<int>>> dist(
	    n, vector<vector<int>>(n, vector<int>(2, INT32_MAX)));

	/*
	 * dist[i][j][0] - clockwise dist from i -> j
	 * dist[i][j][1] - counter-clockwise dist from i -> j
	 */
	for (int i = 0; i < n; i++) {
		for (int j = i; j < i + n; j++) {
			if (i == j) {
				dist[i][j][0] = 0;
			} else {
				int x = (j + n) % n;
				int y = (j - 1 + n) % n;
				dist[i][x][0] = dist[i][y][0] + calc_dist(x, y);
                // cout<<"i = "<<i<<", x = "<<x<<",dist="<<dist[i][x][0]<<endl;
			}
		}
	}
    cout<<endl;

	for (int i = 0; i < n; i++) {
		for (int j = i; j > i - n; j--) {
			if (i == j) {
				dist[i][j][1] = 0;
			} else {
				int x = (j + n) % n;
				int y = (j + 1 + n) % n;
				dist[i][x][1] = dist[i][y][1] + calc_dist(x, y);
                // cout<<"i = "<<i<<", x = "<<x<<",dist="<<dist[i][x][1]<<endl;
			}
		}
	}

	vector<int> ang(n);
	for (int i = 0; i < n; i++) {
        //-1 0 + 1 求夹角
		int prev = (i - 1 + n) % n;
		int nxt = (i + 1) % n;

		/*
		 * two types of possible angles (90 deg either on inside or outside)
		 * reminder: all edges are parallel to either x or y axis & alternate
		 */

		// derived from slope
		ll rt = ((dt[i].y - dt[prev].y) * (dt[nxt].x - dt[i].x) -
		         (dt[nxt].y - dt[i].y) * (dt[i].x - dt[prev].x));

		// no angle should ever be colinear
		assert(rt);

        // cout<<"prev="<<prev<<", next"<<nxt<<",rt="<<rt<<endl;

        //如果都是>0 则表示都是90，如果是 < 0 则表示是270（-90）
		ang[i] = rt > 0 ? MX + 2 : MX + 1;
	}

    // cout<<"ang"<<endl;
    // for (auto& item : ang) {
    //     cout<<item<<" ";
    // }
    // cout<<endl;

	vector<int> hash(1);
	hash[0] = 0;

	vector<ll> poly(2 * n + 1);

	poly[0] = 1;
	for (int i = 1; i < (int)(poly.size()); i++) {
		poly[i] = (int)(poly[i - 1] * P % MOD);
	}

    cout<<"output poly\n";
    for (auto item : poly) {
        cout<<item<<" ";
    }
    cout<<endl;

    //编码每一个顶点的信息，到hash 中去
    //使用距离和角度来编码
	for (int i = 1; i < n; i++) {
        //0-1
		hash.push_back((hash.back() * P + dist[(i - 1 + n) % n][i][0]) % MOD);
        //角度1
		hash.push_back((hash.back() * P + ang[i]) % MOD);
	}

    //退出结点
	hash.push_back(hash.back() * P + dist[n - 1][0][0]);

    cout<<"output hash\n";
    for (auto item : hash) {
        cout<<item<<" ";
    }
    cout<<endl;

	function<int(int i, int j)> get_hash = [&](int i, int j) {
		// gets the hash for the substring from i -> j
		// you can also compute this using the mod inverse of poly_i
		return ((hash[j] - ((hash[i] * poly[j - i]) % MOD) + MOD) % MOD);
	};

    // cout<<"hash size = "<<hash.size()<<endl;

	int ans = 0;
	for (int i = 1; i < (int)(hash.size()) - 2; i++) {
		int fin = -1;

        //n^2 brute force
		for (int len = 1; len < (int)(hash.size()) - i; len++) {
			int cr = get_hash(i, i + len);
            // cout<<"cr = "<<cr<<endl;
			int occ = 0;

			for (int j = 0; j < (int)(hash.size()) - len; j++) {
				if (get_hash(j, j + len) == cr) {
                    // cout<<"found i = "<<i<<", j = "<<j<<endl;
                    occ++;
                }
			}

			// bessie can uniquely identify her position
			if (occ == 1) {
				fin = (i + len + 1) / 2;
                cout<<"=========\n";
                cout<<"found position "<<fin<<endl;
                cout<<"=========\n";
				break;
			}
		}

		int start = (i + 2) / 2;
		if (fin >= n) { fin = -1; }

        cout<<"start = "<<start<<", fin = "<<fin<<endl;

		int a = dist[start][0][0];
		if (fin != -1) {
			// time to get to unique point + best dist from there
			a = min(dist[fin][0][0], dist[fin][0][1]) + dist[start][fin][0];
		}
		// default time to get to exit from start
		int b = min(dist[start][0][0], dist[start][0][1]);

        cout<<"a = "<<a<<", b = "<<b<<endl;

		ans = max(ans, a - b);
	}

	cout << ans << endl;
}
