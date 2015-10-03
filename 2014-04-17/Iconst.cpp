#include <cstdio>

const int RESULT[] = {1,1,2,5,14,43,140,474,1648,5839};

int main() {
    freopen("immetric.in", "r", stdin);
    freopen("immetric.out", "w", stdout);
    int tests = 0, n;
    while (scanf("%d", &n) == 1 && n) {
        printf("Case #%d: %d\n", ++ tests, RESULT[n]);
    }
    return 0;
}
