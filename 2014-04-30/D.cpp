#include<set>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 100005;
set<pair<int, int> > g[N];

bool check(int l, int a, int b) {
    set<pair<int, int> >::iterator it = g[l].lower_bound(make_pair(a, -1));
    if (it == g[l].begin()) {
        return false;
    }
    --it;
    return it->first < a && it->second < b;
}

int ans;

int getans(int a, int b) {
    int l = 0, r = ans;
    while (l < r) {
        int m = l + r + 1 >> 1;
        if (check(m, a, b)) {
            l = m;
        } else {
            r = m - 1;
        }
    }
    return l + 1;
}

void insert(int l, int a, int b) {
    if (g[l].size() != 0) {
        set<pair<int, int> >::iterator it = g[l].upper_bound(make_pair(a, b));
        if (it != g[l].begin()) {
            --it;
            if (it->first <= a && it->second <= b) {
                return;
            }
        }
    }
    g[l].insert(make_pair(a, b));
    do {
        set<pair<int, int> >::iterator it = g[l].upper_bound(make_pair(a, b));
        if (it == g[l].end()) {
            return;
        }
        if (it->first >= a && it->second > b) {
            g[l].erase(it);
        } else {
            return;
        }
    } while (true);
}

int main() {
    ans = 0;
    int n;
    scanf("%d", &n);
    while (n--) {
        int a, b;
        scanf("%d%d", &a, &b);
        int l = getans(a, b);
        ans = max(ans, l);
        insert(l, a, b);
    }
    printf("%d\n", ans);
    return 0;
}
