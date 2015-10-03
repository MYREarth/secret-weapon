#include<vector>
#include<cstdio>
#include<cassert>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 11, MOD = 1000000007;
int n, m;
int fa[N * N], size[N * N];

#define x1 X1
#define y1 Y1

int x1[N], y1[N], x2[N], y2[N];

int f[N][N];

int find(int u);

inline int getf(int x, int y) {
    if (x < 0 || x >= n || y < 0 || y >= n) {
        return n * n;
    } else {
        return f[x][y];
    }
}

const int dx[] = {1, -1, 0, 0}, dy[] = {0, 0, 1, -1};

vector<pair<int, int> > get_edge() {
    vector<pair<int, int> > ret;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int d = 0; d < 4; ++d) {
                int x = i + dx[d], y = j + dy[d];
                int u = find(getf(i, j)), v = find(getf(x, y));
                if (u < v) {
                    ret.push_back(make_pair(u, v));
                    ret.push_back(make_pair(v, u));
                }
            }
        }
    }
    return ret;
}

int ord[N * N + 1];

void relabel(int &cnt, int &front, int &back) {
    cnt = 0;
    for (int i = 0; i < n * n + 1; ++i) {
        if (find(i) == i) {
            ++cnt;
        }
    }
    front = 0, back = cnt;
    for (int i = 0; i < n * n + 1; ++i) {
        if (find(i) == i) {
            if (size[i] == 1 && i != n * n) {
                ord[i] = front++;
            } else {
                ord[i] = --back;
            }
        }
    }
}

int g[N * N + 1][N * N + 1];

void build_matrix(const vector<pair<int, int> > &edge) {
    memset(g, 0, sizeof(g));
    for (int i = 0; i < (int)edge.size(); ++i) {
        int u = ord[edge[i].first], v = ord[edge[i].second];
        --g[u][v], ++g[u][u];
    }
}

bool check_matrix(int n, int back, int down) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (g[i][j] != 0) {
                if (i >= back || j >= back || abs(j - i) < down) {
                    continue;
                }
                return false;
            }
        }
    }
    return true;
}

void print_matrix(int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%d ", g[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int inverse(int a) {
    return a == 1 ? 1 : (long long)(MOD - MOD / a) * inverse(MOD % a) % MOD;
}

int gauss(int n, int back, int down) {
    assert(check_matrix(n, back, down));
    //print_matrix(n);
    int ret = 1;
    for (int i = 0; i < n; ++i) {
        if (g[i][i] == 0) {
            for (int j = i + 1; j < n; ++j) {
                if (g[j][i] != 0) {
                    for (int k = i; k < (i + down) && k < n; ++k) {
                        swap(g[i][k], g[j][k]);
                    }
                    for (int k = max(min(i + down, n), back); k < n; ++k) {
                        swap(g[i][k], g[j][k]);
                    }
                    ret *= -1;
                    break;
                }
            }
        }
        for (int j = i + 1; j < i + down && j < n; ++j) {
            int div = (long long)g[j][i] * inverse(g[i][i]) % MOD;
            for (int k = i; k < (i + down) && k < n; ++k) {
                (g[j][k] -= (long long)g[i][k] * div % MOD) %= MOD;
            }
            for (int k = max(min(i + down, n), back); k < n; ++k) {
                (g[j][k] -= (long long)g[i][k] * div % MOD) %= MOD;
            }
        }
        for (int j = max(min(i + down, n), back); j < n; ++j) {
            int div = (long long)g[j][i] * inverse(g[i][i]) % MOD;
            for (int k = i; k < (i + down) && k < n; ++k) {
                (g[j][k] -= (long long)g[i][k] * div % MOD) %= MOD;
            }
            for (int k = max(min(i + down, n), back); k < n; ++k) {
                (g[j][k] -= (long long)g[i][k] * div % MOD) %= MOD;
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        ret = (long long)ret * g[i][i] % MOD;
    }
    return ret;
}

int solve() {
    int cnt, front, back;
    relabel(cnt, front, back);
    build_matrix(get_edge());
    return gauss(cnt - 1, back, n + 1);
}

int find(int u) {
    return fa[u] == u ? u : fa[u] = find(fa[u]);
}

void merge(int u, int v) {
    fa[u] = v;
    size[v] += size[u];
}

bool init(int st) {
    for (int i = 0; i < n * n; ++i) {
        fa[i] = i;
        size[i] = 1;
    }
    fa[n * n] = n * n;
    size[n * n] = 1;
    for (int i = 0; i < m; ++i) {
        if (st >> i & 1) {
            int u = f[x1[i]][y1[i]], v = f[x2[i]][y2[i]];
            if (find(u) == find(v)) {
                return false;
            }
            merge(find(u), find(v));
        }
    }
//cout << "check" << ' ' << st << endl;
    return true;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    scanf("%d%d", &n, &m);
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            f[i][j] = cnt++;
        }
    }
    for (int i = 0; i < m; ++i) {
        scanf("%d%d%d%d", x1 + i, y1 + i, x2 + i, y2 + i);
        --x1[i], --y1[i], --x2[i], --y2[i];
    }
    int ans = 0;
    for (int st = 0; st < (1 << m); ++st) {
        if (!init(st)) {
            continue;
        }
        int sig = 1;
        for (int i = 0; i < m; ++i) {
            if (st >> i & 1) {
                sig *= -1;
            }
        }
        int delta = sig * solve();
        (ans += delta) %= MOD;
        if (ans < 0) {
            ans += MOD;
        }
//cout << st << ' ' << delta << endl;
    }
    printf("%d\n", ans);
    return 0;
}
