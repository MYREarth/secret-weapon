#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 1005, M = N * N << 1;
int top, head[N], to[M], next[M];

void addedge(int u, int v) {
    to[top] = v, next[top] = head[u], head[u] = top++;
}

int n, m;

int dep[N], low[N];
bool vis[N];

void dfs(int u, int fa) {
    vis[u] = true;
    low[u] = dep[u];
    for (int j = head[u]; ~j; j = next[j]) {
        int v = to[j];
        if (v == fa) {
            continue;
        }
        if (vis[v]) {
            if (dep[v] < dep[u]) {
                printf("%d %d\n", u + 1, v + 1);
                low[u] = min(low[u], dep[v]);
            }
        } else {
            printf("%d %d\n", u + 1, v + 1);
            dep[v] = dep[u] + 1;
            dfs(v, u);
            low[u] = min(low[u], low[v]);
        }
    }
    //cout << u << ' ' << low[u] << ' ' << dep[u] << endl;
    if (low[u] == dep[u] && fa != -1) {
        printf("%d %d\n", u + 1, fa + 1);
    }
}

int main() {
    while (scanf("%d%d", &n, &m) == 2 && (n || m)) {
        top = 0;
        memset(head, -1, sizeof(head));
        for (int i = 0; i < m; ++i) {
            int u, v;
            scanf("%d%d", &u, &v);
            --u, --v;
            addedge(u, v);
            addedge(v, u);
        }
        memset(vis, 0, sizeof(vis));
        memset(dep, 0, sizeof(dep));
        memset(low, 0, sizeof(low));
        static int id = 0;
        printf("%d\n\n", ++id);
        for (int i = 0; i < n; ++i) {
            if (!vis[i]) {
                dfs(i, -1);
            }
        }
        printf("#\n");
    }
    return 0;
}
