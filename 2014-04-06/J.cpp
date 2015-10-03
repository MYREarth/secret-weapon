#include<cmath>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

inline double dist(double x, double y, double z) {
    return sqrt(x * x + y * y + z * z);
}

const int N = 13;
int n, sx[N], sy[N], sz[N], cx[N][N], cy[N][N], cz[N][N], m[N];

double start[N], gend[N], dis[N][N], g[N][N], dp[1 << N][N];

void solve(int n) {
    for (int st = 0; st < (1 << n); ++st) {
        for (int i = 0; i < n; ++i) {
            dp[st][i] = 1e100;
        }
    }
    for (int i = 0; i < n; ++i) {
        dp[1 << i][i] = start[i];
    }
    for (int st = 0; st < (1 << n); ++st) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (~st >> j & 1) {
                    dp[st | 1 << j][j] = min(dp[st | 1 << j][j], dp[st][i] + dis[i][j]);
                }
            }
        }
    }
}

int main() {
    while (scanf("%d", &n) == 1 && n) {
        int mx, my, mz;
        scanf("%d%d%d", &mx, &my, &mz);
        for (int i = 0; i < n; ++i) {
            scanf("%d%d%d%d", m + i, sx + i, sy + i, sz + i);
            for (int j = 0; j < m[i]; ++j) {
                scanf("%d%d%d", &cx[i][j], &cy[i][j], &cz[i][j]);
            }
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m[i]; ++j) {
                start[j] = dist(sx[i] - cx[i][j], sy[i] - cy[i][j], sz[i] - cz[i][j]);
            }
            for (int j = 0; j < m[i]; ++j) {
                for (int k = 0; k < m[i]; ++k) {
                    dis[j][k] = dist(cx[i][j] - cx[i][k], cy[i][j] - cy[i][k], cz[i][j] - cz[i][k]);
                }
            }
            solve(m[i]);
            int full = (1 << m[i]) - 1;
            for (int j = 0; j < n; ++j) {
                g[i][j] = 1e100;
                for (int k = 0; k < m[i]; ++k) {
                    g[i][j] = min(g[i][j], dp[full][k] + dist(sx[j] - cx[i][k], sy[j] - cy[i][k], sz[j] - cz[i][k]));
                }
            }
            gend[i] = 1e100;
            for (int j = 0; j < m[i]; ++j) {
                gend[i] = min(gend[i], dp[full][j]);
            }
        }
        for (int i = 0; i < n; ++i) {
            start[i] = dist(mx - sx[i], my - sy[i], mz - sz[i]);
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                dis[i][j] = g[i][j];
            }
        }
        solve(n);
        double ans = 1e100;
        int full = (1 << n) - 1;
        for (int i = 0; i < n; ++i) {
            ans = min(ans, dp[full][i] + gend[i]);
        }
        printf("%.12f\n", ans);
    }
    return 0;
}
