#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 100005;
int n;

vector<int> edge[N];

long long size[N], cal[N];

void go(int u, int fa = -1) {
    size[u] = 1;
    for (int j = 0; j < (int)edge[u].size(); ++j) {
        int v = edge[u][j];
        if (v == fa) {
            continue;
        }
        go(v, u);
        cal[u] += size[u] * size[v];
        size[u] += size[v];
    }
}

int main() {
    freopen("lca.in", "r", stdin);
    freopen("lca.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        --u, --v;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    go(0);
    int maxs = 0;
    vector<int> ans;
    for (int i = 0; i < n; ++i) {
        if (cal[i] > cal[maxs]) {
            maxs = i;
            ans.clear();
            ans.push_back(i + 1);
        } else if (cal[i] == cal[maxs]) {
            ans.push_back(i + 1);
        }
    }
    printf("%d\n", (int)ans.size());
    for (int i = 0; i < (int)ans.size(); ++i) {
        printf("%d%c", ans[i], i == (int)ans.size() - 1 ? '\n' : ' ');
    }
    return 0;
}
