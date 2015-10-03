#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 10005, M = N << 1, B = 101;
int n, b;
int w[N];

int top, head[N], to[M], next[M];
void addedge(int u, int v) {
    to[top] = v, next[top] = head[u], head[u] = top++;
}

int id;
pair<int, int> p[N << 1];

int newid(int u, int ch) {
    p[id] = make_pair(u, ch);
    return id++;
}

int sum[N], size[N];
vector<int> pt[N], ch[N];

int f[N << 1][B], pa[N << 1][B];


void dp(int u, int fa) {
    int id = newid(u, 0);
    pt[u].push_back(id);
    for (int i = 0; i <= b; ++i) {
        f[id][i] = w[u];
        pa[id][i] = -1;
    }
    sum[u] = w[u], size[u] = 1;
    for (int j = head[u]; ~j; j = next[j]) {
        int v = to[j];
        if (v == fa) {
            continue;
        }
        dp(v, u);
        ch[u].push_back(v);
        size[u] += size[v], sum[u] += sum[v];
        int vid = pt[v].back(), nid = newid(u, pt[u].size());
        pt[u].push_back(nid);
        for (int i = 0; i <= b; ++i) {
            f[nid][i] = f[id][i] + f[vid][0] + sum[v];
            pa[nid][i] = 0;
        }
        for (int k = 1; k <= b; ++k) {
            for (int i = 1; i + k <= b; ++i) {
                int cost = f[id][i] + f[vid][k];
                if (cost < f[nid][i + k]) {
                    f[nid][i + k] = cost;
                    pa[nid][i + k] = k;
                }
            }
        }
        id = nid;
    }
    int mins = 1;
    for (int j = 1; j <= size[u] && j <= b; ++j) {
        if (f[id][j] < f[id][mins]) {
            mins = j;
        }
    }
    f[id][0] = f[id][mins];
    pa[id][0] = mins;
}

vector<vector<int> > ans;

void build(int u, int id = -1, int cut = -1) {
    if (id == -1) {
        id = ans.size();
        ans.push_back(*new vector<int>);
        cut = pa[pt[u].back()][0];
    }
    ans[id].push_back(u);
    for (int j = pt[u].size() - 1; j > 0; --j) {
        int cid = pt[u][j];
        int v = ch[u][j - 1];
        if (pa[cid][cut] == 0) {
            build(v);
        } else {
            build(v, id, pa[cid][cut]);
            cut -= pa[cid][cut];
        }
    }
}

int main() {
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &b);
    for (int i = 0; i < n; ++i) {
        scanf("%d", w + i);
    }
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        addedge(u, v);
        addedge(v, u);
    }
    dp(0, -1);
    build(0);
    printf("%.12f\n", (double)f[pt[0].back()][0] / sum[0]);
    printf("Number of blocks: %d\n", (int)ans.size());
    for (int i = 0; i < (int)ans.size(); ++i) {
        printf("Number of nodes in block %d: %d\n", i, (int)ans[i].size());
        for (int j = 0; j < (int)ans[i].size(); ++j) {
            printf("%d\n", ans[i][j]);
        }
    }
    return 0;
}
