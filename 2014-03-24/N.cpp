#include <cstdio>
#include <cstring>
#include <algorithm>

const int P = 30001;
const int N = 70;

int inv[P], coef[N][N + 1];
char code[N + 1];

int main() {
    int tests;
    scanf("%d", &tests);
    while (tests --) {
        int p;
        scanf("%d%s", &p, code);
        inv[1] = 1;
        for (int i = 2; i < p; ++ i) {
            inv[i] = (long long)(p - p / i) * inv[p % i] % p;
        }
        int n = strlen(code);
        memset(coef, 0, sizeof(coef));
        for (int i = 0; i < n; ++ i) {
            coef[i][0] = 1;
            for (int j = 1; j < n; ++ j) {
                coef[i][j] = (long long)coef[i][j - 1] * (i + 1) % p;
            }
            coef[i][n] = code[i] == '*' ? 0 : code[i] - 'a' + 1;
        }
        for (int j = 0; j < n; ++ j) {
            int i = j;
            while (!coef[i][j]) {
                i ++;
            }
            for (int k = 0; k <= n; ++ k) {
                std::swap(coef[i][k], coef[j][k]);
            }
            int scale = inv[coef[j][j]];
            for (int k = 0; k <= n; ++ k) {
                coef[j][k] = (long long)coef[j][k] * scale % p;
            }
            for (int i = 0; i < n; ++ i) {
                if (i != j && coef[i][j]) {
                    int scale = coef[i][j];
                    for (int k = 0; k <= n; ++ k) {
                        coef[i][k] = (coef[i][k] + p - (long long)coef[j][k] * scale % p) % p;
                    }
                }
            }
        }
        for (int i = 0; i < n; ++ i) {
            printf("%d%c", coef[i][n], i == n - 1 ? '\n' : ' ');
        }
    }
    return 0;
}
