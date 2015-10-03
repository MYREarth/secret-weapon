#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int MOD = 1000000007;

const int N = 205;
int n, g[N][N];

int ans;

void addedge(int u, int v, int flag = 1) {
    for (int i = 0; i <= u; ++i) {
        for (int j = v; j < n; ++j) {
            int old = g[i][j];
            g[i][j] += (long long)g[i][u] * g[v][j] * flag % MOD;
            g[i][j] = (g[i][j] % MOD + MOD) % MOD;
            if (old == 0 && g[i][j] != 0) {
                ++ans;
            } else if (old != 0 && g[i][j] == 0) {
                --ans;
            }
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        g[i][i] = 1;
    }
    int m;
    scanf("%d", &m);
    for (int i = 0; i < m; ++i) {
        int u, v;
        scanf("%d%d", &u,  &v);
        --u, --v;
        addedge(u, v);
    }
    printf("%d\n", ans);
    int k;
    scanf("%d", &k);
    while (k--) {
        char op[2];
        scanf("%s", op);
        int u, v;
        scanf("%d%d", &u, &v);
        --u, --v;
        if (op[0] == '?') {
            printf("%s\n", g[u][v] ? "YES" : "NO");
        } else if (op[0] == '+') {
            addedge(u, v);
            printf("%d\n", ans);
        } else {
            addedge(u, v, -1);
            printf("%d\n", ans);
        }
    }
    return 0;
}
