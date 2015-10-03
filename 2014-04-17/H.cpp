#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 100005, M = N << 1;

int p[N];

#define next NEXT

int top, head[N], next[M], to[M], l[M];

void addedge(int u, int v, int len) {
    to[top] = v, next[top] = head[u], l[top] = len, head[u] = top++;
}

int n;

vector<int> ord;

int len[N], fa[N];

long long sum[N], wei[N];

void dfs(int u) {
    ord.push_back(u);
    sum[u] = 0, wei[u] = p[u];
    for (int j = head[u]; ~j; j = next[j]) {
        int v = to[j];
        if (v == fa[u]) {
            continue;
        }
        fa[v] = u;
        len[v] = l[j];
        dfs(v);
        sum[u] += (long long)wei[v] * l[j] + sum[v];
        wei[u] += wei[v];
    }
}

int main() {
    freopen("house.in", "r", stdin);
    freopen("house.out", "w", stdout);
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", p + i);
    }
    for (int i = 1; i < n; ++i) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        --u, --v;
        addedge(u, v, w);
        addedge(v, u, w);
    }
    fa[0] = -1;
    dfs(0);
    int ans;
    long long cost;
    ans = 0, cost = sum[0];
    for (int i = 1; i < n; ++i) {
        int u = ord[i];
        sum[u] = sum[fa[u]] - wei[u] * len[u] + (wei[0] - wei[u]) * len[u];
        if (sum[u] < cost) {
            cost = sum[u];
            ans = u;
        }
    }
    cout << ans + 1 << ' ' << cost << endl;
    return 0;
}
