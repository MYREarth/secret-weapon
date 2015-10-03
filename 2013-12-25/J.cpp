#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int n, m;

const int N = 500 + 5;
int top, head[N], next[N * N], to[N * N];

void addedge(int u, int v) {
    to[top] = v, next[top] = head[u], head[u] = top++;
}

int stamp;
int match[N], vis[N];

int find(int u) {
    if (vis[u] == stamp) {
        return false;
    }
    vis[u] = stamp;
    for (int j = head[u]; ~j; j = next[j]) {
        int v = to[j];
        if (match[v] == -1 || find(match[v])) {
            match[v] = u;
            return true;
        }
    }
    return false;
}

void matching() {
    memset(match, -1, sizeof(match));
    stamp = 0; 
    memset(vis, 0, sizeof(vis));
    for (int i = 0; i < n; ++i) {
        ++stamp;
        find(i);
    } 
}

int top2, head2[N << 1], to2[N * N * 2], next2[N * N * 2];

void addedge2(int u, int v) {
    to2[top2] = v, next2[top2] = head2[u], head2[u] = top2++;
}

bool used[N];

void build() {
    top2 = 0;
    memset(head2, -1, sizeof(head2));
    for (int u = 0; u < n; ++u) {
        for (int j = head[u]; ~j; j = next[j]) {
            int v = to[j];
            if (match[v] == u) {
                addedge2(v + n, u);
                addedge2(u, v + n);
            } else {
                addedge2(u, v + n);
                addedge2(v + n, u);
            }
        } 
    }
    memset(used, 0, sizeof(used));
    int p1 = n + m, p2 = n + m + 1;
    for (int u = 0; u < m; ++u) {
        if (match[u] == -1) {
            addedge2(u + n, p2);
            addedge2(p2, u + n);
        } else {
            used[match[u]] = true;
            addedge2(p2, u + n);
            addedge2(u + n, p2);
        }
    }
    for (int u = 0; u < n; ++u) {
        if (used[u]) {
            addedge2(u, p1);
            addedge2(p1, u);
        } else {
            addedge2(p1, u);
            addedge2(u, p1);
        }
    }
}

vector<int> ord;

bool vis2[N << 1];

void dfs(int u) {
    vis2[u] = true;
    for (int j = head2[u]; ~j; j = next2[j]) {
        if (j & 1) {
            continue;
        }
        int v = to2[j];
        if (!vis2[v]) {
            dfs(v);
        }
    }
    ord.push_back(u);
}

int cnt, col[N << 1];

void dfs2(int u) {
    col[u] = cnt;
    for (int j = head2[u]; ~j; j = next2[j]) {
        if (~j & 1) {
            continue;
        }
        int v = to2[j];
        if (col[v] == -1) {
            dfs2(v);
        }
    }
}

void restrain() {
    ord.clear();
    memset(vis2, 0, sizeof(vis2)); 
    for (int i = 0; i < n + m + 2; ++i) {
        if (!vis2[i]) {
            dfs(i);
        }
    }
    memset(col, -1, sizeof(col));
    cnt = 0;
    for (int i = n + m + 1; i >= 0; --i) {
        int u = ord[i];
        if (col[u] == -1) {
            ++cnt;
            dfs2(u);
        }
    }
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        static int id = 0;
        printf("Case #%d:\n", ++id);
        scanf("%d%d", &n, &m);
        top = 0;
        memset(head, -1, sizeof(head));
        for (int i = 0; i < n; ++i) {
            int k;
            scanf("%d", &k);
            for (int j = 0; j < k; ++j) {
                int u;
                scanf("%d", &u);
                --u;
                addedge(i, u);
            }
        }
        matching(); 
        build();
        restrain();
        for (int i = 0; i < n; ++i) {
            vector<int> ans;            
            for (int j = head[i]; ~j; j = next[j]) {
                int v = to[j];
                if (col[i] == col[n + v] || match[v] == i) {
                    ans.push_back(v);
                } 
            }
            sort(ans.begin(), ans.end());
            ans.erase(unique(ans.begin(), ans.end()), ans.end());
            printf("%d%c", ans.size(), " \n"[ans.size() == 0]);
            for (int j = 0; j < (int)ans.size(); ++j) {
                printf("%d%c", ans[j] + 1, " \n"[j == ans.size() - 1]);
            }
        }
    }
    return 0;
}
