#include<cmath>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int main() {
    freopen("train.in", "r", stdin);
    freopen("train.out", "w", stdout);
    int n, m, f, l;
    while (scanf("%d%d%d%d", &n, &m, &f, &l) == 4 && n) {
        /*
        long double ans = 0, v0 = 0, M = m;
        for (int i = 0; i < n - 1; ++i) {
            long double a = f / M;
            long double t = (-v0 + sqrt(v0 * v0 + 2 * a * l)) / a;
            ans += t;
            long double vend = v0 + t * a;
            v0 = sqrt(M / (M + m)) * vend;
            M += m;
        }
        printf("%lld\n", (long long)ceil(ans));
        */
        long double ans;
        printf("%lld\n", (long long)ceil(ans = sqrt((long double)(n - 1) * l * n * m / f)));
    }
    return 0;
}
