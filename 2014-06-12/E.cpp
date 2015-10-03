#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 1000005;

int a[N];
long long f[N];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", a + 1 + i);
    }
    f[0] = 0;
    for (int i = 1; i <= n; ++i) {
        f[i] = max(f[i - 1], f[i - 2] + a[i]);
    }
    printf("%lld\n", f[n]);
    return 0;
}
