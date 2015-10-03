#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 2000005;
int f[N];

int top1, p[N], cnt[N];

#define div DIV

int top2, div[N];

void go(int i, int mul) {
    if (i == top1) {
        div[top2++] = mul;
        return ;
    }
    for (int j = 0; j <= (int)cnt[i]; ++j) {
        go(i + 1, mul);
        mul *= p[i];
    }
}

int main() {
    f[1] = 1;
    for (int i = 2; i < N; ++i) {
        if (f[i] == 0) {
            f[i] = i;
            for (long long j = (long long)i * i; j < N; j += i) {
                f[j] = i;
            }
        }
    }
    int n;
    while (scanf("%d", &n) == 1 && n) {
        n *= 2;
        int oldn = n;
        top1 = 0;
        while (n > 1) {
            int a = f[n];
            cnt[top1] = 0;
            p[top1] = a;
            while (n % a == 0) {
                ++cnt[top1];
                n /= a;
            }
            ++top1;
        }
        top2 = 0;
        go(0, 1);
        n = oldn;
        int ans = 0;
        for (int i = 0; i < top2; ++i) {
            int l = div[i] - 1, a2 = n / (l + 1) - l, a;
            if (a2 % 2 != 0) {
                continue;
            }
            a = a2 / 2;
            if (a <= 1) {
                continue;
            }
            ++ans;
        }
        printf("%d\n", ans);
    }
    return 0;
}
