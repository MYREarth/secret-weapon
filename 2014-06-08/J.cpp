#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 100005;

int n, m;

int fa[N], len[N];

int stamp, vis[N];

int main() {
    freopen("joy.in", "r", stdin);
    freopen("joy.out", "w", stdout);
    scanf("%d%d", &n, &m);
    memset(fa, -1, sizeof(fa));
    long long ans = 0;
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        if (u != v) {
            ++stamp;
            int t = u;
            while (t != -1) {
                vis[t] = stamp;
                t = fa[t];
            }

            int lca = v;
            while (lca != -1 && vis[lca] != stamp) {
                lca = fa[lca];
            }

            int maxedgeu = -1, maxedgev = -1, maxedgecost = -1, place = -1;
            if (lca == -1) {

            } else {
                t = u;
                while (t != lca) {
                    if (len[t] > maxedgecost) {
                        maxedgeu = t;
                        maxedgev = fa[t];
                        maxedgecost = len[t];
                        place = 0;
                    }
                    t = fa[t];
                }
                t = v;
                while (t != lca) {
                    if (len[t] > maxedgecost) {
                        maxedgeu = t;
                        maxedgev = fa[t];
                        maxedgecost = len[t];
                        place = 1;
                    }
                    t = fa[t];
                }
            }
            if (lca == -1 || maxedgecost > w) {
                if (lca != -1) {
                    ans -= maxedgecost;
                }
                ans += w;
                if (place == 1) {
                    swap(u, v);
                }
                int last = v, wlast = w;
                t = u;
                while (t != maxedgev) {
                    int mem = fa[t], wmem = len[t];
                    fa[t] = last;
                    len[t] = wlast;
                    last = t;
                    wlast = wmem;
                    t = mem;
                }
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}
