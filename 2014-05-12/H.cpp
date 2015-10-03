#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int main() {
    int n;
    scanf("%d", &n);
    while (n--) {
        long long k, a, b, m;
        scanf("%lld%lld", &k, &m);
        --m;
        while ((1ll << k) <= m) {
            m -= 1ll << k;
            ++k;
        }
        a = 1, b = 0;
        for (long long i = k; i >= 0; --i) {
            if (m >> i & 1) {
                long long nk, na, nb;
                na = (k - i + 1) * a - b, nb = a;
                nk = i + nb / na;
                nb %= na;
                long long g = __gcd(nb, na);
                na /= g, nb /= g;
                k = nk, a = na, b = nb;
            }
        }
        printf("%.12f\n", k + (double)b / a);
    }
    return 0;
}
