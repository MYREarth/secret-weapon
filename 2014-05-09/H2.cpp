#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

long long solve(long long r, long long p) {
    if (p <= 0) {
        return 0;
    }
    if (r == 0) {
        return p;
    }
    long long ret = p;
    for (int i = 0; (r >> i) && (p >> i) > 0; ++i) {
        if (r >> i & 1) {
            ret ^= solve(r & ((1ll << i) - 1), p - (1ll << i));
        }
    }
    return ret;
}

int main() {
    int n;
    scanf("%d", &n);
    while (n--) {
        long long r, p;
        scanf("%lld%lld", &r, &p);
        printf("%lld\n", solve(r, p));
    }
    return 0;
}
