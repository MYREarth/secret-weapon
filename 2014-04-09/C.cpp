#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>
#include <utility>
#include <vector>
#include <set>

const double PI  = acos(-1.);
const double EPS = 1e-8;

int signum(double x) {
    return x < -EPS ? -1 : x > EPS;
}

struct Point {
    double x, y;

    Point() : x(0), y(0) {}
    Point(double x, double y) : x(x), y(y) {}

    Point &operator +=(const Point &o) {
        x += o.x;
        y += o.y;
        return *this;
    }

    Point &operator -=(const Point &o) {
        x -= o.x;
        y -= o.y;
        return *this;
    }

    double arg() const {
        return atan2(y, x);
    }
};

Point rays[6];

bool operator <(const Point &a, const Point &b) {
    if (signum(a.x - b.x) != 0) {
        return signum(a.x - b.x) < 0;
    }
    return signum(a.y - b.y) < 0;
}

Point operator +(Point a, const Point &b) {
    return a += b;
}

Point operator -(Point a, const Point &b) {
    return a -= b;
}

double det(const Point &a, const Point &b) {
    return a.x * b.y - a.y * b.x;
}

int n;
Point p0;

std::vector <std::pair <double, int> > events;

void add_segment(Point a, Point b) {
    a -= p0;
    b -= p0;
    if (det(a, b) < 0) {
        std::swap(a, b);
    }
    double x = a.arg();
    double y = b.arg();
    events.push_back(std::make_pair(x,  1));
    events.push_back(std::make_pair(y, -1));
    if (y + EPS < x) {
        events.push_back(std::make_pair(PI, -1));
        events.push_back(std::make_pair(-PI, 1));
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    for (int i = 0; i < 6; ++ i) {
        double a = 2. * PI / 6. * i;
        rays[i] = Point(cos(a), sin(a));
    }
    scanf("%d%lf%lf", &n, &p0.x, &p0.y);
    {
        std::set <Point> centers;
        centers.insert(Point(0., 0.));
        std::queue <std::pair <Point, int> > queue;
        queue.push(std::make_pair(Point(0., 0.), 0));
        while (!queue.empty()) {
            Point c = queue.front().first;
            int   d = queue.front().second;
            queue.pop();
            for (int i = d & 1; i < 6; i += 2) {
                add_segment(c + rays[i], c + rays[(i + 1) % 6]);
            }
            if (d < n) {
                for (int i = d & 1; i < 6; i += 2) {
                    Point cc = c + rays[i] + rays[(i + 1) % 6];
                    if (!centers.count(cc)) {
                        centers.insert(cc);
                        queue.push(std::make_pair(cc, d + 1));
                    }
                }
            }
        }
    }
    events.push_back(std::make_pair(-PI, 0));
    events.push_back(std::make_pair(PI,  0));
    std::sort(events.begin(), events.end());
    int count = events[0].second;
    double result = 0;
    for (int i = 1; i < (int)events.size(); ++ i) {
        if (count == 2 * n) {
            result += events[i].first - events[i - 1].first;
        }
        count += events[i].second;
    }
    printf("%.8f\n", result / (2 * PI));
    return 0;
}
