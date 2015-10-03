#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int MOD = 1000000007;

const int N = 200005;

int f[N], rev[N];

int reverse(int a) {
    return a == 1 ? 1 : (long long)(MOD - MOD / a) * reverse(MOD % a) % MOD;
}

int cb(int n, int m) {
    return (long long)f[n] * rev[m] % MOD * rev[n - m] % MOD;
}

int fa[N], size[N], cnt[N];

int find(int u) {
    return u == fa[u] ? u : fa[u] = find(fa[u]);
}

void merge(int u, int v) {
    if (size[u] > size[v]) {
        fa[v] = u;
        size[u] += size[v];
    } else {
        fa[u] = v;
        size[v] += size[u];
    }
}

int main() {
    f[0] = 1;
    rev[0] = 1;
    for (int i = 1; i < N; ++i) {
        f[i] = (long long)f[i - 1] * i % MOD;
        rev[i] = reverse(f[i]);
    }
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 0; i <= n; ++i) {
        cnt[i] = cb(i + k - 1, i);
    }
    int ans = 1;
    for (int i = 0; i < n; ++i) {
        fa[i] = i;
        size[i] = 1;
        ans = (long long)ans * cnt[1] % MOD;
    }
    printf("%d\n", ans);
    int m;
    scanf("%d", &m);
    for (int i = 0; i < m; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        --u, --v;
        if (find(u) != find(v)) {
            ans = (long long)ans * reverse(cnt[size[find(u)]]) % MOD;
            ans = (long long)ans * reverse(cnt[size[find(v)]]) % MOD;
            merge(find(u), find(v));
            ans = (long long)ans * cnt[size[find(u)]] % MOD;
        }
        printf("%d\n", ans);
    }
    return 0;
}
