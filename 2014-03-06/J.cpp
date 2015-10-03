#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 100005, M = N << 1;
int n, k;
int top, head[N], to[M], next[M];

vector<int> ans;

void addedge(int u, int v) {
    to[top] = v, next[top] = head[u], head[u] = top++;
}

int dfs(int u, int fa_edge) {
    int ret = 1;
    for (int i = head[u]; ~i; i = next[i]) {
        if ((i >> 1) == fa_edge) {
            continue;
        }
        int v = to[i];
        ret += dfs(v, i >> 1);
    }
    if (ret >= ((k + 1) / 2) && fa_edge != -1) {
        ans.push_back(fa_edge);
        ret = 0;
    }
    return ret;
}

int main() {
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        --u, --v;
        addedge(u, v);
        addedge(v, u);
    }
    dfs(0, -1);
    printf("%d\n", (int)ans.size());
    for (int i = 0; i < (int)ans.size(); ++i) {
        printf("%d\n", ans[i] + 1);
    }
    return 0;
}
