#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 105, INF = 1000005;

int n, m, g[N][N], dis[N * N];

bool by_match(pair<pair<int, int>, int> u, pair<pair<int, int>, int> v) {
    int i = u.second, j = v.second;
    return dis[i] > dis[j];
}

int main() {
    freopen("iterative.in", "r", stdin);
    freopen("iterative.out", "w", stdout);
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            g[i][j] = INF;
        }
        g[i][i] = 0;
    }
    vector<pair<pair<int, int>, int> > edge;
    for (int i = 0; i < m; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        --u, --v;
        g[u][v] = g[v][u] = 1;
        edge.push_back(make_pair(make_pair(u, v), i));
    }
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
            }
        }
    }
    int len = 0, lenu = 0;
    for (int u = 0; u < n; ++u) {
        for (int v = 0; v < n; ++v) {
            if (g[u][v] != INF && g[u][v] > len) {
                len = g[u][v];
                lenu = u;
            }
        }
    }
    printf("%d\n", len + 1);
    printf("%d", lenu + 1);
    for (int i = 0; i < n; ++i) {
        if (lenu != i) {
            printf(" %d", i + 1);
        }
    }
    printf("\n");
    for (int i = 0; i < m; ++i) {
        dis[i] = min(g[edge[i].first.first][lenu], g[edge[i].first.second][lenu]);
    }
    sort(edge.begin(), edge.end(), by_match);
    for (int i = 0; i < m; ++i) {
        printf("%d%c", edge[i].second + 1, i == m - 1 ? '\n' : ' ');
    }
    return 0;
}
