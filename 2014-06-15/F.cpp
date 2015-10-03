#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 1000005;

int n, k;

int a[N];

bool check(int l) {
    int range = 0, i = 0, cnt = 0;
    while (i + 1 < 2 * n * k && i <= range && cnt <= n) {
        if (a[i + 1] - a[i] <= l) {
            range += 2 * k;
            i += 2;
            ++cnt;
        } else {
            ++i;
        }
    }
    return cnt >= n;
}

int main() {
    scanf("%d%d", &n, &k);
    int m = 2 * n * k;
    for (int i = 0; i < m; ++i) {
        scanf("%d", a + i);
    }
    sort(a, a + m);
    int l = a[1] - a[0], r = a[m - 1] - a[0];
    while (l < r) {
        int m = l + r >> 1;
        if (check(m)) {
            r = m;
        } else {
            l = m + 1;
        }
    }
    printf("%d\n", l);
    return 0;
}
