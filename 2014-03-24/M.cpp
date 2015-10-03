#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 100005 << 1;

int n;
const long long L = 10000000;
long long a[N], sum[N];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%lld", a + i);
    }
    sort(a, a + n);
    for (int i = n; i < n * 2; ++i) {
        a[i] = a[i - n] + L;
    }
    for (int i = 0; i < n * 2; ++i) {
        sum[i + 1] = sum[i] + a[i];
    }
    long long ans = 1ll << 62;
    for (int i = 0; i < n; ++i) {
        long long cost = 0, l = i, m = i + n / 2, r = i + n - 1;
        cost = sum[r + 1] - sum[m + 1] - sum[m + 1] + sum[l] - (n - (n / 2 + 1)) * a[m] + (n / 2 + 1) * a[m];
        //cout << i << ' ' << cost << endl;
        ans = min(ans, cost);
    }
    cout << ans << endl;
    return 0;
}
