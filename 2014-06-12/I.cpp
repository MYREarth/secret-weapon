#include<bitset>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int n, p;

const int N = 205;

int fa[N], w[N], size[N];

vector<int> edge[N];
vector<int> ord;

void dfs(int u) {
    ord.push_back(u);
    size[u] = 1;
    for (int j = 0; j < (int)edge[u].size(); ++j) {
        int v = edge[u][j];
        dfs(v);
        size[u] += size[v];
    }
}

const int P = 1000005;
bitset<P> f[N];

int main() {
    scanf("%d%d", &n, &p);
    for (int i = 0; i < n; ++i) {
        scanf("%d%d", fa + i, w + i);
        --fa[i];
        if (fa[i] != -1) {
            edge[fa[i]].push_back(i);
        }
    }
    for (int i = 0; i < n; ++i) {
        if (fa[i] == -1) {
            dfs(i);
        }
    }
    f[n].set(0);
    for (int i = n - 1; i >= 0; --i) {
        int u = ord[i];
        f[i] = f[i + 1] << w[u] | f[i + size[u]];
    }
    int ans = p;
    while (!f[0][ans]) {
        --ans;
    }
    printf("%d\n", ans);
    vector<int> anst;
    int pos = 0, x = ans;
    while (pos != n) {
        int u = ord[pos];
        if (f[pos + size[u]][x]) {
            pos = pos + size[u];
        } else {
            anst.push_back(u + 1);
            pos = pos + 1;
            x -= w[u];
        }
    }
    sort(anst.begin(), anst.end());
    printf("%d", (int)anst.size());
    for (int i = 0; i < (int)anst.size(); ++i) {
        printf(" %d", anst[i]);
    }
    printf("\n");
    return 0;
}
