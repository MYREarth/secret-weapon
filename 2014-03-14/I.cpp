#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int n, s, m;
vector<pair<int, int> > mark;

const int N = 100005 << 1, LOG = 19;
int table[N][LOG];

int nn;

void build() {
    nn = mark.size();
    for (int i = 0; i < nn; ++i) {
        table[i][0] = mark[i].second;
    }
    for (int i = 1; (1 << i) <= nn; ++i) {
        for (int j = 0; j + (1 << i) <= nn; ++j) {
            table[j][i] = max(table[j][i - 1], table[j + (1 << i - 1)][i - 1]);
        }
    }
}

int getmax(int l, int r) {
    int gap = 0;
    while (l + (1 << gap) < r - (1 << gap) + 1) {
        ++gap;
    }
//cout << l << ' ' << r << ' ' << gap << endl;
//cout << table[l][gap] << ' ' << table[r - (1 << gap) + 1][gap] << endl;
    return max(table[l][gap], table[r - (1 << gap) + 1][gap]);
}

int main() {
    /*
    freopen("intercity.in", "r", stdin);
    freopen("intercity.out", "w", stdout);
    */
    scanf("%d%d%d", &n, &s, &m);
    vector<pair<int, int> > evt;
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        scanf("%d%d%d", &c, &a, &b);
        evt.push_back(make_pair(a, c));
        evt.push_back(make_pair(b, -c));
    }
    sort(evt.begin(), evt.end());
    int cur = 0;
    for (int i = 0; i < (int)evt.size(); ++i) {
        int j = i;
        while (j < (int)evt.size() && evt[j].first == evt[i].first) {
            cur += evt[j].second;
            ++j;
        }
        if (j == evt.size()) {
            mark.push_back(make_pair(n, cur));
        } else {
            mark.push_back(make_pair(evt[j].first - 1, cur));
        }
        i = j - 1;
    }
for (int i = 0; i < (int)mark.size(); ++i) {
    printf("%d %d\n", mark[i].first, mark[i].second);
}
cout << endl;
    build();
    int p = 0, q;
    scanf("%d", &q);
    while (q--) {
        int a, b, x, y;
        scanf("%d%d", &x, &y);
        a = x + p, b = y + p - 1;
cout << a << ' ' << b << endl;
        a = lower_bound(mark.begin(), mark.end(), make_pair(a, -1)) - mark.begin();
        b = lower_bound(mark.begin(), mark.end(), make_pair(b, -1)) - mark.begin();
cout << s << endl;
        int ans = s - getmax(a, b);
        printf("%d\n", p = ans < 0 ? 0 : ans);
    }
    return 0;
}
