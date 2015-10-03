#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 1505;

int n, cnt[N], pa, pb, len;
vector<int> edge[N];

int dep[N], fa[N];

bool onpath[N];

void dfs(int u) {
    for (int j = 0; j < (int)edge[u].size(); ++j) {
        int v = edge[u][j];
        if (v == fa[u]) {
            continue;
        }
        fa[v] = u;
        dep[v] = dep[u] + 1;
        dfs(v);
    }
}

int t[N], best[N];

void dp(int u) {
    if (cnt[u] == 0) {
        return;
    }
    t[u] = min(t[fa[u]] + max(1, cnt[u] - onpath[u]), dep[u] + len);
    best[u] = ((cnt[u] - onpath[u]) > 0 ? t[u] - t[fa[u]] : 0) + onpath[u] + best[fa[u]];
    for (int i = 0; i < (int)edge[u].size(); ++i) {
        int v = edge[u][i];
        if (v == fa[u]) {
            continue;
        }
        dp(v);
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        --u, --v;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    for (int i = 0; i < n; ++i) {
        scanf("%d", cnt + i);
    }
    scanf("%d%d", &pa, &pb);
    --pa, --pb;
    int ans = 0;
    for (int x = 0; x < n; ++x) {
        if (cnt[x] == 0 || x == pa) {
            continue;
        }
        dep[x] = 0;
        fa[x] = -1;
        dfs(x);
        if (dep[pa] < dep[pb]) {
            continue;
        }
//cout << dep[pa] << ' ' << dep[pb] << endl;
        for (int i = 0; i < n; ++i) {
            onpath[i] = false;
            best[i] = 0;
        }
        int tmp = pb;
        while (tmp != x) {
            tmp = fa[tmp];
            onpath[tmp] = true;
        }
        onpath[x] = true;
        if (dep[pa] > dep[pb]) {
            if (pb == x) {
                len = dep[pa] - 1;
            } else {
                len = dep[pa] - dep[pb];
            }
        } else {
            len = 0;
        }
        t[x] = min(len, cnt[x] - onpath[x]);
        best[x] = t[x] + onpath[x];
        for (int i = 0; i < (int)edge[x].size(); ++i) {
            dp(edge[x][i]);
        }
        for (int i = 0; i < n; ++i) {
            ans = max(ans, best[i]);
        }
        /*
cout << "X" << ' ' << x << ' ' << endl;
for (int i = 0; i < n; ++i) {
    cout << t[i] << ' ' << best[i] << endl;
}**/
    }
    printf("%d\n", ans);
    return 0;
}
