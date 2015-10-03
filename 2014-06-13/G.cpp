#include<cmath>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

struct Point {
    double x, y;

    Point(double x = 0, double y = 0) : x(x), y(y) {}

    void in() {
        scanf("%lf%lf", &x, &y);
    }
};

Point operator - (Point &a, Point &b) {
    return Point(a.x - b.x, a.y - b.y);
}

int sign(double x, double eps = 1e-9) {
    return x < -eps ? -1 : x > eps;
}

const double pi = acos((double)-1);
int n, m, a;

double ang, k;

const int N = 10005;

int ord[N];
double h[N];

bool by_h(const int &i, const int &j) {
    return h[i] > h[j];
}

Point p[N];

double cal(const Point &a, const Point &b, const double &y) {
    return a.x + (y - a.y) / (b.y - a.y) * (b.x - a.x);
}

double pos[N];

int main() {
    freopen("green.in", "r", stdin);
    freopen("green.out", "w", stdout);
    scanf("%d%d%d", &n, &m, &a);
    ang = (double)a / 180 * pi;
    k = tan(ang);
    for (int i = 0; i < n; ++i) {
        scanf("%lf", h + i);
        ord[i] = i;
    }
    sort(ord, ord + n, by_h);
    for (int i = 0; i < m; ++i) {
        p[i].in();
        p[i].y += p[i].x * k;
    }
    vector<Point> ground;
    int last = 0;
    ground.push_back(p[0]);
    for (int i = 1; i < m; ++i) {
        if (sign(p[i].y - p[last].y) <= 0) {
            continue;
        }
        if (last != i - 1) {
            ground.push_back(Point(cal(p[i - 1], p[i], p[last].y), p[last].y));
        }
        ground.push_back(p[i]);
        last = i;
    }
    double ans = h[ord[0]], lasty = ground.back().y;
    pos[ord[0]] = ground.back().x;
    for (int i = 1; i < n; ++i) {
        double newy = lasty - h[ord[i]];
        while (ground.size() > 1 && sign(ground[ground.size() - 2].y - newy) >= 0) {
            ground.pop_back();
        }
        if (ground.size() == 1) {
            pos[ord[i]] = ground[0].x;
            newy = ground[0].y;
        } else {
            pos[ord[i]] = cal(ground[ground.size() - 2], ground.back(), newy);
        }
        ans += lasty - newy;
        lasty = newy;
    }
    printf("%.12f\n", ans);
    for (int i = 0; i < n; ++i) {
        printf("%.12f\n", pos[i]);
    }
    return 0;
}
