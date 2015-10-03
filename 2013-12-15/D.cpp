#include<queue>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 2 * 100000;
int n, m, top, head[N], to[N], next[N];

void addedge(int u, int v) {
    to[top] = v, next[top] = head[u], head[u] = top++;
}

int dep[N];

void bfs() {
    for (int i = 0; i < n; ++i) {
        dep[i] = n + 1;
    }
    dep[0] = 0;
    queue<int> q;
    q.push(0);
    while (q.size()) {
        int u = q.front();
        q.pop();
        for (int j = head[u]; ~j; j = next[j]) {
            int v = to[j];
            if (dep[v] > dep[u] + 1) {
                dep[v] = dep[u] + 1;
                q.push(v);
            }
        }
    }
}

vector<int> belong[N];
int mins[N];

bool cmp(int u, int v) {
    return dep[mins[u]] > dep[mins[v]];
}

bool vis[N];

int main() {
    freopen("garlands.in", "r", stdin);
    freopen("garlands.out", "w", stdout);
    top = 0;
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 0; i < n - 1; ++i) {
        int u;
        scanf("%d", &u);
        --u;
        addedge(i + 1, u);
        addedge(u, i + 1);
    }
    bfs();
    scanf("%d", &m);
    vector<int> block;
    for (int i = 0; i < m; ++i) {
        block.push_back(i);
        mins[i] = n + 1;
        int ki;
        scanf("%d", &ki);
        for (int j = 0; j < ki; ++j) {
            int u;
            scanf("%d", &u);
            --u;
            belong[u].push_back(i);
            if (mins[i] == n + 1) {
                mins[i] = u;
            } else {
                if (dep[mins[i]] > dep[u]) {
                    mins[i] = u;
                }
            }
        }
    }
    sort(block.begin(), block.end(), cmp);
    int ans = 0;
    vector<int> col;
    for (int i = 0; i < m; ++i) {
        if (!vis[block[i]]) {
            ++ans;
            int u = mins[block[i]];
            col.push_back(u + 1);
            for (int j = 0; j < (int)belong[u].size(); ++j) {
                vis[belong[u][j]] = true;
            }
        } 
    }
    printf("%d\n", ans);
    sort(col.begin(), col.end());
    for (int i = 0; i < ans; ++i) {
        printf("%d%c", col[i], " \n"[i == ans - 1]);
    }
    return 0;
}
