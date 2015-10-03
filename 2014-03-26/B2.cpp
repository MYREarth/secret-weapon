#include <cstdio>

int main() {
    int n = 2;
    for (int i = 0, j = 1; i < 1 << n; ++ i) {
        j *= 5;
        j %= 1 << n + 1;
        printf("%d, ", j);
    }
    puts("");
}
