#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <vector>

const int N = 201;
const int MOD = (int)1e9 + 7;

int n, m, parent[N], size[N], scale[N], ways[2][N][N + 1];
std::vector <int> children[N];

int inverse(int a) {
    return a == 1 ? 1 : (long long)(MOD - MOD / a) * inverse(MOD % a) % MOD;
}

void prepare(int u) {
    size[u] = 1;
    for (auto &v : children[u]) {
        prepare(v);
        size[u] += size[v];
    }
}

void update(int &x, int a) {
    x += a;
    if (x >= MOD) {
        x -= MOD;
    }
}

void solve(int u) {
    for (auto &v : children[u]) {
        solve(v);
    }
    int tmp[2][2][N + 1];
    memset(tmp, 0, sizeof(tmp));
    tmp[0][0][0] = 1;
    int p = 0;
    int total = 0;
    for (auto &v : children[u]) {
        memset(tmp[p ^ 1], 0, sizeof(tmp[p ^ 1]));
        for (int x = 0; x < 2; ++ x) {
            for (int y = 0; y <= total; ++ y) {
                for (int z = 0; z < 2; ++ z) {
                    if (x && z) {
                        continue;
                    }
                    for (int yy = 0; yy <= size[v]; ++ yy) {
                        update(tmp[p ^ 1][x | z][y + yy], (long long)tmp[p][x][y] * ways[z][v][yy] % MOD);
                    }
                }
            }
        }
        total += size[v];
        p ^= 1;
    }
    for (int i = 0; i <= size[u]; ++ i) {
        ways[0][u][i] = (tmp[p][0][i] + tmp[p][1][i]) % MOD;
        if (i) {
            ways[1][u][i] = (long long)tmp[p][0][i - 1] * scale[u] % MOD;
        }
    }
}

int main() {
    while (scanf("%d%d", &n, &m) == 2 && n) {
        for (int i = 0; i <= n; ++ i) {
            children[i].clear();
        }
        parent[1] = 0;
        children[0].push_back(1);
        for (int i = 2; i <= n; ++ i) {
            scanf("%d", parent + i);
            children[parent[i]].push_back(i);
        }
        prepare(0);
        scale[0] = 1;
        for (int i = 1; i <= n; ++ i) {
            scale[0] = (long long)scale[0] * i % MOD * inverse(size[i]) % MOD;
        }
        for (int i = 1; i <= n; ++ i) {
            scale[i] = (long long)size[i] * inverse(size[parent[i]] - size[i]) % MOD;
        }
        memset(ways, 0, sizeof(ways));
        solve(1);
        int result = 0;
        for (int j = 0; j <= m; ++ j) {
            (result += ways[0][1][j]) %= MOD;
        }
        printf("%d\n", (int)((long long)scale[0] * result % MOD));
    }
    return 0;
}
