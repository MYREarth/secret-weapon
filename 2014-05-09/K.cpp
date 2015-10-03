#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

long double fac(int n) {
    long double ret = log(1);
    for (int i = 1; i <= n; ++i) {
        ret += log((long double)i);
    }
    return ret;
}

int cnt(int n) {
    int ret = 0;
    for (int i = 1; (1 << i) <= n; ++i) {
        ret += n / (1 << i);
    }
    return ret;
}

int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    if (k == 1) {
        printf("%.12f\n", (double)n);
        return 0;
    }
    if (k > n) {
        printf("%.12f\n", 0.0);
        return 0;
    }
    int p1 = (n * (n - 1) / 2 % 2) ? -1 : 1, p2 = (cnt(n) - cnt(k)) == 0;
    long double ans = 0;
    ans = exp(fac(n) - 2 * (fac(k) + fac(n - k)) + fac(n - k)) + p2 * p1 * exp(-fac(n));
    printf("%.12f\n", (double)ans);
    return 0;
}
