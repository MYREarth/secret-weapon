#include<map>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 750000;
int n, k;
vector<int> edge[N];

map<int, int> *cur;
vector<int> len;
long long cal = 0;

int stamp, vis[N];
bool used[N];

int fa[N], size[N], mch[N];

int dep;

void dfs (int u, int fa) {
    ++dep;
    len.push_back(dep);
    cal += (*cur)[k - dep];
    for (int i = 0; i < (int)edge[u].size(); ++i) {
        int v = edge[u][i];
        if (v == fa || used[v]) {
            continue;
        }
        dfs(v, u);
    }
    --dep;
}

void solve(int u) {
    ++stamp;
    vector<int> q;
    fa[u] = -1, size[u] = 0, mch[u] = 0;
    q.push_back(u), vis[u] = ++stamp;
    for (int i = 0; i < (int)q.size(); ++i) {
        int u = q[i];
        for (int j = 0; j < (int)edge[u].size(); ++j) {
            int v = edge[u][j];
            if (!used[v] && vis[v] != stamp) {
                fa[v] = u, size[v] = 0, mch[v] = 0;
                vis[v] = stamp;
                q.push_back(v);
            }
        }
    }
    for (int i = q.size() - 1; i >= 0; --i) {
        int u = q[i];
        ++size[u];
        mch[u] = max(mch[u], (int)q.size() - size[u]);
        if (fa[u] != -1) {
            mch[fa[u]] = max(mch[fa[u]], size[u]);
            size[fa[u]] += size[u];
        }
    }
    int root = u;
    for (int i = 0; i < (int)q.size(); ++i) {
        int u = q[i];
        if (mch[u] < mch[root]) {
            root = u;
        }
    }
    map<int, int> cnt;
    cnt[0] = 1;
    cur = &cnt;
    used[root] = true;
    for (int i = 0; i < (int)edge[root].size(); ++i) {
        int v = edge[root][i];
        if (!used[v]) {
            len.clear();
            dfs(v, root);
            for (int j = 0; j < (int)len.size(); ++j) {
                ++cnt[len[j]];
            }
        }
    }
    for (int i = 0; i < (int)edge[root].size(); ++i) {
        int v = edge[root][i];
        if (!used[v]) {
            solve(v);
        }
    }
}

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        --u, --v;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    solve(0);
    printf("%lld\n", cal);
    return 0;
}

