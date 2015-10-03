#include<deque>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

typedef deque<pair<int, int> > Grid;

const int N = 105;

Grid g[N];

Grid operator + (const Grid &a, const Grid &b) {
    Grid ret;
    for (int i = 0; i + 1 < (int)a.size(); ++i) {
        ret.push_back(a[i]);
    }
    int l = a.back().first, h = a.back().second;
    for (int i = 1; i < (int)b.size(); ++i) {
        ret.push_back(make_pair(l + b[i].first, h + b[i].second));
    }
    return ret;
}

Grid operator | (const Grid &a, const Grid &b) {
    Grid ret;
    ret.push_back(make_pair(0, 0));
    int la = a.back().first, lb = b.back().first,
        ha = a.back().second, hb = b.back().second;
    ret.push_back(make_pair(1, 0));
    for (int i = 1; i + 1 < (int)a.size(); ++i) {
        ret.push_back(make_pair(a[i].first + lb, a[i].second));
    }
    for (int i = 1; i + 1 < (int)b.size(); ++i) {
        ret.push_back(make_pair(b[i].first, b[i].second + ha + 1));
    }
    ret.push_back(make_pair(la + lb - 1, ha + hb + 1));
    ret.push_back(make_pair(la + lb, ha + hb + 1));
    return ret;
}

int main() {
    freopen("grid.in", "r", stdin);
    freopen("grid.out", "w", stdout);
    g[0].push_back(make_pair(0, 0));
    g[0].push_back(make_pair(1, 0));
    g[0].push_back(make_pair(2, 0));
    int n;
    while (scanf("%d", &n) == 1 && n > -1) {
        for (int i = 1; i <= n; ++i) {
            char op[2];
            int a, b;
            scanf("%s%d%d", op, &a, &b);
            if (op[0] == '+') {
                g[i] = g[a] + g[b];
            } else if (op[0] == '|') {
                g[i] = g[a] | g[b];
            }
        }
        printf("%d\n", (int)g[n].size());
        for (int i = 0; i < (int)g[n].size(); ++i) {
            printf("%d %d\n", g[n][i].first, g[n][i].second);
        }
        for (int i = 1; i <= n; ++i) {
            g[i].clear();
        }
    }
    return 0;
}
