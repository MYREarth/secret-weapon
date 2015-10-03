#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int n, m;

const int N = 100005;
int ord[N], a[N], rank[N];

bool by_a(int i, int j) {
    return a[i] < a[j];
}

pair<int, int> ans[N];

#define left LEFT
#define right RIGHT

vector<pair<int, int> > left[N], right[N];

int tr[N];

void insert(int pos) {
    ++pos;
    while (pos <= n) {
        ++tr[pos];
        pos += pos & -pos;
    }
}

int query(int pos) {
    int ret = 0;
    while (pos) {
        ret += tr[pos];
        pos -= pos & -pos;
    }
    return ret;
}

int query(int l, int r) {
    return query(r + 1) - query(l);
}

int main() {
    freopen("subsorting.in", "r", stdin);
    freopen("subsorting.out", "w", stdout);
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
        ord[i] = i;
    }
    sort(ord, ord + n, by_a);
    for (int i = 0; i < m; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        --u, --v;
        if (u < v) {
            left[u].push_back(make_pair(v, i));
        } else {
            right[u].push_back(make_pair(v, i));
        }
    }
    for (int i = 0; i < n; ++i) {
        int u = ord[i];
        for (int j = 0; j < (int)left[u].size(); ++j) {
            int v = left[u][j].first, id = left[u][j].second;
            if (query(u, n - 1) < v - u) {
                ans[id].first = ans[id].second = -1;
            } else {
                ans[id].first = u;
                int l = v, r = n - 1;
                while (l < r) {
                    int mid = l + r >> 1;
                    if (query(u, mid) >= v - u) {
                        r = mid;
                    } else {
                        l = mid + 1;
                    }
                }
                ans[id].second = l;
            }
        }
        insert(u);
    }
    memset(tr, 0, sizeof(tr));
    for (int i = 0; i < n; ++i) {
        int u = ord[n - i - 1];
        for (int j = 0; j < (int)right[u].size(); ++j) {
            int v = right[u][j].first, id = right[u][j].second;
            if (query(0, u) < u - v) {
                ans[id].first = ans[id].second = -1;
            } else {
                ans[id].second = u;
                int l = 0, r = v;
                while (l < r) {
                    int mid = l + r + 1 >> 1;
                    if (query(mid, u) >= u - v) {
                        l = mid;
                    } else {
                        r = mid - 1;
                    }
                }
                ans[id].first= l;
            }
        }
        insert(u);
    }
    for (int i = 0; i < m; ++i) {
        if (ans[i].first == -1) {
            printf("%d\n", -1);
        } else {
            printf("%d %d\n", ans[i].first + 1, ans[i].second + 1);
        }
    }
    return 0;
}
