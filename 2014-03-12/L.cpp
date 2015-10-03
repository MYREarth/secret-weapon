#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int main() {
    freopen("local.in", "r", stdin);
    freopen("local.out", "w", stdout);
    int t;
    scanf("%d", &t);
    for (int i = 1; i <= t; ++i) {
        int n;
        scanf("%d", &n);
        int ans = 0;
        for (int j = 0; j < n; ++j) {
            int op;
            scanf("%d", &op);
            if (op != 1) {
                int a;
                scanf("%d", &a);
                ans += a;
            } else {
                int a, b;
                scanf("%d%d", &a, &b);
                ans += a * b;
            }
        }
        printf("Day %d: %d dollars.\n", i, ans);
    }
    return 0;
}
