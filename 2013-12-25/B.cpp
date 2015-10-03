#include<cmath>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int n, m;

const int N = 30000;
int top, head[N], to[N * 3 * 2], next[N * 3 * 2];

void addedge(int u, int v) {
    to[top] = v, next[top] = head[u], head[u] = top++;
}

struct Que {
    int l, r, id;

    Que(int l, int r, int id) : l(l), r(r), id(id) {}
};

bool operator < (const Que &a, const Que &b) {
    return a.r < b.r;
}

int b;
vector<Que> q[300];

int ans[N];

int stamp;
int fa[N], fa2[N], vis[N];

int find(int u) {
    return u == fa[u] ? u : fa[u] = find(fa[u]);
}

void merge(int u, int v) {
    fa[u] = v;
}

int find2(int u) {
    if (vis[u] != stamp) {
        vis[u] = stamp;
        fa2[u] = fa[u];
    }
    return u == fa2[u] ? u : fa2[u] = find2(fa2[u]);
}

void merge2(int u, int v) {
    fa2[u] = v;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        top = 0;
        memset(head, -1, sizeof(head));
        scanf("%d%d", &n, &m);
        for (int i = 0; i < m; ++i) {
            int u, v;
            scanf("%d%d", &u, &v);
            --u, --v;
            addedge(u, v);
            addedge(v, u);
        }
        b = sqrt(n) + 1;   
        for (int i = 0; i <= n / b; ++i) {
            q[i].clear();
        }
        int qq;
        scanf("%d", &qq);
        for (int i = 0; i < qq; ++i) {
            int l, r;
            scanf("%d%d", &l, &r);
            --l, --r;
            q[l / b].push_back(Que(l, r, i));
        }
        for (int i = 0; i <= n / b; ++i) {
            sort(q[i].begin(), q[i].end());
            stamp = 0;
            for (int j = 0; j < n; ++j) {
                fa[j] = j;
                vis[j] = -1;
            } 
            int last = (i + 1) * b, cnt = 0;
            for (int j = 0; j < (int)q[i].size(); ++j) {
                ++stamp;
                int l = q[i][j].l, r = q[i][j].r, id = q[i][j].id, tmp = 0;
                if (r / b == i) {
                    for (int k = l; k <= r; ++k) {
                        vis[k] = stamp;
                        fa2[k] = k; 
                        ++tmp;
                    }
                    for (int u = l; u <= r; ++u) {
                        for (int o = head[u]; ~o; o = next[o]) {
                            int v = to[o];
                            if (v < l || v > r) {
                                continue;
                            }
                            if (find2(u) != find2(v)) {
                                --tmp;
                                merge2(find2(u), find2(v));
                            }
                        }
                    }
                } else {
                    while (last <= r) {
                        int u = last++; 
                        ++cnt;
                        for (int o = head[u]; ~o; o = next[o]) {
                            int v = to[o];
                            if (v >= last || v < (i + 1) * b) {
                                continue;
                            }
                            if (find(u) != find(v)) {
                                merge(find(u), find(v));
                                --cnt;
                            }
                        }
                    }
                    tmp = cnt;
                    for (int k = l; k < (i + 1) * b; ++k) {
                        vis[k] = stamp;
                        fa2[k] = k; 
                        ++tmp;
                    }
                    for (int u = l; u < (i + 1) * b; ++u) {
                        for (int o = head[u]; ~o; o = next[o]) {
                            int v = to[o];
                            if (v < l || v > r) {
                                continue;
                            }
                            if (find2(u) != find2(v)) {
                                --tmp;
                                merge2(find2(u), find2(v));
                            }
                        }
                    }
                }
                ans[id] = tmp;
            }
        }
        static int id = 0;
        printf("Case #%d:\n", ++id);
        for (int i = 0; i < qq; ++i) {
            printf("%d\n", ans[i]);
        }
    }
    return 0;
}
