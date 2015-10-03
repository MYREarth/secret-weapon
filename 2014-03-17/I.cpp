#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 100005;
int n, m, k;
int w[N], sum[N], drop[N];

int main() {
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 0; i < n; ++i) {
        scanf("%d", w + i);
        sum[i + 1] = sum[i] + w[i];
    }
    int last = 0;
    for (int i = 1; i <= n; ++i) {
        while (sum[i] - sum[last] > k) {
            ++last;
        }
        drop[i] = max(0, last - 1);
    }
    int cur = 0, i = 0;
    while (m--) {
        int t;
        scanf("%d", &t);
        if (t > cur + n - i) {
            printf("%d\n", cur + n - i);
            return 0;
        }
        i += t - cur - 1;
        i = drop[i];
        cur = t;
    }
    printf("%d\n", cur + n - i);
    return 0;
}
