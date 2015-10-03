#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int n;

unsigned long long k;

const int N = 100005;

int ans[N];

int main() {
    freopen("bubble.in", "r", stdin);
    freopen("bubble.out", "w", stdout);
    while (scanf("%d%llu", &n, &k) == 2 && n) {
        for (int i = 0; i < n; ++i) {
            if (n - i - 2 > 63) {
                ans[i] = i;
                continue;
            }
            for (int j = 0; j < n - i; ++j) {
                unsigned long long delta = 1ull << (n - i - 2 - j);
                if (k <= delta || j == n - i) {
                    ans[i] = i + j;
                    for (int k = i + 1; k <= i + j; ++k) {
                        ans[k] = k - 1;
                    }
                    i += j;
                    break;
                } else {
                    k -= delta;
                }
            }
        }
        for (int i = 0; i < n; ++i) {
            printf("%d%c", ans[i] + 1, i == n - 1 ? '\n' : ' ');
        }
    }
    return 0;
}
