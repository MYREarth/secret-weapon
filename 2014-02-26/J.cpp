#include<sstream>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 500005;
int n, k, a[N], next[N][20];

const int MOD = 1000000007;

int f[N], sf[N][21];

const long long INF = 1000000000000000001ll;

long long g[N], sg[N][20];

void add(long long &a, long long b) {
    if (a == INF || b == INF) {
        a = INF;
    } else {
        a = a + b;
        if (a >= INF) {
            a = INF;
        }
    }
}

char buffer[1500005];

int top, ans[N];

int main() {
    //FILE FILE FILE FILE FILE FILE
    freopen("subsequence.in", "r", stdin);
    freopen("subsequence.out", "w", stdout);
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; ++i) {
        scanf("%d", a + i + 1);
    }
    for (int i = 0; i < 20; ++i) {
        next[n][i] = n + 1;
    }
    for (int i = n - 1; i >= 0; --i) {
        for (int j = 0; j < 20; ++j) {
            next[i][j] = next[i + 1][j];
        }
        next[i][a[i + 1]] = i + 1; 
    }
    f[n] = 1; g[n] = 1;
    for (int i = n - 1; i >= 0; --i) {
        if (i) {
            f[i] = 1; g[i] = 1;
        }
        for (int j = 0; j < 20; ++j) {
            if (next[i][j] != n + 1) {
                (f[i] += f[next[i][j]]) %= MOD;
                add(g[i], g[next[i][j]]);
            }
        }
    }
    for (int i = 0; i <= n; ++i) {
        sf[i][0] = 0;
        sg[i][0] = 0;
        for (int j = 0; j < 20; ++j) {
            sf[i][j + 1] = sf[i][j];
            if (j) {
                sg[i][j] = sg[i][j - 1];
            }
            if (next[i][j] != n + 1) {
                (sf[i][j + 1] += f[next[i][j]]) %= MOD;
                add(sg[i][j], g[next[i][j]]);
            }
        }
    }
    for (int i = 0; i < k; ++i) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            gets(buffer); 
            int pos = 0, rank = 0;
            int tmp = 0, l = strlen(buffer), st = 0;
            while (buffer[st] == ' ') {
                ++st;
            }
            for (int j = st; j <= l; ++j) {
                if (buffer[j] >= '0' && buffer[j] <= '9') {
                    tmp = tmp * 10 + (buffer[j] - '0');
                } else {
                    ++rank;
                    (rank += sf[pos][tmp]) %= MOD;
                    pos = next[pos][tmp];
                    tmp = 0;
                }
            }
            printf("%d\n", rank); 
        } else {
            long long y;
            top = 0;
            scanf("%lld", &y);
            int pos = 0;
            while (y) {
                int tmp = 0; 
                tmp = lower_bound(sg[pos], sg[pos] + 20, y) - sg[pos];
                if (tmp) {
                    y -= sg[pos][tmp - 1];
                }
                pos = next[pos][tmp];
                ans[top++] = a[pos];
                --y;
            }
            for (int j = 0; j < top; ++j) {
                printf("%d%c", ans[j], j == top - 1 ? '\n' : ' ');
            }
        }
    }
    return 0;
}
