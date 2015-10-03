#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 20;

int n;
int g[N][N];

int m;

const int INF = 100000000;

int dis[2][1 << (N - 2)][N];

void dp(int source, int dis[][N]) {
    for (int st = 0; st < 1 << n - 2; ++st) {
        for (int i = 1; i < n - 1; ++i) {
            dis[st][i] = INF;
        }
    }
    for (int i = 1; i < n - 1; ++i) {
        dis[1 << i - 1][i] = g[source][i];
    }
    for (int st = 0; st < 1 << n - 2; ++st) {
        for (int i = 1; i < n - 1; ++i) {
            for (int j = 1; j < n - 1; ++j) {
                dis[st ^ (1 << j - 1)][j] = min(dis[st ^ (1 << j - 1)][j], dis[st][i] + g[i][j]);
            }
        }
    }
}

int main() {
    while (scanf("%d", &n) == 1) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                g[i][j] = INF;
            }
            g[i][i] = 0;
        }
        scanf("%d", &m);
        for (int i = 0; i < m; ++i) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            g[u][v] = g[v][u] = min(g[u][v], w);
        }
        for (int k = 0; k < n; ++k) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
                }
            }
        }
        dp(0, dis[0]);
        dp(n - 1, dis[1]);
        int ans = INF;
        int mask = (1 << n - 2) - 1;
        for (int st = 0; st < 1 << n - 2; ++st) {
            if (__builtin_popcount(st) == (n + (n == 3)) / 2 - 1) {
                for (int i = 1; i < n - 1; ++i) {
                    for (int j = 1; j < n - 1; ++j) {
                        if (st >> (j - 1) & 1) {
                            ans = min(ans, dis[0][st][i] + dis[1][mask ^ st ^ (1 << i - 1)][i] +
                                    dis[1][st][j] + dis[0][mask ^ st ^ (1 << j - 1)][j]);
                        }
                    }
                }
            }
        }
        static int id = 0;
        printf("Case %d: %d\n", ++id, ans);
    }
    return 0;
}
