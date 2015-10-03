#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 10005;
long double fac[N];

long double g(int a, int b) {
    return fac[a] + fac[b] - fac[a + b + 1];
}

long double s[N];

char ss[N];

const int K = 10;
pair<int, int> cnt[1 << K];

void cover(int l, int k) {
    for (int i = 0; i < (1 << k); ++i) {
        cnt[i] = make_pair(0, 0);
    }
    int mask = 0;
    for (int i = 0; i < k; ++i) {
        mask = mask << 1 | (ss[i] == 'B');
        s[i + 1] = s[i] - log((long double)2.0);
    }
    for (int i = k; i < l; ++i) {
        int &a = cnt[mask].first, &b = cnt[mask].second;
        if (ss[i] == 'A') {
            s[i + 1] = s[i] - g(a, b);
            s[i + 1] += g(++a, b);
        } else {
            s[i + 1] = s[i] - g(a, b);
            s[i + 1] += g(a, ++b);
        }
        mask = (mask << 1 | (ss[i] == 'B')) & ((1 << k) - 1);
    }
}

int main() {
    freopen("rsg.in", "r", stdin);
    freopen("rsg.out", "w", stdout);
    fac[0] = 0;
    for (int i = 1; i < N; ++i) {
        fac[i] = fac[i - 1] + log(i);
    }
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%s", ss);
        int l = strlen(ss);
        ss[l++] = 'A';
        long double sum1 = 0, sum2 = 0;
        for (int i = 1; i <= 10; ++i) {
            cover(l, i);
            sum1 += exp(s[l]);
            sum2 += exp(s[l - 1]);
        }
        double ans = sum1 / sum2;
        printf("%.12lf\n", ans);
    }
    return 0;
}
