#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 2 * 100005;
int n, m;
vector<int> col[N];

vector<int> edge[N];

void addedge(int u, int v) {
    edge[u].push_back(v);
}

int ans, dep[N];
bool vis[N], block[N];

vector<int> rch[N];

bool by_dep(int u, int v) {
    return dep[u] > dep[v];
}

bool cycle;

void dfs(int u) {
    vis[u] = true;
    for (int i = 0; i < (int)edge[u].size(); ++i) {
        int v = edge[u][i];
        if (!vis[v]) {
            ++ans;
            dep[v] = dep[u] + 1;
            dfs(v);
        } else if (dep[v] < dep[u]) {
            continue;
        } else if (dep[v] > dep[u]) {
            if (block[u] || ((dep[v] - dep[u]) % 2) == 1) {
                continue;
            }
            if (!cycle) {
                cycle = true;
                ++ans;
            }
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m * 2; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        --x, --y;
        col[y].push_back(x);
    }
    for (int i = 0; i < m; ++i) {
        int u = col[i][0], v = col[i][1];
        addedge(u, v);
        addedge(v, u);
    }
    ans = 0;
    for (int i = 0; i < n; ++i) {
        if (!vis[i]) {
            dep[i] = 0;
            cycle = false;
            dfs(i);
        }
    }
    printf("%d\n", ans);
    return 0;
}
