#include<queue>
#include<cmath>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int n, m;

const int N = 405;
int x[N], y[N], z[N], k[N];
vector<int> edge[N];

int cnt, col[N];

int bfs(int source, int t) {
    queue<int> q;
    q.push(source);
    col[source] = cnt;
    int ret = 0;
    while (q.size()) {
        int u = q.front();
        ret += k[u];
        q.pop();
        for (int j = 0; j < (int)edge[u].size(); ++j) {
            int v = edge[u][j];
            if (col[v] != cnt && z[v] <= t) {
                q.push(v);
                col[v] = cnt;
            }
        }
    }
    return ret;
}

double dis[N][N];

int c[N];
double g[N][N];

double path[N];
bool use[N];

int main() {
    while (scanf("%d%d", &n, &m) == 2) {
        vector<int> h;
        for (int i = 0; i < n; ++i) {
            scanf("%d%d%d%d", x + i, y + i, z + i, k + i);
            for (int j = 0; j < i; ++j) {
                long double dx = x[j] - x[i], dy = y[j] - y[i], dz = z[j] - z[i];
                dis[i][j] = dis[j][i] = sqrt(dx * dx + dy * dy + dz * dz);
            }
            edge[i].clear();
            h.push_back(z[i]);
        }
        sort(h.begin(), h.end());
        h.erase(unique(h.begin(), h.end()), h.end());
        for (int i = 0; i < m; ++i) {
            int u, v;
            scanf("%d%d", &u, &v);
            u--, v--;
            edge[u].push_back(v);
            edge[v].push_back(u);
        }
        double ans = 1e100;
        for (int i = 0; i < (int)h.size(); ++i) {
            int t = h[i];
            if (t < z[0] || t < z[n - 1]) {
                continue;
            }
            for (int j = 0; j < n; ++j) {
                col[j] = -1;
            }
            cnt = 0;
            for (int j = 0; j < n; ++j) {
                if (col[j] == -1 && z[j] <= t) {
                    c[cnt] = bfs(j, t);
                    ++cnt;
                }
            }
            if (col[0] == col[n - 1]) {
                ans = min(ans, c[0] * 0.5);
                break;
            } else {
                for (int i = 0; i < n; ++i) {
                    for (int j = 0; j < n; ++j) {
                        g[i][j] = 1e100;
                    }
                    g[i][i] = 0;
                }
                for (int i = 0; i < n; ++i) {
                    if (col[i] == -1) {
                        continue;
                    }
                    for (int j = 0; j < n; ++j) {
                        if (col[j] == -1) {
                            continue;
                        }
                        if (col[i] == col[j]) {
                            g[i][j] = 0;
                        } else {
                            if (k[i] > 0 && k[j] > 0) {
                                g[i][j] = dis[i][j] + c[col[j]] * 0.5 - 1;
                            }
                        }
                    }
                }
                for (int i = 0; i < n; ++i) {
                    path[i] = 1e100;
                    use[i] = false;
                }
                path[0] = c[col[0]] * 0.5;
                while (!use[n - 1]) {
                    int u = -1;
                    for (int i = 0; i < n; ++i) {
                        if (use[i]) {
                            continue;
                        }
                        if (u == -1 || path[u] > path[i]) {
                            u = i;
                        }
                    }
                    use[u] = true;
                    if (col[u] != col[0] && col[u] != col[n - 1] && c[col[u]] == 1) {
                        continue;
                    }
                    for (int v = 0; v < n; ++v) {
                        if (path[v] > path[u] + g[u][v]) {
                            path[v] = path[u] + g[u][v];
                        }
                    }
                }
                ans = min(ans, path[n - 1]);
            }
        }
        static int id = 0;
        printf("Case %d: ", ++id);
        if (ans > 1e99) {
            printf("impossible\n");
        } else {
            printf("%.4f\n", ans);
        }
    }
    return 0;
}
