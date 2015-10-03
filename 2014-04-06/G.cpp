#include<queue>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int n, m;

const int N = 36, M = N * N;

int f[N][N], gold[N], u[M], v[M];;

bool inque[N], onpath[N];

vector<int> nxt[N];

int ans;

int top, head[N], to[M], nt[M];

int fa[N];

int find(int u) {
    return u == fa[u] ? u : fa[u] = find(fa[u]);
}

void merge(int u, int v) {
    if (u == v) {
        return;
    }
    fa[u] = v;
}

int appear[N][N], stamp;

void addedge(int u, int v) {
    if (appear[u][v] == stamp || u == v) {
        return;
    }
    appear[u][v] = stamp;
    to[top] = v, nt[top] = head[u], head[u] = top++;
}

const int INF = 200000000;

int dis[N];

void solve(int g) {
    for (int i = 0; i < n; ++i) {
        fa[i] = i;
    }
    for (int i = 0; i < m; ++i) {
        if (!onpath[u[i]] && !onpath[v[i]]) {
            merge(find(u[i]), find(v[i]));
        }
    }
    top = 0;
    memset(head, -1, sizeof(int) * n);
    ++stamp;
    for (int i = 0; i < m; ++i) {
        addedge(find(u[i]), find(v[i]));
        addedge(find(v[i]), find(u[i]));
    }
    priority_queue<pair<int, int> > heap;
    for (int i = 0; i < n; ++i) {
        if (find(i) == i) {
            dis[i] = INF;
        }
    }
    dis[0] = 0;
    heap.push(make_pair(0, 0));
    while (heap.size() && dis[1] > -heap.top().first) {
        int u = heap.top().second, d = -heap.top().first;
        heap.pop();
        if (d != dis[u]) {
            continue;
        }
        for (int j = head[u]; ~j; j = nt[j]) {
            int v = to[j];
            if (dis[v] > dis[u] + (onpath[v] * gold[v])) {
                dis[v] = dis[u] + (onpath[v] * gold[v]);
                heap.push(make_pair(-dis[v], v));
            }
        }
    }
    ans = max(ans, g - dis[1]);
}

int best[N];

void go(int u, int g) {
    if (g + best[u] <= ans) {
        return;
    }
    onpath[u] = true;
    if (u == 1) {
        solve(g);
        onpath[u] = false;
        return;
    }
    for (int j = 0; j < (int)nxt[u].size(); ++j) {
        go(nxt[u][j], g + gold[nxt[u][j]]);
    }
    onpath[u] = false;
}

bool bydis(int u, int v) {
    return f[u][1] < f[v][1];
}

int main() {
    while (scanf("%d%d", &n, &m) && (n || m)) {
        memset(f, 63, sizeof(f));
        for (int i = 0; i < n; ++i) {
            f[i][i] = 0;
        }
        for (int i = 2; i < n; ++i) {
            scanf("%d", gold + i);
        }
        for (int i = 0; i < m; ++i) {
            scanf("%d%d", u + i, v + i);
            --u[i], --v[i];
            f[u[i]][v[i]] = f[v[i]][u[i]] = 1;
        }
        for (int k = 0; k < n; ++k) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
                }
            }
        }
        for (int i = 0; i < n; ++i) {
            nxt[i].clear();
            inque[i] = (f[0][1] == f[0][i] + f[i][1]);
            if (inque[i]) {
                for (int j = 0; j < n; ++j) {
                    if (f[i][j] == 1 && f[j][1] == f[i][1] - 1) {
                        nxt[i].push_back(j);
                    }
                }
            }
        }
        int ord[N];
        for (int i = 0; i < n; ++i) {
            ord[i] = i;
        }
        sort(ord, ord + n, bydis);
        for (int i = 0; i < n; ++i) {
            int u = ord[i];
            if (inque[u]) {
                best[u] = 0;
                for (int j = 0; j < (int)nxt[u].size(); ++j) {
                    best[u] = max(best[u], best[nxt[u][j]] + gold[nxt[u][j]]);
                }
            }
        }
        ans = 0;
        go(0, 0);
        printf("%d\n", ans);
    }
    return 0;
}
