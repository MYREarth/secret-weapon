#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

typedef unsigned long long HASH;
const HASH MAGIC = 37;

const int N = 100005;
char s[N];
int n, m, a[N];

HASH h[N], pow[N];

HASH gethash(int i, int l) {
    return h[i + l] - h[i] * pow[l];
}

int lcp(int i, int j) {
    int l = 0, r = n - max(i, j);
    while (l < r) {
        int mid = l + r + 1 >> 1;
        if (gethash(i, mid) == gethash(j, mid)) {
            l = mid;
        } else {
            r = mid - 1;
        }
    }
    return l;
}
bool cmp(int i, int j) {
    if (s[i] != s[j]) {
        return s[i] < s[j];
    }
    int l = lcp(i, j);
    return s[i + l] < s[j + l];
}

int go1[N], go2[N];

inline int getID(int l, int r) {
    return l + r | l != r;
}

int sum[N << 1], tag[N << 1];

void update(int l, int r) {
    int m = l + r >> 1;
    sum[getID(l, r)] = sum[getID(l, m)] + sum[getID(m + 1, r)];
}

void covern(int l, int r, int t) {
    tag[getID(l, r)] = t + 1;
    sum[getID(l, r)] = (r - l + 1) * t;
}

void push_down(int l, int r) {
    int i = getID(l, r), m = l + r >> 1;
    if (tag[i]) {
        covern(l, m, tag[i] - 1);
        covern(m + 1, r, tag[i] - 1);
        update(l, r);
        tag[i] = 0;
    }
}

void cover(int l, int r, int a, int b, int t) {
    if (b < l || r < a) {
        return;
    }
    if (a <= l && r <= b) {
        covern(l, r, t);
        return;
    } else {
        push_down(l, r);
        int m = l + r >> 1;
        cover(l, m, a, b, t);
        cover(m + 1, r, a, b, t);
        update(l, r);
    }
}

int query(int l, int r, int a, int b) {
    if (b < l || r < a) {
        return 0;
    }
    if (a <= l && r <= b) {
        return sum[getID(l, r)];
    } else {
        push_down(l, r);
        int m = l + r >> 1;
        return query(l, m, a, b) + query(m + 1, r, a, b);
    }
}

int main() {
    freopen("substrings.in", "r", stdin);
    freopen("substrings.out", "w", stdout);
    scanf("%s", s);
    n = strlen(s);
    pow[0] = 1;
    for (int i = 0; i < n; ++i) {
        pow[i + 1] = pow[i] * MAGIC;
        h[i + 1] = h[i] * MAGIC + (s[i] - 'a' + 1);
    }
    scanf("%d", &m);
    for (int i = 0; i < m; ++i) {
        scanf("%d", a + i);
        --a[i];
    }
    vector<int> pos;
    int last0 = n, last1 = n, p = m - 1;
    for (int i = n - 1; i >= 0; --i) {
        if (p >= 0 && i == a[p]) {
            last1 = last0;
            last0 = i;
            --p;
        } else {
            go1[i] = last0 - i, go2[i] = last1 - i;
            pos.push_back(i);
        }
    }
    sort(pos.begin(), pos.end(), cmp);
    long long ans = 0;
    for (int i = 0; i < (int)pos.size(); ++i) {
        int u = pos[i];
        if (i) {
            int d = lcp(u, pos[i - 1]);
  //          cout << "CUT" << ' ' << d << endl;
            cover(0, n, d, n, 0);
        }
//cout << u << ' ' << go1[u] << ' ' << go2[u] << endl;
        ans += go1[u] - query(0, n, 0, go1[u] - 1);
        if (go1[u] < go2[u] - 1) {
            ans += (go2[u] - go1[u] - 1) - query(0, n, go1[u] + 1, go2[u] - 1);
        }
        cover(0, n, 0, go1[u] - 1, 1);
        if (go1[u] < go2[u] - 1) {
            cover(0, n, go1[u] + 1, go2[u] - 1, 1);
        }
//cout << ans << endl;
    }
    cout << ans << endl;
    return 0;
}
