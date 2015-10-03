#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 105;

int n;
int g[N], p[N], ord[N];

bool cmp(int i, int j) {
    return g[i] * p[j] < g[j] * p[i];
}

int main() {
    freopen("monsters.in", "r", stdin);
    freopen("monsters.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d%d", g + i, p + i);
        ord[i] = i;
    }
    sort(ord, ord + n, cmp);
    long long ans = 0, t = 0;
    for (int i = 0; i < n; ++i) {
        int u = ord[i];
        t += g[u];
        ans += t * p[u];
    }
    cout << ans << endl;
    for (int i = 0; i < n; ++i) {
        printf("%d%c", ord[i] + 1, i == n - 1 ? '\n' : ' ');
    }
    return 0;
}
