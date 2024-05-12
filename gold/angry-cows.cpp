#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int MAX_POS = 10;

int main() {
	freopen("angry.in", "r", stdin);
	freopen("angry.out", "w", stdout);

	int n;
	cin >> n;
	vector<int> bales(n);
	for (int i = 0; i < n; i++) {
		cin >> bales[i];
		// to avoid floats, double all coordinates
		bales[i] *= 2;
	}
	sort(bales.begin(), bales.end());

	/**
	 * @returns whether it's possible to explode
	 * the rest of the haybales before/after idx
	 *
	 * @param pos position of our cow
	 * @param idx furthest haybale we hit with our radius
	 * @param r current radius at our position
	 * @param dir whether we're checking positions to the right/left
	 */
	function<bool(int, int, int, bool)> push = [&](int pos, int idx, int r,
	                                               bool dir) {
		// finished search
		if (idx >= n - 1 && dir == 0) {
			return (idx >= n || pos + r >= bales[idx]);
		}
		if (idx <= 0 && dir == 1) {
            return (idx < 0 || pos - r <= bales[idx]);
        }

		if (dir == 0) {  // go right
			if (pos + r >= bales.back()) return true;

			int new_idx = idx;
			while (new_idx < n && pos + r >= bales[new_idx]) {
                new_idx++;
            }
            cout<<"right new_index = "<<new_idx<<endl;

			// no progression
			if (new_idx == idx) return false;

			return push(bales[new_idx - 1], new_idx, r - 2, dir);

		} else {  // go left
			if (pos - r <= bales[0]) return true;

			int new_idx = idx;
			while (new_idx < n && pos - r <= bales[new_idx]) {
                new_idx--;
            }

            cout<<"left new_index = "<<new_idx<<endl;

			// no progression
			if (new_idx == idx) return false;

			return push(bales[new_idx + 1], new_idx, r - 2, dir);
		}

		return false;
	};

	int lo = 0;
	int hi = MAX_POS * 2;
	while (lo < hi) {
		int power = lo + (hi - lo) / 2;

		/*
		 * finds the largest initial position such that
		 * our explosions propagate all the way to the left
		 */
		int pos_lo = 0;
		int pos_hi = MAX_POS * 2;

		while (pos_lo < pos_hi) {
			int pos = pos_lo + (pos_hi - pos_lo + 1) / 2;

			// get index of first haybale to our right
			int close =
			    lower_bound(bales.begin(), bales.end(), pos) - bales.begin();
            cout<<"close = "<<close<<", pos = "<<pos<<endl;

			// is it possible to complete our explosions heading left?
			if (close < n && push(pos, close, power, 1)) {
				pos_lo = pos;
                cout<<"left search... pos_lo "<<pos_lo<<endl;
			} else {
				pos_hi = pos - 1;
                cout<<"left search... pos_hi "<<pos_hi<<endl;
			}
		}

        cout<<"after bi search pos = "<<pos_lo<<endl;

        cout<<endl<<endl;


		int close =
		    upper_bound(bales.begin(), bales.end(), pos_lo) - bales.begin();
		// is it possible to complete our explosions heading right?
		if (push(pos_lo, close, power, 0)) {
			hi = power;
            cout<<"right search... hi power "<<hi<<endl;
		} else {
			lo = power + 1;
            cout<<"right search... lo power "<<lo<<endl;
		}
	}

	// rescale our answer
	cout << fixed << setprecision(1) << (double)lo / 2 << endl;
}
