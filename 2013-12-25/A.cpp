#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>

const int N = 20000;

int n, m, a[N], l[N], r[N], order[N], block_size, phi[N + 1];
std::vector <int> divisors[N + 1];
long long result[N];

bool compare(int i, int j) {
    if (l[i] / block_size != l[j] / block_size) {
        return l[i] / block_size < l[j] / block_size;
    }
    return (l[i] / block_size & 1) ^ (r[i] < r[j]);
}

int multiples[N + 1];
long long current, binom[N + 1];

#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i)

void modify(int a, int signum) {
    foreach (it, divisors[a]) {
        int d = *it;
        if (signum == 1) {
            current += multiples[d] * phi[d];
        } else {
            current -= (multiples[d] - 1) * phi[d];
        }
        multiples[d] += signum;
    }
}

int main() {
    for (int i = 0; i <= N; ++ i) {
        binom[i] = (long long)i * (i - 1) / 2;
    }
    for (int i = 1; i <= N; ++ i) {
        for (int j = i; j <= N; j += i) {
            divisors[j].push_back(i);
        }
    }
    phi[1] = 1;
    for (int i = 2; i <= N; ++ i) {
        int p = divisors[i][1];
        if (i / p % p == 0) {
            phi[i] = phi[i / p] * p;
        } else {
            phi[i] = phi[i / p] * (p - 1);
        }
    }
    int test_count;
    scanf("%d", &test_count);
    for (int t = 1; t <= test_count; ++ t) {
        scanf("%d", &n);
        for (int i = 0; i < n; ++ i) {
            scanf("%d", a + i);
        }
        scanf("%d", &m);
        for (int i = 0; i < m; ++ i) {
            scanf("%d%d", l + i, r + i);
            l[i] --;
            r[i] --;
            order[i] = i;
        }
        block_size = std::max(static_cast<int>(sqrt(static_cast<double>(n) / 2)), 1);
        std::sort(order, order + m, compare);
        memset(result, -1, sizeof(result));
        int left = 0;
        int right = -1;
        current = 0;
        memset(multiples, 0, sizeof(multiples));
        for (int _ = 0; _ < m; ++ _) {
            int i = order[_];
            while (right < r[i]) {
                modify(a[++ right], +1);
            }
            while (left > l[i]) {
                modify(a[-- left], +1);
            }
            while (right > r[i]) {
                modify(a[right --], -1);
            }
            while (left < l[i]) {
                modify(a[left ++], -1);
            }
            result[i] = current;
        }
        printf("Case #%d:\n", t);
        for (int i = 0; i < m; ++ i) {
            printf("%I64d\n", result[i]);
        }
    }
    return 0;
}
