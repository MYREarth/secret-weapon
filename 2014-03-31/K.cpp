#include<vector>
#include<cstdio>
#include<cassert>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 5005;

int dgr[N];
bool g[N][N];

int a, b, c, d, m = 0, n = 0;

bool check() {
    for (int i = 0; i < n + m; ++i) {
        int dgr1 = 0, dgr2 = 0;
        for (int j = 0; j < m; ++j) {
            dgr1 += g[i][j];
        }
        for (int j = m; j < n + m; ++j) {
            dgr2 += g[i][j];
        }
        if (i < m) {
            if (dgr1 != a || dgr2 != b) {
                cout << "HI" << endl;
                cout << i << ' ' << dgr1 << ' ' << a << ' ' << dgr2 << ' ' << b << endl;
                return false;
            }
        } else {
            if (dgr1 != d || dgr2 != c) {
                cout << i << ' ' << dgr1 << ' ' << c << ' ' << dgr2 << ' ' << d << endl;
                return false;
            }
        }
    }
    return true;
}

int ord[N];

bool bydgr(int i, int j) {
    return dgr[i] < dgr[j];
}

void build(int delta, int n, int d) {
    memset(dgr, 0, sizeof(dgr));
    for (int i = 0; i < n; ++i) {
        ord[i] = i;
    }
    for (int i = 0; i < n; ++i) {
        int mins = 0;
        for (int j = 0; j < n; ++j) {
            if (dgr[j] < dgr[mins]) {
                mins = j;
            }
        }
        assert(dgr[mins] <= d);
        int k = d - dgr[mins];
        dgr[mins] = d;
        sort(ord, ord + n, bydgr);
        for (int j = 0; j < k; ++j) {
            int u = ord[j];
            g[mins + delta][u + delta] = g[u + delta][mins + delta] = true;
            ++dgr[u];
        }
    }
}

int main() {
    freopen("kids.in", "r", stdin);
    freopen("kids.out", "w", stdout);
    scanf("%d%d%d%d", &a, &b, &c, &d);
    swap(c, d);
    bool over = false;
    while (!over) {
        ++m;
        if (m * a % 2 == 0) {
            if (m * a <= m * (m - 1)) {
                if (m * b % d == 0) {
                    n = m * b / d;
                    if (n * c % 2 == 0) {
                        if (n * c <= n * (n - 1)) {
                            if (n >= b && m >= d) {
                                build(0, m, a);
                                build(m, n, c);
                                memset(dgr, 0, sizeof(dgr));
                                for (int i = 0; i < n; ++i) {
                                    ord[i] = i;
                                }
                                for (int i = 0; i < m; ++i) {
                                    sort(ord, ord + n, bydgr);
                                    for (int j = 0; j < b; ++j) {
                                        int v = ord[j];
                                        g[i][v + m] = g[v + m][i] = true;
                                        ++dgr[v];
                                    }
                                }
                                over = true;
                            }
                        }
                    }
                }
            }
        }
    }
    printf("%d %d\n", m, n);
    for (int i = 0; i < n + m; ++i) {
        for (int j = i + 1; j < n + m; ++j) {
            if (g[i][j]) {
                printf("%d %d\n", i + 1, j + 1);
            }
        }
    }
    assert(check());
    return 0;
}

