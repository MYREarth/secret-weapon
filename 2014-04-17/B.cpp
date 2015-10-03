#include<queue>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int n;

const int N = 200005;

int size[N], maxchild[N];

vector<int> edge[N];

void dfs(int u, int fa) {
    size[u] = 1;
    for (int i = 0; i < (int)edge[u].size(); ++i) {
        int v = edge[u][i];
        if (v == fa) {
            continue;
        }
        dfs(v, u);
        size[u] += size[v];
        maxchild[u] = max(maxchild[u], size[v]);
    }
}

int col, ans[N];

vector<int> ch[N];

void go(int u, int fa, int col) {
    ch[col].push_back(u);
    for (int i = 0; i < (int)edge[u].size(); ++i) {
        int v = edge[u][i];
        if (v == fa) {
            continue;
        }
        go(v, u, col);
    }
}

int main() {
    freopen("bicoloring.in", "r", stdin);
    freopen("bicoloring.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        --u, --v;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    dfs(0, -1);
    int cen = 0;
    for (int i = 1; i < n; ++i) {
        maxchild[i] = max(maxchild[i], size[0] - size[i]);
        if (maxchild[i] < maxchild[cen]) {
            cen = i;
        }
    }
    ans[cen] = col = 1;
    int cnt = 0;
    priority_queue<pair<int, int> > heap;
    for (int i = 0; i < (int)edge[cen].size(); ++i) {
        int u = edge[cen][i];
        go(u, cen, cnt);
        heap.push(make_pair(ch[cnt].size(), cnt));
        ++cnt;
    }
    int last = -1;
    while (heap.size()) {
        int p = heap.top().second;
        heap.pop();
        int u = ch[p].back();
        ch[p].pop_back();
        if (last == -1) {
            ++col;
            last = p;
        } else {
            if (ch[p].size() > 0) {
                heap.push(make_pair(ch[p].size(), p));
            }
            if (ch[last].size() > 0) {
                heap.push(make_pair(ch[last].size(), last));
            }
            last = -1;
        }
        ans[u] = col;
    }
    for (int i = 0; i < n; ++i) {
        printf("%d%c", ans[i], i == n - 1 ? '\n' : ' ');
    }
    return 0;
}
