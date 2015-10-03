#include <cstdio>

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) {
        printf("%d & !%d\n", i + 1, (i + 1) % n + 1);
    }
    return 0;
}
