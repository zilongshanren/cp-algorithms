#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

struct Point {
    double x, y;
};

struct LineSegment {
    Point start, end;
};

bool compareX(const Point &a, const Point &b) {
    return a.x < b.x;
}

vector<Point> findIntersections(vector<LineSegment> &lineSegments) {
    vector<Point> eventQueue;
    for (const LineSegment &segment : lineSegments) {
        eventQueue.push_back(segment.start);
        eventQueue.push_back(segment.end);
    }

    sort(eventQueue.begin(), eventQueue.end(), compareX);

    set<double> activeHorizontalSegments;
    vector<Point> intersections;

    for (const Point &event : eventQueue) {
        LineSegment currentSegment = {event, event}; // Create a dummy segment to find the position in the status set

        auto it = activeHorizontalSegments.lower_bound(currentSegment.start.y);
        if (it != activeHorizontalSegments.begin() && it != activeHorizontalSegments.end()) {
            auto below = prev(it);

            if (currentSegment.start.x == currentSegment.end.x) { // Vertical segment
                for (auto y = below; y != it; ++y) {
                    intersections.push_back({currentSegment.start.x, *y});
                }
            } else { // Horizontal segment
                if (event.x == currentSegment.start.x) {
                    activeHorizontalSegments.insert(currentSegment.start.y);
                } else {
                    activeHorizontalSegments.erase(currentSegment.start.y);
                }
            }
        }
    }

    return intersections;
}

int main() {
    vector<LineSegment> lineSegments = {
        {{0, 0}, {10, 0}},
        {{0, 5}, {10, 5}},
        {{5, 0}, {5, 10}},
        {{10, 0}, {20, 0}}
    };

    vector<Point> intersections = findIntersections(lineSegments);

    for (const Point &intersection : intersections) {
        cout << "Intersection point: (" << intersection.x << ", " << intersection.y << ")" << endl;
    }

    return 0;
}
