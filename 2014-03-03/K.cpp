#include<queue>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 2005;
int n, match[N];
vector<int> b[N];

vector<pair<int, int> > pr[N][2];

vector<pair<int, int> > make(int i, int c) {
    vector<pair<int, int> > ret(2);
    if (c == 0) {
        ret[0] = make_pair(b[i][0], b[i][1]);
        ret[1] = make_pair(b[i][2], b[i][3]);
    } else {
        ret[0] = make_pair(b[i][0], b[i][2]);
        ret[1] = make_pair(b[i][1], b[i][3]);
    }
    return ret;
}

bool check(int i, int c1, int j, int c2) {
    vector<pair<int, int> > &pi = pr[i][c1], &pj = pr[j][c2];  
    for (int a = 0; a < 2; ++a) {
        for (int b = 0; b < 2; ++b) {
            if (pi[a].first < pj[b].first && pj[b].second < pi[a].second) {
                return false;
            }
            if (pj[b].first < pi[a].first && pi[a].second < pj[b].second) {
                return false;
            }
        }
    }
    return true;
}

bool g[N][N];

void addedge(int i, int j) {
    g[i][j] = true;
    g[j ^ 1][i ^ 1] = true;
}

bool vis[N];
int top, cnt, ord[N], col[N];

void dfs(int u, int n) {
    vis[u] = true;
    ord[top++] = u;
    for (int i = 0; i < n; ++i) {
        if (!vis[i] && g[u][i]) {
            dfs(i, n);
        }
    }
}

void dfs2(int u, int n) {
    col[u] = cnt;
    for (int i = 0; i < n; ++i) {
        if (!col[i] && g[i][u]) {
            dfs2(i, n);
        }
    }
}

vector<int> solve(int n) {
    memset(vis, 0, sizeof(bool) * n * 2);
    top = 0;
    for (int i = 0; i < n * 2; ++i) {
        if (!vis[i]) {
            dfs(i, n * 2);
        }
    }
    cnt = 0;
    for (int i = n * 2 - 1; i >= 0; --i) {
        if (!col[ord[i]]) {
            ++cnt;
            dfs2(ord[i], n * 2);
        }
    }
    vector<int> ret;
    for (int i = 0; i < n; ++i) {
        if (col[i << 1] > col[i << 1 | 1]) {
            ret.push_back(i << 1);
        } else {
            ret.push_back(i << 1 | 1);
        }
    }
    return ret;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for (int i = 0; i < n; ++i) {
            int a;
            scanf("%d", &a);
            b[a].push_back(i);
        }
        queue<pair<int, int> > q;
        for (int i = 0; i <= n; ++i) {
            if (b[i].size() == 2) {
                q.push(make_pair(b[i][0], b[i][1]));
                b[i].clear();
            }
        }
        while (q.size()) {
            int u = q.front().first, v = q.front().second;
            match[u] = v; match[v] = -1;
            q.pop();
            for (int j = 0; j <= n; ++j) {
                if (b[j].size() == 4) {
                    if (u < b[j][0] && b[j][1] < v || u < b[j][2] && b[j][3] < v) {
                        q.push(make_pair(b[j][0], b[j][2]));
                        q.push(make_pair(b[j][1], b[j][3]));
                        b[j].clear();
                    } else if (b[j][0] < u && v < b[j][2] || b[j][1] < u && v < b[j][3]) {
                        q.push(make_pair(b[j][0], b[j][1]));
                        q.push(make_pair(b[j][2], b[j][3]));
                        b[j].clear();
                    }
                }
            }
        }
        vector<int> left;
        for (int i = 0; i <= n; ++i) {
            if (b[i].size() > 0) {
                left.push_back(i);
            }
        }
        int m = left.size();
        for (int i = 0; i < m * 2; ++i) {
            for (int j = 0; j < m * 2; ++j) {
                g[i][j] = false;
            }
        }
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < 2; ++j) {
                pr[left[i]][j] = make(left[i], j);
            }
        }
        for (int i = 0; i < m; ++i) {
            int u = left[i];
            for (int j = i + 1; j < m; ++j) {
                int v = left[j];
                for (int c1 = 0; c1 <= 1; ++c1) {
                    for (int c2 = 0; c2 <= 1; ++c2) {
                        if (check(u, c1, v, c2 ^ 1)) {
                            addedge(u << 1 | c1, v << 1 | c2 ^ 1);
                        }
                    }
                }
            }
        }
        vector<int> ans = solve(m);
        for (int i = 0; i < m; ++i) {
            int u = left[ans[i] >> 1];
            if (~ans[i] & 1) {
                match[b[u][0]] = b[u][1];
                match[b[u][1]] = -1;
                match[b[u][2]] = b[u][3];
                match[b[u][3]] = -1;
            } else {
                match[b[u][0]] = b[u][2];
                match[b[u][1]] = b[u][3];
                match[b[u][2]] = -1;
                match[b[u][3]] = -1;
            }
        }
        for (int i = 0; i < n; ++i) {
            printf("%d", match[i] == -1);
        }
        printf("\n");
        for (int i = 0; i <= n; ++i) {
            b[i].clear();
        }
    }
    return 0;
}
