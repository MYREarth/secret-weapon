#include<queue>
#include<cstdio>
#include<climits>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 100000 + 5;
int n;

int top, head[N], to[N << 1], next[N << 1], cost[N << 1];

void addedge(int u, int v, int c) {
    to[top] = v, next[top] = head[u], cost[top] = c, head[u] = top++;
}

int dis[N], fa[N];

void bfs(int st) {
    for (int i = 0; i < n; ++i) {
        dis[i] = INT_MAX;
    }
    memset(fa, -1, sizeof(fa));
    queue<int> q; 
    q.push(st);
    dis[st] = 0;
    while (q.size()) {
        int u = q.front();
        q.pop();
        for (int j = head[u]; ~j; j = next[j]) {
            int v = to[j];
            if (dis[v] > dis[u] + 1) {
                dis[v] = dis[u] + 1;
                fa[v] = u;
                q.push(v);
            }
        } 
    }
}

bool mark[N];

int len[2][N], best[N][2];

void dfs(int u, int t, int fa) {
    best[u][0] = best[u][1] = 0;
    len[t][u] = 0;
    for (int j = head[u]; ~j; j = next[j]) {
        int v = to[j];
        if (v == fa) {
            continue;
        }
        dfs(v, t, u); 
        len[t][u] = max(len[t][u], len[t][v]);
        int tmp = best[v][0] + 1;
        if (tmp > best[u][0]) {
            best[u][1] = best[u][0];
            best[u][0] = tmp;
        } else if (tmp > best[u][1]) {
            best[u][1] = tmp;
        }
    }
    len[t][u] = max(len[t][u], best[u][0] + best[u][1]);
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        top = 0;
        memset(head, -1, sizeof(head));
        for (int i = 0; i < n - 1; ++i) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            --u, --v;
            addedge(u, v, w);
            addedge(v, u, w);
        }
        bfs(0);
        int p1 = 0, p2 = 0;
        for (int i = 0; i < n; ++i) {
            if (dis[i] > dis[p1]) {
                p1 = i;
            }
        }
        bfs(p1);
        for (int i = 0; i < n; ++i) {
            if (dis[i] > dis[p2]) {
                p2 = i;
            }
        }
        int p = p2, d = 0;
        memset(mark, 0, sizeof(mark));
        while (p != -1) {
            mark[p] = true;
            ++d;
            p = fa[p];
        }
        --d;
        dfs(p1, 0, -1);
        dfs(p2, 1, -1);
        int ans = INT_MAX, anst = 0;
        for (int u = 0; u < n; ++u) {
            for (int j = head[u]; ~j; j = next[j]) {
                int v = to[j], tmp;
                if (!mark[u] || !mark[v]) {
                    tmp = d * cost[j];
                } else {
                    tmp = min(max(len[0][u], len[1][v]), max(len[1][u], len[0][v])) * cost[j];
                }
                if (tmp < ans || tmp == ans && (j >> 1) < anst) {
                    ans = tmp;
                    anst = j >> 1;
                }
            }
        }
        static int id = 0;
        printf("Case #%d: %d\n", ++id, anst + 1);
    }
    return 0;
}
