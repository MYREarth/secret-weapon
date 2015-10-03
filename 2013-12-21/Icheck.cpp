#include <cstdio>
#include <cstring>
#include <climits>
#include <cassert>
#include <algorithm>

const int N = 1000;

int n, m, a[N + 1], b[N + 1], dp[N + 1][N + 1];

int solve() {
    dp[0][0] = 0;
    for (int i = 0; i <= n; ++ i) {
        for (int j = 0; j <= m; ++ j) {
            if (i > 0 || j > 0) {
                dp[i][j] = INT_MAX;
                if (i) {
                    dp[i][j] = std::min(dp[i][j], dp[i - 1][j] + b[j]);
                }
                if (j) {
                    dp[i][j] = std::min(dp[i][j], dp[i][j - 1] + a[i]);
                }
            }
        }
    }
    return dp[n][m];
}

int main() {
    while (true) {
        static int test_cnt = 0;
        printf("now %d\n", ++ test_cnt);
        n = rand() % 2 + 1;
        m = rand() % 2 + 1;
        for (int i = 0; i <= n; ++ i) {
            a[i] = rand() % 2 + 1;
        }
        for (int i = 0; i <= m; ++ i) {
            b[i] = rand() % 2 + 1;
        }
for (int i = 0; i <= n; ++ i) {
    printf("%d, ", a[i]);
}
puts("");
for (int i = 0; i <= m; ++ i) {
    printf("%d, ", b[i]);
}
puts("");
        int ans1 = solve();
        std::sort(a, a + n + 1);
        std::sort(b, b + m + 1);
        int ans2 = solve();
printf("%d %d\n", ans1, ans2);
        assert(ans1 == ans2);
    }
    return 0;
}
