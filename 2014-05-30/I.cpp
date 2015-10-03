#include<deque>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int n;

const int N = 10005;

int fa[N];
long long f[N];

long long cal(int u, long long x) {
    return f[u] + x * (n - u);
}

bool cmp(int u, int v, int w) {
    return (f[v] - f[u]) * (w - v) >= (f[w] - f[v]) * (v - u);
}

int main() {
    freopen("iq.in", "r", stdin);
    freopen("iq.out", "w", stdout);
    while (scanf("%d", &n) == 1 && n) {
        vector<pair<int, int> > t(n);
        for (int i = 0; i < n; ++i) {
            scanf("%d", &t[i].first);
            t[i].second = i;
        }
        sort(t.begin(), t.end());
        f[0] = 0;
        deque<int> q;
        q.push_back(0);
        for (int i = 1; i <= n; ++i) {
            while (q.size() > 1 && cal(q[0], t[i - 1].first) >= cal(q[1], t[i - 1].first)) {
                q.pop_front();
            }
            f[i] = cal(q[0], t[i - 1].first);
            fa[i] = q[0];
            while (q.size() > 1 && cmp(q[q.size() - 2], q[q.size() - 1], i)) {
                q.pop_back();
            }
            q.push_back(i);
        }
        printf("%lld\n", f[n]);
        vector<vector<int> > ans;
        int u = n;
        while (u) {
            int v = fa[u];
            vector<int> tmp;
            for (int i = v + 1; i <= u; ++i) {
                tmp.push_back(t[i - 1].second);
            }
            ans.push_back(tmp);
            u = v;
        }
        reverse(ans.begin(), ans.end());
        printf("%d\n", (int)ans.size());
        for (int i = 0; i < (int)ans.size(); ++i) {
            printf("%d", (int)ans[i].size());
            for (int j = 0; j < (int)ans[i].size(); ++j) {
                printf(" %d", ans[i][j] + 1);
            }
            printf("\n");
        }
    }
    return 0;
}
