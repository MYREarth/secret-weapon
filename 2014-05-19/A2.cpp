#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int n;

int main() {
    int ans = 0;
    scanf("%d", &n);
    for (int st = 0; st < (1 << n); ++st) {
        if (__builtin_popcount(st) <= __builtin_popcount(ans)) {
            continue;
        }
        bool check = true;
        for (int i = 0; i < n && check; ++i) {
            if (st >> i & 1) {
                for (int j = i + 1; j < n && check; ++j) {
                    if (st >> j & 1) {
                        int k = 2 * (j - i) + j;
                        if (k < n && (st >> k & 1)) {
                            check = false;
                        }
                    }
                }
            }
        }
        if (check) {
    printf("%d\n", __builtin_popcount(ans));
    for (int i = 0; i < n; ++i) {
        if (ans >> i & 1) {
            printf("%d%c", i + 1, (ans >> i + 1) ? ' ' : '\n');
        }
    }
            ans = st;
        }
    }
    printf("%d\n", __builtin_popcount(ans));
    for (int i = 0; i < n; ++i) {
        if (ans >> i & 1) {
            printf("%d%c", i + 1, (ans >> i + 1) ? ' ' : '\n');
        }
    }
    return 0;
}
