#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int main() {
    long long n, k, ans;
    scanf("%lld%lld", &n, &k);
    if (k > n) {
        printf("%lld\n", n);
        return 0;
    } else {
        ans = n * n;
    }
    for (long long l = n + 2 - k; l <= n; ++l) {
        long long d = k - (n - l), tmp = l + n;
        long long s = l - d;
        tmp += s * l;
        ans = min(ans, tmp);
    }
    printf("%lld\n", ans);
    return 0;
}
