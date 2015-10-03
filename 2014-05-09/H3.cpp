#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

long long calc(long long n) {
    return (64 - __builtin_clzll(n));
}

long long cal(long long r, long long p) {
    if (p <= 0) {
        return 0;
    }
    if (r == -1) {
        return 1;
    }
    long long k = calc(r + 1);
    long long q = (p - 1) % (1ll << k);
    if (q >= (1ll << (k - 1))) {
        return 0;
    }
    return cal(r - (1ll << (k - 1)), q + 1);
}

int main() {
    int n;
    scanf("%d", &n);
    while (n--) {
        long long r, p, ans = 0;
        scanf("%lld%lld", &r, &p);
        for (int i = 0; i < 60; ++i) {
            ans |= cal(r + (1ll << i) - 1, p - ((1ll << i) - 1)) << i;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
