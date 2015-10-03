#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

unsigned long long MASK = (1ll << 42) - 1, P = 1ll << 21;

int main() {
    freopen("fact.in", "r", stdin);
    freopen("fact.out", "w", stdout);
    unsigned long long pa = 0, pb = 1, npa, npb, q;
    for (int i = 0; i < P; ++i) {
        q = i * 2 + 1;
        npa = pa * q + pb;
        npb = pb * q;
        pa = npa, pb = npb;
    }
    unsigned long long n;
    scanf("%lld", &n);
    unsigned long long l = n >> 21, last = l << 21, nn = n - last;

    unsigned long long ca = 0, cb = 1, nca, ncb;
    for (int i = 0; i < l; ++i) {
        npa = pa * i, npb = pb;
        nca = npb * ca + npa * cb;
        ncb = npb * cb;
        ca = nca, cb = ncb;
    }
    unsigned long long mul = (ca << 22) + cb;
    for (int i = 0; i < nn; ++i) {
        unsigned long long cur = (last + i) * 2 + 1;
        mul *= cur;
    }
    printf("%lld\n", mul & MASK);
    return 0;
}
