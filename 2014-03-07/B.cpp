#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 2505;
int n, d, r, m;
int v[N];
double x[N];

int sign(double x, double eps = 1e-9) {
    return x < -eps ? -1 : x > eps;
}

void go() {
    int next = -1;
    double t = 1e10;
    for (int i = 0; i < n; ++i) {
        if (v[i] == 0) {
            continue;
        }
        if (v[i] > 0) {
            double tt = (d - r - x[i]) / v[i];
            if (t > tt) {
                next = i;
                t = tt;
            }
        } else {
            double tt = (x[i] - r) / -v[i];
            if (t > tt) {
                next = i;
                t = tt;
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        x[i] = x[i] + v[i] * t;
    }
    v[next] = -v[next];
}

int main() {
    freopen("arcanoid.in", "r", stdin);
    freopen("arcanoid.out", "w", stdout);
    scanf("%d%d%d%d", &n, &d, &r, &m);
    for (int i = 0; i < n; ++i) {
        scanf("%lf", x + i);
    }
    for (int i = 0; i < n; ++i) {
        scanf("%d", v + i);
    }
    for (int i = 0; i < m; ++i) {
        go();
    }
    for (int i = 0; i < n; ++i) {
        if (sign(x[i] - r) == 0 && v[i] > 0) {
            x[i] = 0;
        } else if (sign(x[i] - (d - r)) == 0 && v[i] < 0) {
            x[i] = d;
        }
        printf("%.12f%c", x[i], i == n - 1 ? '\n' : ' ');
    }
    return 0;
}
