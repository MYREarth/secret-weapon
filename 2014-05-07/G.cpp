#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int main() {
    long long h, l, w, a, b, c, d;
    scanf("%lld%lld%lld", &h, &l, &w);
    if ((w + l - 4 * h) % 4 != 0) {
        printf("impossible\n");
        return 0;
    }
    long long lb = max(0ll, (w + l - 4 * h) / 4), ub = min(w, (l - w) / 2);
    if (lb > ub) {
        printf("impossible\n");
        return 0;
    }
    for (a = lb; a <= lb + 10 && a <= ub; ++a) {
        b = a - (w + l - 4 * h) / 4;
        c = (w - a) / 2;
        d = (l - w - 2 * a) / 4;
        if (a >= 0 && b >= 0 && c >= 0 && d >= 0 && b + c + d == h && 3 * a + 2 * c + 4 * d == l && a + 2 * c == w) {
            printf("%lld %lld %lld %lld\n", a, b, c, d);
            return 0;
        }
    }
    printf("impossible\n");
    return 0;
}
