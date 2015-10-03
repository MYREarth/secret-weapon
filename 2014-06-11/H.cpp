#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 5000;

int n, m, count[N][N], gcd[N][N];

// 799026027343168

int main() {
    memset(count, 0, sizeof(count));
    n = 5000, m = 5000;
    memset(gcd, -1, sizeof(gcd));
    for (int a = 1; a < n; ++ a) {
        for (int b = 1; b < m; ++ b) {
            if (gcd[a][b] == -1) {
                for (int i = 1; a * i < n && b * i < m; ++ i) {
                    gcd[a * i][b * i] = i;
                }
            }
        }
    }
    for (int i = 1; i < n; ++ i) {
        for (int j = 1; j < m; ++ j) {
            count[i][j] ++;
        }
    }
    for (int a = 1; a < n; ++ a) {
        for (int b = 1; b <= a; ++ b) {
            if (gcd[a][b] == 1) {
                int delta = a == b ? 1 : 2;
                for (int a0 = a, b0 = b; a0 < n && b0 < m; a0 += a, b0 += b) {
                    for (int x = a0 + b, y = b0 + a; x < n && y < m; x += b, y += a) {
                        count[x][y] += delta;
                    }
                }
                //for (int i = 1; a * i < n && b * i < m; ++ i) {
                //    for (int j = 1; a * i + b * j < n && b * i + a * j < m; ++ j) {
                //        count[a * i + b * j][b * i + a * j] ++;
                //    }
                //}
            }
        }
    }
    scanf("%d%d", &n, &m);
    long long result = 0;
    for (int i = 1; i < n; ++ i) {
        for (int j = 1; j < m; ++ j) {
            result += (long long)count[i][j] * (n - i) * (m - j);
        }
    }
    printf("%lld\n", result);
    return 0;
}
