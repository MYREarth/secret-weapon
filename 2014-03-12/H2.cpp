#include <cstdio>
#include <cstring>
#include <algorithm>

const int N = 100;

int n, m, a[N], dp[N + 1][N + 1];

void update(int &x, int a) {
    x = std::max(x, a);
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++ i) {
        scanf("%d", a + i);
    }
    memset(dp, 0, sizeof(dp));
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j <= m; ++ j) {
            update(dp[i + 1][j], dp[i][j]);
            if (j < m) {
                for (int k = i, sum = 0; k < n; ++ k) {
                    sum += a[k];
                    update(dp[k + 1][j + 1], dp[i][j] + sum);
                }
            }
        }
    }
    printf("%d\n", dp[n][m]);
    return 0;
}
