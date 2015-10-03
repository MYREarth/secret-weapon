#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int main() {
    long long n, k;
    scanf("%lld%lld", &n, &k);
    long long ans = n, c = n + 2 - k;
    if (c > 0) {
        ans += c * (c - 1);
    }
    printf("%lld\n", ans);
    return 0;
}
