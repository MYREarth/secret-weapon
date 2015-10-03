#include<bitset>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int t;

int n, k;

const int N = 900;
char buf[N];

vector<int> edge[N];

int stamp, vis[N];

int match[N];

bool find(int u) {
    if (vis[u] == stamp) {
        return false;
    }
    vis[u] = stamp;
    for (int j = 0; j < (int)edge[u].size(); ++j) {
        int v = edge[u][j];
        if (match[v] == -1 || find(match[v])) {
            match[v] = u;
            return true;
        }
    }
    return false;
}

vector<int> edge1[N], edge2[N];

int cnt_col, col[N];

vector<int> ord;

bool vis1[N], vis2[N];

void dfs1(int u) {
    vis1[u] = true;
    for (int i = 0; i < (int)edge1[u].size(); ++i) {
        int v = edge1[u][i];
        if (!vis1[v]) {
            dfs1(v);
        }
    }
    ord.push_back(u);
}

void dfs2(int u) {
    vis2[u] = true;
    col[u] = cnt_col;
    for (int i = 0; i < (int)edge2[u].size(); ++i) {
        int v = edge2[u][i];
        if (!vis2[v]) {
            dfs2(v);
        }
    }
}

void paint (vector<pair<int, int> > e) {
    for (int i = 0; i < n * 2; ++i) {
        edge1[i].clear();
        edge2[i].clear();
    }
    for (int i = 0; i < (int)e.size(); ++i) {
        int u = e[i].first, v = e[i].second;
        edge1[u].push_back(v);
        edge2[v].push_back(u);
    }
    cnt_col = 0;
    for (int i = 0; i < n * 2; ++i) {
        vis1[i] = false;
        vis2[i] = false;
        col[i] = -1;
    }
    ord.clear();
    for (int i = 0; i < n * 2; ++i) {
        if (!vis1[i]) {
            dfs1(i);
        }
    }
    reverse(ord.begin(), ord.end());
    for (int i = 0; i < n * 2; ++i) {
        if (!vis2[ord[i]]) {
            dfs2(ord[i]);
            ++cnt_col;
        }
    }
}

vector<int> out[N];
bitset<N> reach[N];

bool caled[N];

void cal(int u) {
    caled[u] = true;
    for (int j = 0; j < (int)out[u].size(); ++j) {
        int v = out[u][j];
        if (reach[u][v]) {
            continue;
        }
        if (!caled[v]) {
            cal(v);
        }
        reach[u] |= reach[v];
    }
}

bool check(vector<pair<int, int> > e, bitset<N> important, int n) {
    if (!important.any()) {
        return true;
    }
    for (int i = 0; i < n; ++i) {
        caled[i] = false;
        out[i].clear();
        reach[i].reset();
        reach[i][i] = true;
    }
    for (int i = 0; i < (int)e.size(); ++i) {
        out[e[i].first].push_back(e[i].second);
    }
    for (int i = 0; i < n; ++i) {
        if (!caled[i]) {
            cal(i);
        }
    }
    bool find = false;
    for (int i = 0; i < n && !find; ++i) {
        find = (reach[i] & important) == important;
    }
    if (!find) {
        return false;
    }
    bitset<N> end;
    for (int i = 0; i < n; ++i) {
        end[i] = true;
    }
    for (int i = 0; i < n; ++i) {
        if (important[i]) {
            end = end & reach[i];
        }
    }
    return end.any();
}

int main() {
    //freopen("holygame.in", "r", stdin);
    //freopen("holygame.out", "w", stdout);
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &k);
        for (int i = 0; i < n; ++i) {
            edge[i].clear();
        }
        for (int i = 0; i < n; ++i) {
            scanf("%s", buf);
            for (int j = 0; j < n; ++j) {
                if (buf[j] == '1') {
                    edge[i].push_back(j);
                }
            }
        }
        for (int i = 0; i < n; ++i) {
            match[i] = -1;
        }
        int cnt = 0;
        for (int i = 0; i < n; ++i) {
            ++stamp;
            cnt += find(i);
        }
        if (k == 0) {
            if (cnt == n) {
                printf("Angel Angel\n");
            } else {
                printf("Demon Demon\n");
            }
        } else {
            vector<pair<int, int> > e;
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < (int)edge[i].size(); ++j) {
                    int u = i, v = edge[i][j] + n;
                    if (match[edge[i][j]] == i) {
                        e.push_back(make_pair(v, u));
                    } else {
                        e.push_back(make_pair(u, v));
                    }
                }
            }
            if (cnt == n) {
                paint(e);
                bitset<N> important;
                for (int i = 0; i < n; ++i) {
                    if (match[i] == -1) {
                        continue;
                    }
                    int u = match[i], v = i + n;
                    if (col[u] != col[v]) {
                        important.set(col[u]);
                        important.set(col[v]);
                    }
                }
                vector<pair<int, int> > e2;
                for (int i = 0; i < (int)e.size(); ++i) {
                    int u = col[e[i].first], v = col[e[i].second];
                    if (u != v) {
                        e2.push_back(make_pair(u, v));
                    }
                }
                if (check(e2, important, cnt_col)) {
                    printf("Angel Angel\n");
                } else {
                    printf("Demon Angel\n");
                }
            } else {
                if (cnt < n - 1) {
                    printf("Demon Demon\n");
                } else {
                    paint(e);
                    bool flag = false;
                    for (int i = 0; i < n; ++i) {
                        if (match[i] == -1) {
                            continue;
                        }
                        flag = flag || col[i + n] != col[match[i]];
                    }
                    if (flag) {
                        printf("Demon Demon\n");
                    } else {
                        printf("Demon Angel\n");
                    }
                }
            }
        }
    }
    return 0;
}
