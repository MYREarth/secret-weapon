#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 32768;

int n, fa[N], lc[N], rc[N], b[N];

int cnt;

int ord[N];

void dfs(int u) {
    ord[u] = cnt;
    ++cnt;
    if(lc[u] != -1) {
        dfs(lc[u]);
        dfs(rc[u]);
    }
}

int can[N];

int solve(const vector<bool> &tr, int pos) {
    int ret = 0;
    if (tr.size() == 1) {
        if (tr[0]) {
            ret = 2;
        } else {
            ret = 1;
        }
    } else {
        int m = tr.size() >> 1;
        vector<bool> ntr(m);
        int left, right, mix, cur = tr[0];
        for (int i = 0; i < m; ++i) {
            ntr[i] = tr[1 + i];
        }
        left = solve(ntr, pos == -1 ? -1 : pos + 1);
        for (int i = 0; i < m; ++i) {
            ntr[i] = tr[1 + i + m];
        }
        right = solve(ntr, pos == -1 ? -1 : pos + 1 + m);
        for (int i = 0; i < m; ++i) {
            ntr[i] = tr[1 + i] ^ tr[1 + i + m];
        }
        mix = solve(ntr, -1);
        int c[2];
        c[1] = (~left & 1) || (~right & 1) || (~mix & 1);
        c[0] = (~left & 2) || (~right & 2) || (~mix & 2);
        if (cur) {
            swap(c[0], c[1]);
        }
        ret = c[1] << 1 | c[0];
    }
    if (pos != -1) {
        can[pos] = ret;
    }
    return ret;
}

int main() {
    scanf("%d", &n);
    memset(fa, -1, sizeof(fa));
    for (int i = 0; i < n; ++i) {
        scanf("%d%d%d", lc + i, rc + i, b + i);
        --lc[i], --rc[i];
        if (lc[i] != -1 && rc[i] != -1) {
            fa[lc[i]] = i;
            fa[rc[i]] = i;
        }
    }
    int root = 0;
    while (fa[root] != -1) {
        root = fa[root];
    }
    cnt = 0;
    dfs(root);
    vector<bool> tr(n);
    for (int i = 0; i < n; ++i) {
        tr[ord[i]] = b[i] == 1;
    }
    solve(tr, 0);
    for (int i = 0; i < n; ++i) {
        if (can[ord[i]] & 1) {
            printf("Ksusha\n");
        } else {
            printf("Sasha\n");
        }
    }
    return 0;
}
