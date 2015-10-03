#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 20005, M = 100005 << 1;
int n, m;
int top, head[N], to[M], next[M];

int dgr[N], dep[N], low[N];

void addedge(int u, int v) {
    to[top] = v, next[top] = head[u], head[u] = top++;
}

vector<vector<int> > ans;

bool vis[N];

bool solve(int u, int fa_edge) {
//cout << "IN" << ' ' << u + 1 << ' ' << ans.size() << endl;
    bool flag = true;
    vis[u] = true;
    low[u] = dep[u] + 1;
    int best = -1, lowest = -1;
    for (int j = head[u]; ~j && flag; j = next[j]) {
        if ((j >> 1) == (fa_edge >> 1)) {
            continue;
        }
        int v = to[j];
        if (!vis[v]) {
            dep[v] = dep[u] + 1;
            flag = solve(v, j);
        }
        low[u] = min(low[u], min(dep[v], low[v]));
        if (dep[v] < dep[u]) {
            if (best == -1) {
                lowest = dep[v];
                best = j;
            } else {
                if (lowest > dep[v]) {
                    vector<int> cut;
                    cut.push_back(u), cut.push_back(to[best]);
                    --dgr[u], --dgr[to[best]];
                    ans.push_back(cut);
                    best = j;
                    lowest = dep[v];
                } else {
                    vector<int> cut;
                    cut.push_back(u), cut.push_back(v);
                    --dgr[u], --dgr[v];
                    ans.push_back(cut);
                }
            }
        }
    }
//cout << u + 1 << ' ' << low[u] << ' ' << dep[u] + 1 << endl;
    if (!flag || low[u] == dep[u] + 1) {
        return false;
    }
    int fa = to[fa_edge ^ 1];
    if (dgr[u] == 0) {
    } else if (dgr[u] == 1) {
        ans.back().push_back(fa);
        --dgr[u], --dgr[fa];
    } else {
        vector<int> cut;
        cut.push_back(to[best]), cut.push_back(u), cut.push_back(fa);
        --dgr[to[best]], --dgr[fa], --dgr[u], --dgr[u];
        ans.push_back(cut);
    }
//cout << "OUT" << ' ' << u + 1 << ' ' << ans.size() << endl;
    return true;
}

int main() {
    //freopen("ear.in", "r", stdin);
    //freopen("ear.out", "w", stdout);
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        --u, --v;
        ++dgr[u], ++dgr[v];
        addedge(u, v);
        addedge(v, u);
    }
    if (solve(0, -1)) {
        printf("%d\n", ans.size());
        for (int i = 0; i < (int)ans.size(); ++i) {
            printf("%d", ans[i].size() - 1);
            for (int j = 0; j < (int)ans[i].size(); ++j) {
                printf(" %d", ans[i][j] + 1);
            }
            printf("\n");
        }
    } else {
        printf("-1\n");
    }
    return 0;
}
