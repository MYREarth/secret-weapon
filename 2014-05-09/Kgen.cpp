#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 10;

int permutation[N];
long long total[N][2], count[N][N];

void solve(int n) {
    for (int i = 0; i < n; ++ i) {
        permutation[i] = i;
    }
    memset(total, 0, sizeof(total));
    do {
        memset(count, 0, sizeof(count));
        for (int i = 0; i < n; ++ i) {
            count[1][i] = 1;
        }
        for (int i = 2; i <= n; ++ i) {
            for (int j = 0; j < n; ++ j) {
                for (int k = 0; k < j; ++ k) {
                    if (permutation[k] > permutation[j]) {
                        count[i][j] += count[i - 1][k];
                    }
                }
            }
        }
        int inversion = 0;
        for (int i = 0; i < n; ++ i) {
            inversion += count[2][i];
        }
        for (int i = 1; i <= n; ++ i) {
            for (int j = 0; j < n; ++ j) {
                total[i][inversion % 2] += count[i][j];
            }
        }
    } while (std::next_permutation(permutation, permutation + n));
    double fact = 0.5;
    for (int i = 1; i <= n; ++ i) {
        fact *= i;
    }
    for (int i = 1; i <= n; ++ i) {
        printf("%.12f%c", total[i][0] / fact, " \n"[i == n]);
    }
}

int main() {
    for (int i = 1; i < N; ++ i) {
        solve(i);
    }
    return 0;
}
