#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 100005;

int ans[N], a[N], b[N];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d%d", a + i, b + i);
        ans[i] = 1;
        for (int j = 0; j < i; ++j) {
            if (a[j] < a[i] && b[j] < b[i]) {
                ans[i] = max(ans[i], ans[j] + 1);
            }
        }
cout << a[i] << ' ' << b[i] << ' ' << ans[i] << endl;
    }
    int out = 0;
    for (int i = 0; i < n; ++i) {
        out = max(out, ans[i]);
    }
    printf("%d\n", out);
    return 0;
}
