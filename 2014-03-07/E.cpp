#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 50005, M = N << 2;
int n, m;

int top, head[N], to[M], next[M];

void addedge(int u, int v) {
    to[top] = v, next[top] = head[u], head[u] = top++;
}

int ans, col[N];
bool vis[N];

void dye(int u) {
    vis[u] = true;
    bool use[3];
    memset(use, 0, sizeof(use));
    for (int j = head[u]; ~j; j = next[j]) {
        int v = to[j];
        if (vis[v]) {
            use[col[v]] = true;
        }
    }
    col[u] = 0;
    while (use[col[u]]) {
        ++col[u];
    }
    ans = max(ans, col[u] + 1);
    for (int j = head[u]; ~j; j = next[j]) {
        int v = to[j];
        if (!vis[v]) {
            dye(v);
        }
    }
}

int main() {
    freopen("coloring.in", "r", stdin);
    freopen("coloring.out", "w", stdout);
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    if (n == 1) {
        printf("1\n1\n");
        return 0;
    }
    for (int i = 0; i < m; ++i) {
        int k;
        scanf("%d", &k);
        int u;
        scanf("%d", &u);
        --u;
        for (int i = 1; i < k; ++i) {
            int v;
            scanf("%d", &v);
            --v;
            addedge(u, v);
            addedge(v, u);
            u = v;
        }
    }
    ans = 0;
    dye(0);
    printf("%d\n", ans);
    for (int i = 0; i < n; ++i) {
        printf("%d%c", col[i] + 1, i == n - 1 ? '\n' : ' ');
    }
    return 0;
}
