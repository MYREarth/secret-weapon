#include <cstdio>
#include <cstring>
#include <algorithm>

const int N = 20000;

int a[N];

int main() {
    int tests;
    scanf("%d", &tests);
    while (tests --) {
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; ++ i) {
            scanf("%d", a + i);
        }
        std::sort(a, a + n);
        int result = 0;
        for (int i = n - 3; i >= 0; i -= 3) {
            result += a[i];
        }
        printf("%d\n", result);
    }
    return 0;
}
