#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 205, MOD = 666013;

char s[N];

int f[N];

int n, k;

int main() {
    scanf("%d%d", &n, &k);
    scanf("%s", s);
    int ans = 1;
    for (int i = 0; i < n; ++i) {
        if (s[i] == '?') {
            ans = ans * k % MOD;
        }
    }
    for (int i = 1; i < n; ++i) {
        f[i] = 1;
        for (int j = 0; j < i; ++j) {
            char pattern = s[j];
            for (int k = j; k < n; k += i) {
                if (pattern == '#') {
                    continue;
                } else if (pattern == '?') {
                    pattern = s[k];
                } else if (s[k] != '?') {
                    pattern = s[k] == pattern ?  pattern : '#';
                }
            }
            if (pattern == '#') {
                f[i] *= 0;
            } else if (pattern == '?') {
                f[i] = f[i] * k % MOD;
            }
        }
        for (int j = 1; j < i; ++j) {

            f[i] = (f[i] - f[__gcd(i, j)] + MOD) % MOD;
        }
        printf("%d %d\n",i,f[i]);
        ans = (ans - f[i] + MOD) % MOD;
    }
    printf("%d\n", ans);
    return 0;
}
