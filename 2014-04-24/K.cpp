#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int L = 100000 << 1, MOD = 1000000007;

struct SegTree {
    int a[2][L], sum[2][L], dot[L];

    SegTree () {
        memset(a, 0, sizeof(a));
        memset(sum, 0, sizeof(sum));
        memset(dot, 0, sizeof(dot));
    }

    inline int getID (int l, int r) {
        return l + r | l != r;
    }

    void cover(int d, int l, int r, int s) {
        int i = getID(l, r);
        (a[d][i] += s) %= MOD;
        (sum[d][i] += (long long)s * (r - l + 1) % MOD) %= MOD;
        (dot[i] += (long long)s * sum[1 ^ d][i] % MOD) %= MOD;
    }

    void update(int l, int r) {
        int m = l + r >> 1;
        int i = getID(l, r), lc = getID(l, m), rc = getID(m + 1, r);
        for (int k = 0; k < 2; ++k) {
            sum[k][i] = (sum[k][lc] + sum[k][rc]) % MOD;
        }
        dot[i] = (dot[lc] + dot[rc]) % MOD;
    }

    void pushdown(int l, int r) {
        int i = getID(l, r);
        for (int k = 0; k < 2; ++k) {
            if (a[k][i]) {
                int m = l + r >> 1;
                cover(k, l, m, a[k][i]);
                cover(k, m + 1, r, a[k][i]);
                a[k][i] = 0;
            }
        }
    }

    void add(int l, int r, int d, int a, int b, int s) {
        if (b < l || r < a) {
            return;
        }
        if (a <= l && r <= b) {
            cover(d, l, r, s);
            return;
        }
        pushdown(l, r);
        int m = l + r >> 1;
        add(l, m, d, a, b, s);
        add(m + 1, r, d, a, b, s);
        update(l, r);
    }

    int ask(int l, int r, int a, int b) {
        if (b < l || r < a) {
            return 0;
        }
        if (a <= l && r <= b) {
            return dot[getID(l ,r)];
        }
        pushdown(l, r);
        int m = l + r >> 1;
        return (ask(l, m, a, b) + ask(m + 1, r, a, b)) % MOD;
    }
};

SegTree tr;

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    while (m--) {
        char op[2];
        int l, r;
        scanf("%s%d%d", op, &l, &r);
        --l, --r;
        if (op[0] == '?') {
            printf("%d\n", tr.ask(0, n - 1, l, r));
        } else {
            int x;
            scanf("%d", &x);
            tr.add(0, n - 1, op[0] == '.', l, r, x);
        }
    }
    return 0;
}
