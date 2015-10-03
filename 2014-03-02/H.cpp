#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 2 * 1000005;

int n;
int a[N], b[N];

int delta[N];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", a + i);
    }
    for (int i = 0; i < n; ++i) {
        scanf("%d", b + i);
    }
    sort(a, a + n);
    sort(b, b + n);
    int cur = 0;
    for (int i = 0; i < n; ++i) {
        if (b[i] > a[i]) {
            cur += 2;
            delta[i] -= 2;
        } else if (b[i] == a[i]) {
            cur += 1;
            int l = lower_bound(a, a + n, b[i]) - a;  
            if (l == 0) {
                delta[i] -= 1;
            } else {
                delta[i - l] += 1;
                delta[i] -= 2;
            }
        } else {
            int l = lower_bound(a, a + n, b[i]) - a, r = upper_bound(a, a + n, b[i]) - a;
            delta[i - l] += 1;
            delta[i - r] += 1;
            delta[i] -= 2;
        }
    } 
    int ans = cur;
    for (int i = 0; i < n; ++i) {
        cur += delta[i];
        ans = max(ans, cur);
    }
    printf("%d\n", ans);
    return 0;
}
