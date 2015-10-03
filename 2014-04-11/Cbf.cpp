#include <cstdio>
#include <cstring>

const int MOD = (int)1e9 + 7;

const int N = 10;

int ways[N][N];

int main() {
    memset(ways, 0, sizeof(ways));
    ways[0][0] = 1;
    for (int i = 1; i < N; ++ i) {
        ways[i][0] = 1;
        for (int j = 1; j <= i; ++ j) {
            ways[i][j] = (ways[i - 1][j] + (long long)ways[i - 1][j - 1] * (i + i - j) % MOD) % MOD;
            printf("%10d", ways[i][j]);
        }
        puts("");
    }
    return 0;
}
