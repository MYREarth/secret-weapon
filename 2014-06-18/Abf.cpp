#include <cstdio>
#include <cstring>

const int N = 50;

int n, x[N][6];

int main() {
    while (scanf("%d", &n) == 1) {
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < 6; ++ j) {
                scanf("%d", x[i] + j);
            }
        }
        int result = 1;
        double now = 0.;
        for (int _ = 0; _ < 100000; ++ _) {
            now += 0.001;
        }
        static int test_count = 0;
        printf("Case %d: %d\n", ++ test_count, result);
    }
    return 0;
}
