#include <ctime>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <climits>
#include <utility>
#include <algorithm>

#define DEBUG(x)
//#define DEBUG(x) x

const int N = 1000000;

inline double sqr(double x) {
    return x * x;
}

struct Point {
    double x, y;

    Point() {}
    Point(double x, double y) : x(x), y(y) {}

    inline double to(const Point &p) const {
        return sqrt(sqr(x - p.x) + sqr(y - p.y));
    }
};

bool operator <(const Point &a, const Point &b) {
    return a.x < b.x;
}

int n, x[N], y[N];
double result;
Point points[N];

bool by_y(const Point &a, const Point &b) {
    return a.y < b.y;
}

Point candidates[N];

void solve(int l, int r) {
    if (r - l >= 3) {
        int mid = l + r >> 1;
        double xmid = points[mid].x;
        solve(l, mid);
        solve(mid, r);
        int total = 0;
        for (int i = std::upper_bound(points + l, points + r, Point(xmid - 0.5 * result, 0)) - points; i < r && points[i].x < xmid + 0.5 * result; ++ i) {
            candidates[total ++] = points[i];
        }
        std::sort(candidates, candidates + total, by_y);
        for (int i = 0; i < total; ++ i) {
            for (int j = i + 1; j < total && 2 * (candidates[j].y - candidates[i].y) < result; ++ j) {
                double dij = candidates[i].to(candidates[j]);
                if (dij * 2 < result) {
                    for (int k = j + 1; k < total && dij + (candidates[k].y - candidates[i].y + candidates[k].y - candidates[j].y) < result; ++ k) {
                        result = std::min(result, dij + candidates[j].to(candidates[k]) + candidates[k].to(candidates[i]));
                    }
                }
            }
        }
    }
}

int main() {
    scanf("%d", &n);
    DEBUG(n = 1000000);
    for (int i = 0; i < n; ++ i) {
        scanf("%d%d", x + i, y + i);
        DEBUG(x[i] = rand() % 1000000000);
        DEBUG(y[i] = rand() % 1000000000);
        //DEBUG(x[i] = 100000 + rand() % 100000);
        //DEBUG(y[i] = 100000 + rand() % 100000);
    }
    double theta = acos(-1.) * (double)rand() / RAND_MAX;
    double cosTheta = cos(theta);
    double sinTheta = sin(theta);
    for (int i = 0; i < n; ++ i) {
        points[i] = Point(x[i] * cosTheta - y[i] * sinTheta, x[i] * sinTheta + y[i] * cosTheta);
    }
    std::sort(points, points + n);
    result = 1e100;
    solve(0, n);
    printf("%.10f\n", result);
    return 0;
}
