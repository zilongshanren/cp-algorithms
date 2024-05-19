#include <bits/stdc++.h>

using namespace std;

class Point {
public:
	long double x, y;
	bool operator<(const Point &other) {
		if (x == other.x) { return y < other.y; }
		return x < other.x;
	}
};

const pair<Point, Point> INF{{-1e9, -1e9}, {1e9, 1e9}};

long double dist(const pair<Point, Point> &a) {
	long double d1 = a.first.x - a.second.x;
	long double d2 = a.first.y - a.second.y;
	return sqrt(d1 * d1 + d2 * d2);
}

pair<Point, Point> get_closest_points(const pair<Point, Point> &a,
                                      const pair<Point, Point> &b) {
	return dist(a) < dist(b) ? a : b;
}

/**
 * Brute force for points with near
 * the median point in the sorted array
 */
pair<Point, Point> strip_solve(vector<Point> &points) {
	pair<Point, Point> ans = INF;
	for (int i = 0; i < (int)points.size(); i++) {
		for (int j = i + 1; j < (int)points.size() && j - i < 9; j++) {
			ans = get_closest_points(ans, {points[i], points[j]});
		}
	}
	return ans;
}

/** Solve the problem for range [l, r] */
pair<Point, Point> solve(vector<Point> &points, int l, int r) {
	if (l == r) { return INF; }
	int mid = (l + r) / 2;

	// The smallest distance in range [l, mid]
	pair<Point, Point> ans_left = solve(points, l, mid);
	// The smallest distance in range [mid+1, r]
	pair<Point, Point> ans_right = solve(points, mid + 1, r);
	pair<Point, Point> ans;

	ans = get_closest_points(ans_left, ans_right);
	long double delta = dist(ans);

	Point mid_point = points[mid];
	vector<Point> strip;
	for (int i = l; i < r; i++) {
		if (abs(points[i].x - mid_point.x) <= delta) {
			strip.push_back(points[i]);
		}
	}
	sort(strip.begin(), strip.end(), [](Point a, Point b) {return a.y < b.y || (a.y == b.y && a.x < b.x);});
	return get_closest_points(ans, strip_solve(strip));
}

int main() {
	int n;
	while (scanf("%d", &n) && n > 0) {
		vector<Point> v;
		for (int i = 0; i < n; i++) {
			long double x, y;
			scanf("%Lf %Lf", &x, &y);
			v.push_back({x, y});
		}
        std::sort(v.begin(), v.end(), [](Point a, Point b) {return a.x < b.x || (a.x == b.x && a.y < b.y);});
		pair<Point, Point> ans = solve(v, 0, v.size());
		printf("%0.2Lf %0.2Lf %0.2Lf %0.2Lf\n", ans.first.x, ans.first.y, ans.second.x, ans.second.y);
	}
}
