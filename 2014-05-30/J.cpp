#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int main() {
    freopen("jubilee.in", "r", stdin);
    freopen("jubilee.out", "w", stdout);
    int n;
    while (scanf("%d", &n) == 1 && n) {
        if (n == 3) {
            printf("1\n1 1 1\n1 1 1\n");
        } else if (n == 4) {
            printf("2\n1 1 2 2\n1 2 1 2\n");
        } else if (n == 5) {
            printf("2\n1 2 1 1 2\n1 2 2 1 2\n");
        } else if (n == 6) {
            printf("2\n1 2 1 2 1 2\n1 2 1 2 1 2\n");
        } else {
            printf("3\n");
            for (int i = 0; i < n; ++i) {
                printf("%d%c", i % 2 + 1, i == n - 1 ? '\n' : ' ');
            }
            for (int i = 0; i < n; ++i) {
                printf("3%c", i == n - 1 ? '\n' : ' ');
            }
        }
    }
    return 0;
}
