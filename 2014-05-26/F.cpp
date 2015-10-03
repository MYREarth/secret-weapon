#include <cstdio>
#include <cstring>
#include <algorithm>

const int N = 100000;
const int M = 1000000;

int n, q, s[N], c[N], x[N], start[N + 1], need[N + 1], f[M + 1];

int main() {
    freopen("greedy.in", "r", stdin);
    freopen("greedy.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) {
        scanf("%d", s + i);
    }
    for (int i = 0; i < n; ++ i) {
        scanf("%d", c + i);
    }
    scanf("%d", &q);
    for (int i = 0; i < q; ++ i) {
        scanf("%d", x + i);
    }
    int m = *std::max_element(x, x + q);
    int total = 0;
    start[0] = 0;
    need[0] = m + 1;
    for (int i = 0; i < n; ++ i) {
        need[i + 1] = std::max(s[i], need[i] - s[i]);
        start[i + 1] = start[i];
        if (s[i] < need[i] - s[i]) {
            total += c[i];
            c[i] *= -1;
            start[i + 1] += s[i];
        }
    }
    memset(f, -1, sizeof(f));
    for (int j = 0; j < need[n]; ++ j) {
        f[start[n] + j] = total;
    }
    for (int i = n - 1; i >= 0; -- i) {
        if (c[i] > 0) {
            for (int j = s[i]; j < need[i]; ++ j) {
                f[start[i] + j] = f[start[i] + j - s[i]] + c[i];
            }
        } else {
            for (int j = 0; j < s[i]; ++ j) {
                f[start[i] + j] = f[start[i] + j + s[i]] + c[i];
            }
        }
    }
    for (int i = 0; i < q; ++ i) {
        printf("%d\n", f[x[i]]);
    }
    return 0;
}
