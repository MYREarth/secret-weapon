#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int n;

vector<vector<pair<int, int> > > fac;

const int N = 205;
bool vis[N], used[N];

inline int tr(int u) {
    return u > 2 * n ? u - 2 * n : u;
}

void build() {
    fac.clear();
    memset(used, 0, sizeof(used));
    for (int i = 1; i < n; ++i) {
        if (used[i]) {
            continue;
        }
        int len = 0, tmp = 0;
        do {
            ++len;
            tmp = (tmp + i) % (n * 2);
        } while (tmp != 0);
cout << n << ' ' << i << ' ' << len << endl;
        if (len % 2 == 0) {
            continue;
        } else {
            int delta = len;
            while (used[delta]) {
                delta += len;
            }
cout << "delta" << ' ' << delta << endl;
            memset(vis, 0, sizeof(vis));
            used[i] = used[delta] = true;
            vector<vector<int> > cycles;
            for (int j = 0; true; ++j) {
                int cur = j ? cycles[j - 1][0] + delta : 1;
                if (cur > 2 * n) {
                    cur -= 2 * n;
                }
                if (vis[cur]) {
                    break;
                }
                vector<int> tmp;
                do {
                    vis[cur] = true;
                    tmp.push_back(cur);
                    cur += i;
                    if (cur > 2 * n) {
                        cur -= 2 * n;
                    }
                } while (!vis[cur]);
                cycles.push_back(tmp);
            }
            if (delta != n) {
                vector<pair<int, int> > tmp[4];
                for (int j = 0; j < (int)cycles.size(); ++j) {
                    tmp[0].push_back(make_pair(cycles[j][0], cycles[j][1]));
                    tmp[1].push_back(make_pair(cycles[j][1], cycles[j][2]));
                    if (j % 2 == 0) {
                        tmp[3].push_back(make_pair(cycles[j][0], tr(cycles[j][0] + delta)));
                        tmp[2].push_back(make_pair(cycles[j][1], tr(cycles[j][1] + delta)));
                    }
                    if (j % 2 == 1) {
                        tmp[3].push_back(make_pair(cycles[j][1], tr(cycles[j][1] + delta)));
                        tmp[3].push_back(make_pair(cycles[j][2], tr(cycles[j][2] + delta)));
                    }
                    for (int k = 0; k < (int)cycles[j].size(); ++k) {
                        int u = cycles[j][k];
                        if (k != 0 && k != 1) {
                            if (j % 2 == 1) {
                                tmp[0].push_back(make_pair(u, tr(u + delta)));
                            }
                            if (k % 2 == 0) {
                                tmp[2].push_back(make_pair(u, tr(u + i)));
                            }
                        }
                        if (k != 1 && k != 2) {
                            if (j % 2 == 0) {
                                tmp[1].push_back(make_pair(u, tr(u + delta)));
                            }
                            if (k % 2 == 1) {
                                tmp[3].push_back(make_pair(u, tr(u + i)));
                            }
                        }
                    }
                }
                for (int j = 0; j < 4; ++j) {
                    fac.push_back(tmp[j]);
                }
            } else {
                vector<pair<int, int> > tmp[4];
                for (int j = 0; j < (int)cycles.size(); ++j) {
                    tmp[0].push_back(make_pair(cycles[j][0], cycles[j][1]));
                    if (j % 2 == 0) {
                        tmp[3].push_back(make_pair(cycles[j][0], tr(cycles[j][0] + delta)));
                        tmp[2].push_back(make_pair(cycles[j][1], tr(cycles[j][1] + delta)));
                    }
                    for (int k = 0; k < (int)cycles[j].size(); ++k) {
                        int u = cycles[j][k];
                        if (k != 0 && k != 1) {
                            if (j % 2 == 1) {
                                tmp[0].push_back(make_pair(u, tr(u + delta)));
                            }
                            if (k % 2 == 0) {
                                tmp[2].push_back(make_pair(u, tr(u + i)));
                            }
                        }
                        if (k % 2 == 1) {
                            tmp[3].push_back(make_pair(u, tr(u + i)));
                        }
                    }
                }
                for (int j = 0; j < 4; ++j) {
                    if (j != 1) {
                        fac.push_back(tmp[j]);
                    }
                }
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        if (used[i]) {
            continue;
        }
        if (i == n) {
            vector<pair<int, int> > tmp;
            for (int j = 1; j <= n; ++j) {
                tmp.push_back(make_pair(j, j + n));
            }
            fac.push_back(tmp);
        } else {
            int len = 0, tmp = 0;
            do {
                ++len;
                tmp = (tmp + i) % (n * 2);
            } while (tmp != 0);
            memset(vis, 0, sizeof(vis));
            used[i] = true;
            if (len % 2 == 0) {
                vector<int> tmp;
                for (int j = 1; j <= 2 * n; ++j) {
                    if (vis[j]) {
                        continue;
                    }
                    int next = j;
                    do {
                        tmp.push_back(next);
                        vis[next] = true;
                        next += i;
                        if (next > 2 * n) {
                            next -= 2 * n;
                        }
                    } while (!vis[next]);
                }
                vector<pair<int, int> > a[2];
                for (int j = 0; j < (int)tmp.size(); ++j) {
                    if ((j + 1) % len == 0) {
                        a[j % 2].push_back(make_pair(tmp[j], tmp[(j + 1) - len]));
                    } else {
                        a[j % 2].push_back(make_pair(tmp[j], tmp[j + 1]));
                    }
                }
                fac.push_back(a[0]), fac.push_back(a[1]);
            }
        }
    }
}

bool g[N][N];

bool check() {
    for (int i = 1; i <= 2 * n; ++i) {
        for (int j = 1; j <= 2 * n; ++j) {
            g[i][j] = false;
        }
    }
    if (fac.size() != 2 * n - 1) {
        return false;
    }
    for (int i = 0; i < 2 * n - 1; ++i) {
        if (fac[i].size() != n) {
            return false;
        }
        memset(vis, 0, sizeof(vis));
        for (int j = 0; j < (int)fac[i].size(); ++j) {
            int u = fac[i][j].first, v = fac[i][j].second;
            if (vis[u] || vis[v] || u == v) {
                return false;
            }
            vis[u] = true;
            vis[v] = true;
            if (g[u][v] || g[v][u]) {
                return false;
            }
            g[u][v] = g[v][u] = true;
        }
    }
    return true;
}

int main() {
    //freopen("factor.in", "r", stdin);
    //freopen("factor.out", "w", stdout);

    for (int i = 1; i <= 100; ++i) {
        n = i;
        build();
        if (!check()) {
            printf("%d\n", i);
            printf("%d\n", (int)fac.size());
            for (int j = 0; j < (int)fac.size(); ++j) {
                for (int k = 0; k < (int)fac[j].size(); ++k) {
                    printf("%d %d  ", fac[j][k].first, fac[j][k].second);
                }
                printf("\n");
            }
            return 0;
        }
    }

    scanf("%d", &n);
    build();
    check();
    int m;
    scanf("%d", &m);
    for (int i = 0; i < m; ++i) {
        int k;
        scanf("%d", &k);
        while (k--) {
            vector<pair<int, int> > tmp = fac.back();
            for (int i = 0; i < (int)tmp.size(); ++i) {
                printf("%d %d\n", tmp[i].first, tmp[i].second);
            }
            fac.pop_back();
        }
        if (i != m - 1) {
            printf("\n");
        }
    }
    return 0;
}
