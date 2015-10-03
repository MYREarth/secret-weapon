#include <cstdio>
#include <cstring>
#include <vector>

const int N = 10000000;

int  min_divisor[N + 1];

bool win(int n, int m) {
    if (n == 1) {
        return false;
    }
    return !win(m, n / min_divisor[n]);
}

int main() {
    freopen("funny.in", "r", stdin);
    freopen("funny.out", "w", stdout);
    memset(min_divisor, -1, sizeof(min_divisor));
    std::vector <int> primes;
    for (int d = 2; d <= N; ++ d) {
        if (min_divisor[d] == -1) {
            primes.push_back(d);
            min_divisor[d] = d;
        }
        for (int p : primes) {
            if (d * p > N) {
                break;
            }
            min_divisor[d * p] = p;
            if (d % p == 0) {
                break;
            }
        }
    }
    int n, m;
    while (scanf("%d%d", &n, &m) == 2 && n && m) {
        printf("%d %d - %s\n", n, m, win(n, m) ? "Vera" : "Harry");
    }
    return 0;
}
