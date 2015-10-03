#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 1000005;

int n;

int v[N];

vector<int> edge[N];

int tr[N];

void inc(int pos, int val) {
    while (pos < N) {
        tr[pos] += val;
        pos += pos & -pos;
    }
}

int ask(int pos) {
    int ret = 0;
    while (pos) {
        ret += tr[pos];
        pos -= pos & -pos;
    }
    return ret;
}

int s;

int fa[N];
vector<pair<int, int> > stack;

long long ans;

void solve() {
    fa[0] = -1;
    stack.push_back(make_pair(0, 0));
    while (stack.size()) {
        int u = stack.back().first, i = stack.back().second;
        if (i == 0) {
            int t = s - v[u];
            if (t >= 0) {
                ans += ask(t);
            }
            inc(v[u], 1);
        }
        if (i == edge[u].size()) {
            stack.pop_back();
            inc(v[u], -1);
            continue;
        }
        int v = edge[u][i];
        ++stack.back().second;
        if (v == fa[u]) {
            continue;
        }
        fa[v] = u;
        stack.push_back(make_pair(v, 0));
    }
}

int main() {
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
    scanf("%d%d", &n, &s);
    for (int i = 1; i < n; ++i) {
        int f;
        scanf("%d", &f);
        --f;
        edge[f].push_back(i);
        edge[i].push_back(f);
    }
    for (int i = 0; i < n; ++i) {
        scanf("%d", v + i);
    }
    solve();
    cout << ans << endl;
    return 0;
}
