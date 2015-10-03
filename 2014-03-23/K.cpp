#include<cmath>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 100005;
int n;

struct Point {
    double x, y;

    Point (double x = 0, double y = 0) : x(x), y(y) {}

    void in() {
        scanf("%lf%lf", &x, &y);
    }

    double len2() {
        return x * x + y * y;
    }

    double len() {
        return sqrt(len2());
    }
};

Point operator + (Point a, Point b) {
    return Point(a.x + b.x, a.y + b.y);
}

Point operator - (Point a, Point b) {
    return Point(a.x - b.x, a.y - b.y);
}

Point operator * (double k, Point a) {
    return Point(k * a.x, k * a.y);
}

double dot(Point a, Point b) {
    return a.x * b.x + a.y * b.y;
}

Point l[N][2];

void go(Point &v) {
    for (int i = 1; i <= n; ++i) {
        Point v1 = l[i][0], v2 = l[i][1];
        v = v1 + dot((v2 - v1), (v - v1)) / (v2 - v1).len2() * (v2 - v1);
    }
}

const double eps = 1e-8;

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        l[i][0].in(), l[i][1].in();
    }
    l[n][0] = l[0][0], l[n][1] = l[0][1];
    Point a = l[0][0], b = l[0][1], aa = a, bb = b;
    go(aa), go(bb);
    if ((aa - bb).len() < eps) {
        printf("%.12f %.12f\n", aa.x, aa.y);
    } else {
        Point t = b - a - bb + aa, w = aa - a;
        double x = 0;
        if (t.len() < eps) {
            if (w.len() > eps) {
                printf("-1\n");
            } else {
                x = 0;
            }
        } else {
            if (abs(t.x) > eps) {
                x = w.x / t.x;
            } else {
                x = w.y / t.y;
            }
        }
        Point ans = a + x * (b - a);
        printf("%.12f %.12f\n", ans.x, ans.y);
    }
    return 0;
}
