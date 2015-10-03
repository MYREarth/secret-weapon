#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int n;

const int N = 100005;
vector<pair<int, int> > edge[N];

vector<pair<pair<int, int>, pair<int, int> > > evt;

const int LOG = 18;

int ans[N], fa[N][LOG], dep[N];

int cnt = 1, in[N], out[N];

void dfs(int u, int f = -1) {
    in[u] = cnt++;
    for (int j = 0; j < (int)edge[u].size(); ++j) {
        int v = edge[u][j].first, w = edge[u][j].second;
        if (v != f) {
            dep[v] = dep[u] + 1;
            fa[v][0] = u;
            evt.push_back(make_pair(make_pair(w, -1), make_pair(u, v)));
            dfs(v, u);
        }
    }
    out[u] = cnt++;
}

int lca(int u, int v) {
    if (dep[u] < dep[v]) {
        swap(u, v);
    }
    int l = dep[u] - dep[v];
    for (int j = 0; j < LOG; ++j) {
        if (l >> j & 1) {
            u = fa[u][j];
        }
    }
    if (u == v) {
        return u;
    }
    for (int j = LOG - 1; j >= 0; --j) {
        if (fa[u][j] != fa[v][j]) {
            u = fa[u][j];
            v = fa[v][j];
        }
    }
    return fa[u][0];
}

int tr[N << 1];

void add(int pos, int val) {
    while (pos < cnt) {
        tr[pos] += val;
        pos += pos & -pos;
    }
}

int ask(int pos) {
    int ret = 0;
    while (pos > 0) {
        ret += tr[pos];
        pos -= pos & -pos;
    }
    return ret;
}

int main() {
    memset(fa, -1, sizeof(fa));
    freopen("union.in", "r", stdin);
    freopen("union.out", "w", stdout);

    scanf("%d", &n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        --u, --v;
        edge[u].push_back(make_pair(v, w));
        edge[v].push_back(make_pair(u, w));
    }
    dfs(0);
    for (int i = 1; i < LOG; ++i) {
        for (int j = 0; j < n; ++j) {
            if (fa[j][i - 1] != -1) {
                fa[j][i] = fa[fa[j][i - 1]][i - 1];
            }
        }
    }
    int q;
    scanf("%d", &q);
    for (int i = 0; i < q; ++i) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        --u, --v;
        evt.push_back(make_pair(make_pair(w, i), make_pair(u, v)));
    }
    sort(evt.begin(), evt.end());
    for (int i = 0; i < (int)evt.size(); ++i) {
        int e = evt[i].first.second, u = evt[i].second.first, v = evt[i].second.second;
        if (e == -1) {
            add(in[v], 1);
            add(out[v], -1);
        } else {
            int w = lca(u, v);
            ans[e] = ask(in[u]) + ask(in[v]) - 2 * ask(in[w]);
        }
    }
    for (int i = 0; i < q; ++i) {
        printf("%d\n", ans[i]);
    }
    return 0;
}
