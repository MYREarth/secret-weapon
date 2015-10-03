#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int n, s, top, down;

const int N = 404;

const int S = 1500;

int a[N], dp[2][S * 2 + 1][S + 1];

const int INF = 1000000000;

inline int cal(int top, int n) {
    if (top < n) {
        return (top + 1) * top / 2;
    } else {
        return (top + top - n + 1) * n / 2;
    }
}

int main() {
    scanf("%d", &n);
    s = 0;
    for (int i = 0; i < n; ++i) {
        scanf("%d", a + i);
        s += a[i];
    }
    top = 0;
    while (cal(top, n) <= s) {
        ++top;
    }
    int now = 0;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < S * 2 + 1; ++j) {
            for (int k = 0; k <= S; ++k) {
                dp[i][j][k] = INF;
            }
        }
    }
    for (int i = 0; i < top; ++i) {
        dp[now][a[0] - i + s][i] = abs(a[0] - i);
    }
    for (int i = 1; i < n; ++i) {
        int next = now ^ 1;
        int b = a[i];
        for (int j = 0; j < s * 2 + 1; ++j) {
            for (int k = 0; k < top; ++k) {
                if (dp[now][j][k] == INF) {
                    continue;
                }
                if (k != 0) {
                    int delta = b - (k - 1);
                    if (j + delta >= 0 && j + delta < S * 2 + 1) {
                        dp[next][j + delta][k - 1] = min(dp[next][j + delta][k - 1], dp[now][j][k] + abs(j + delta - s));
                    }
                }
                int delta = b - k;
                if (j + delta >= 0 && j + delta < S * 2 + 1) {
                    dp[next][j + delta][k] = min(dp[next][j + delta][k], dp[now][j][k] + abs(j + delta - s));
                }
                if (k != top - 1) {
                    int delta = b - (k + 1);
                    if (j + delta >= 0 && j + delta < S * 2 + 1) {
                        dp[next][j + delta][k + 1] = min(dp[next][j + delta][k + 1], dp[now][j][k] + abs(j + delta - s));
                    }
                }
                dp[now][j][k] = INF;
            }
        }
        now = next;
    }
    int ans = INF;
    for (int i = 0; i < top; ++i) {
        ans = min(ans, dp[now][s][i]);
    }
    printf("%d\n", ans);
    return 0;
}
