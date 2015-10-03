#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 505, M = 20005, BAR = 20000;

int n, q;

long long a[N], d[N], c[N], s[N];

const int LOG = 10;

const long long INF = 1ll << 60;

long long bag[N][M], dp[LOG][M];

void solve(int l, int r, int dep) {
    if (l == r) {
        for (int i = 0; i < M; ++i) {
            bag[l][i] = dp[dep][i];
        }
    } else {
        int m = l + r >> 1;
        for (int i = 0; i < M; ++i) {
            dp[dep + 1][i] = dp[dep][i];
        }
        for (int i = l; i <= m; ++i) {
            for (int j = 0; j + c[i] < M; ++j) {
                dp[dep + 1][j + c[i]] = min(dp[dep + 1][j + c[i]], dp[dep][j] + s[i]);
            }
        }
        solve(m + 1, r, dep + 1);
        for (int i = 0; i < M; ++i) {
            dp[dep + 1][i] = dp[dep][i];
        }
        for (int i = m + 1; i < r; ++i) {
            for (int j = 0; j + c[i] < M; ++j) {
                dp[dep + 1][j + c[i]] = min(dp[dep + 1][j + c[i]], dp[dep][j] + s[i]);
            }
        }
        solve(l, m, dep + 1);
    }
}

int main() {
    //scanf("%d%d", &n, &q);
    n = 500;
    for (int i = 0; i < n; ++i) {
        //scanf("%lld%lld%lld", a + i, d + i, c + i);
        //c[i] = min(c[i], (long long)BAR);
        //s[i] = c[i] * (a[i] + a[i] - d[i] * (c[i] - 1)) / 2;
        c[i] = 1;
        s[i] = 1;
    }
    for (int i = 0; i < M; ++i) {
        dp[0][i] = INF;
    }
    dp[0][0] = 0;
    solve(0, n - 1, 0);
    return 0;
}
