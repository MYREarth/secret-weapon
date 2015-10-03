#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int n, k;

const int N = 205;

char s[N];

int main() {
    scanf("%d%d", &n, &k);
    scanf("%s", s);
    int ans = 0;
    for (int st = 0; st < (1 << n); ++st) {
        bool flag = true;
        for (int j = 0; j < n; ++j) {
            if (s[j] != '?' && s[j] - '0' != (st >> j & 1)) {
                flag = false;
            }
        }
        if (flag) {
            bool good = true;
            for (int j = 1; j < n; ++j) {
                bool cmp = true;
                for (int k = 0; k < j; ++k) {
                    if ((st >> k & 1) != (st >> (n - j + k) & 1)) {
                        cmp = false;
                        break;
                    }
                }
                if (cmp) {
                    good = false;
                    break;
                }
            }
            if (good) {
                for (int j = 0; j < n; ++j) {
                    printf("%d", st >> j & 1);
                }
                printf("\n");
            }
            ans += good;
        }
    }
    printf("%d\n", ans);
    return 0;
}
