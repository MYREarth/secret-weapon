#include<cmath>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 105;

int n, w, x[N], y[N];

double dis[N][2];

double ans;

int sign(double x, double eps = 1e-9) {
    return x < -eps ? -1 : x > eps;
}

const double pi = acos(-1);

double dist(double x, double y) {
    return sqrt(x * x + y * y);
}

double ang(double x, double y) {
    return atan2(y, x);
}

int main() {
    freopen("race.in", "r", stdin);
    freopen("race.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 0; i <= n; ++i) {
        scanf("%d%d", x + i, y + i);
    }
    scanf("%d", &w);
    ans = 1e10;
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= 1; ++j) {
            dis[i][j] = 1e10;
            int tx = x[i], ty = y[i] + j * w;
            double l = -pi / 2, r = pi / 2;
            for (int k = i - 1; k >= 0; --k) {
                double ll = ang(-(x[k] - tx), y[k] - ty), rr = ang(-(x[k] - tx), y[k] + w - ty);
                if (sign(ll - l) >= 0 && sign(r - ll) >= 0) {
                    dis[i][j] = min(dis[i][j], dis[k][0] + dist(tx - x[k], ty - y[k]));
                }
                if (sign(rr - l) >= 0 && sign(r - rr) >= 0) {
                    dis[i][j] = min(dis[i][j], dis[k][1] + dist(tx - x[k], ty - (y[k] + w)));
                }
                l = max(ll, l), r = min(rr, r);
            }
            if (sign(r - 0) >= 0 && sign(0 - l) >= 0) {
                dis[i][j] = min(dis[i][j], (double)tx);
            }
            //cout << i << ' ' << j << ' ' << tx << ' ' << ty << ' ' << dis[i][j] << endl;
            l = -pi / 2, r = pi / 2;
            for (int k = i + 1; k <= n; ++k) {
                double ll = ang((x[k] - tx), y[k] - ty), rr = ang((x[k] - tx), y[k] + w - ty);
                l = max(ll, l), r = min(rr, r);
            }
            if (sign(r - 0) >= 0 && sign(0 - l) >= 0) {
                ans = min(ans, dis[i][j] + (double)x[n] - tx);
            }
        }
    }
    printf("%.12f\n", ans);
    return 0;
}
