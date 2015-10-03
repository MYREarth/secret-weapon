#include<cmath>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

double f[205];

double cb(int n, int m) {
    return f[n] - f[m] - f[n - m];
}

double dp[205][25];
bool vis[205][25];

double getans(int n, int k) {
    if (vis[n][k]) {
        return dp[n][k];
    }
    int kill = min(k, n - k);
    vis[n][k] = true;
    if (k == 0) {
        return dp[n][k] = n;
    } else if (n == k + kill) {
        return dp[n][k] = 0;
    } else {
        dp[n][k] = 0;
        for (int r = 0; r <= n - kill; ++r) {
            double tmp = 0;
            for (int l = 0; l <= r && l <= k; ++l) {
                if (n - kill - k < r - l) {
                    continue;
                }
                double p = exp(cb(k, l) + cb(n - kill - k, r - l) - cb(n - kill, r));
                tmp += p * getans(n - kill - r, k - l);
            }
            dp[n][k] = max(dp[n][k], tmp);
        }
        return dp[n][k];
    }
}

int main() {
    f[0] = 0;
    for (int i = 1; i <= 205; ++i) {
        f[i] = f[i - 1] + log(i);
    }
    memset(vis, 0, sizeof(vis));
    int n, k;
    scanf("%d%d", &n, &k);
    printf("%.12f\n", getans(n, k));
    return 0;
}
