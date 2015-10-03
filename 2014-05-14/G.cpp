#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 505;

int n;

int g[N][N];

bool by_val(pair<int, int> x, pair<int, int> y) {
    return g[x.first][x.second] > g[y.first][y.second];
}

int fa[N], fa2[N];

int find(int fa[], int u) {
    return u == fa[u] ? u : fa[u] = find(fa, fa[u]);
}

void merge(int fa[], int u, int v) {
    fa[u] = v;
}

int main() {
    freopen("treexor.in", "r", stdin);
    freopen("treexor.out", "w", stdout);
    scanf("%d", &n);
    if (n % 2 == 0) {
        printf("-1\n");
        return 0;
    }
    vector<pair<int, int> > all;
    for (int i = 0; i < n; ++i) {
        fa[i] = fa2[i] = i;
        for (int j = 0; j < n; ++j) {
            if (i < j) {
                all.push_back(make_pair(i, j));
            }
            scanf("%d", &g[i][j]);
        }
    }
    sort(all.begin(), all.end(), by_val);
    for (int i = 0; i < (int)all.size(); ++i) {
        int u = all[i].first, v = all[i].second;
        if (i < (n - 1) / 2) {
            printf("%d %d\n", u + 1, v + 1);
            merge(fa, find(fa, u), find(fa, v));
        } else if (i < n - 1) {
            merge(fa2, find(fa2, u), find(fa2, v));
        } else {
            if (find(fa, u) != find(fa, v) && find(fa2, u) != find(fa2, v)) {
                printf("%d %d\n", u + 1, v + 1);
                merge(fa, find(fa, u), find(fa, v));
                merge(fa2, find(fa2, u), find(fa2, v));
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        if (find(fa, i) != find(fa, 0) || find(fa2, i) != find(fa2, 0)) {
            while (true) {
                continue;
            }
        }
    }
    return 0;
}
