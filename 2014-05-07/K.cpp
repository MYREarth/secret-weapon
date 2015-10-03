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
    if (u < v) {
        swap(u, v);
    }
    fa[u] = v;
}

vector<pair<long long, long long> > p;

inline long long dis (const int &i, const int &j) {
    return (p[i].first - p[j].first) * (p[i].first - p[j].first) + (p[i].second - p[j].second) * (p[i].second - p[j].second);
}

int old_cnt, old_fa[N];

void backup() {
    old_cnt = 0;
    for (int i = 0; i < n; ++i) {
        old_fa[i] = find(i);
        if (i == old_fa[i]) {
            ++old_cnt;
        }
    }
}

const int BAR = 15000000;
int top, record[BAR][2];
long long len[BAR];

bool check(long long d, long long &bar, long long &bar1) {
    top = 0;
    bar = 0;
    int cnt = 0;
    for (int i = 0, j; i < n; ++i) {
        fa[i] = old_fa[i];
        cnt += (fa[i] == i);
        for (j = i - 1; j >= 0 && (p[i].first - p[j].first) * (p[i].first - p[j].first) <= d && cnt > 1; --j) {
            if (find(i) != find(j)) {
                long long dd = dis(i, j);
                if (dd <= d) {
                    bar = max(bar, dd);
                    merge(find(i), find(j));
                    --cnt;
                } else {
                    record[top][0] = i, record[top][1] = j;
                    len[top] = dd;
                    ++top;
                }
            }
        }
        if (j >= 0 && find(i) != find(j)) {
            record[top][0] = i, record[top][1] = j;
            len[top] = (p[i].first - p[j].first) * (p[i].first - p[j].first);
            ++top;
        }
        if (cnt == 1) {
            top = 0;
        }
    }
    if (cnt > 1) {
        bar1 = 1ll << 60;
        for (int i = 0; i < top; ++i) {
            int u = record[i][0], v = record[i][1];
            if (find(u) != find(v)) {
                bar1 = min(bar1, len[i]);
            }
        }
    }
    return cnt == 1;
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
    sort(p.begin(), p.end());
    long long l = 1, r = 0;
    for (int i = 0; i + 1 < n; ++i) {
        r = max(r, dis(i, i + 1));
    }
    for (int i = 0; i < n; ++i) {
        fa[i] = i;
    }
    backup();
    bool last = true;
    while (l < r) {
        long long m = last ? ((l + r) / 2) : (l + r * 3) / 4, bar, bar1;
//cout << l << ' ' << r << ' ' << m << endl;
        if (check(m, bar, bar1)) {
            last = true;
            r = bar;
        } else {
            l = bar1;
            last = false;
            backup();
        }
    }
    printf("%lld\n", r);
    return 0;
}
