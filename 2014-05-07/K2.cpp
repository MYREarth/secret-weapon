#include<cmath>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int n;
long long a;

const int N = 100005;

int fa[N];

int find(int u) {
    return u == fa[u] ? u : fa[u] = find(fa[u]);
}

void merge(int u, int v) {
    fa[u] = v;
}

vector<pair<long long, long long> > p;

int ord[N];

bool by_y(int i, int j) {
    return p[i].second < p[j].second;
}

int main() {
    scanf("%d%lld", &n, &a);
    vector<long long> b;
    for (int i = 0; i < n * 2; ++i) {
        a = a * 279470273ll % 4294967291ll;
        b.push_back(a % 1000000);
    }
    for (int i = 0; i + 1 < (int)b.size(); i += 2) {
        p.push_back(make_pair(b[i], b[i + 1]));
    }
    vector<pair<long long, pair<long long, long long> > > edge;
    sort(p.begin(), p.end());
    for (int i = 0; i < n; ++i) {
        fa[i] = i;
        for (int j = max(0, i - 200); j < i; ++j) {
            edge.push_back(make_pair((p[i].first - p[j].first) * (p[i].first - p[j].first) +
                                     (p[i].second - p[j].second) * (p[i].second - p[j].second),
                                     make_pair(i, j)));
        }
    }
    for (int i = 0; i < n; ++i) {
        ord[i] = i;
    }
    sort(ord, ord + n, by_y);
    for (int _ = 0; _ < n; ++_) {
        int i = ord[_];
        for (int __ = max(0, _ - 200); __ < _; ++__) {
            int j = ord[__];
            edge.push_back(make_pair((p[i].first - p[j].first) * (p[i].first - p[j].first) +
                                     (p[i].second - p[j].second) * (p[i].second - p[j].second),
                                     make_pair(i, j)));
        }
    }
    sort(edge.begin(), edge.end());
    long long ans = 0;
    for (int i = 0; i < (int)edge.size(); ++i) {
        int u = edge[i].second.first, v = edge[i].second.second;
        if (find(u) != find(v)) {
            ans = edge[i].first;
            merge(find(u), find(v));
        }
    }
    printf("%lld\n", ans);
    return 0;
}
