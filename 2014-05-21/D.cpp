#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 100005, LOG = 17;
int n;

int fa[N][LOG], dep[N];
vector<int> edge[N];

void dfs(int u) {
    for (int i = 0; i < (int)edge[u].size(); ++i) {
        int v = edge[u][i];
        if (v == fa[u][0]) {
            continue;
        }
        dep[v] = dep[u] + 1;
        fa[v][0] = u;
        dfs(v);
    }
}

int lca(int u, int v) {
    if (dep[u] < dep[v]) {
        swap(u, v);
    }
    for (int i = LOG - 1; i >= 0; --i) {
        if (dep[u] - dep[v] >> i & 1) {
            u = fa[u][i];
        }
    }
    if (u == v) {
        return u;
    }
    for (int i = LOG - 1; i >= 0; --i) {
        if (fa[u][i] != fa[v][i]) {
            u = fa[u][i];
            v = fa[v][i];
        }
    }
    return fa[u][0];
}

int main() {
    freopen("dynamic.in", "r", stdin);
    freopen("dynamic.out", "w", stdout);
    while (scanf("%d", &n) == 1 && n) {
        for (int i = 0; i < n; ++i) {
            edge[i].clear();
        }
        for (int i = 0; i < n - 1; ++i) {
            int u, v;
            scanf("%d%d", &u, &v);
            --u, --v;
            edge[u].push_back(v);
            edge[v].push_back(u);
        }
        int root = 0;
        dep[0] = 0;
        fa[0][0] = -1;
        dfs(0);
        for (int i = 1; i < LOG; ++i) {
            for (int j = 0; j < n; ++j) {
                if (fa[j][i - 1] == -1) {
                    fa[j][i] = -1;
                } else {
                    fa[j][i] = fa[fa[j][i - 1]][i - 1];
                }
            }
        }
        int q;
        scanf("%d", &q);
        while (q--) {
            char op[2];
            scanf("%s", op);
            if (op[0] == '?') {
                int u, v, fu, fv;
                scanf("%d%d", &u, &v);
                --u, --v;
                fu = lca(u, root), fv = lca(v, root);
                int ans;
                if (fu == root && fv == root) {
                    ans = lca(u, v);
                } else if (fu == root || fv == root) {
                    ans = root;
                } else if (fu == fv) {
                    ans = lca(u, v);
                } else {
                    ans = dep[fu] > dep[fv] ? fu : fv;
                }
                printf("%d\n", ans + 1);
            } else {
                int u;
                scanf("%d", &u);
                root = --u;
            }
        }
    }
    return 0;
}
