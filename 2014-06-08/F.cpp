#include<vector>
#include<cstdio>
#include<cassert>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int n, p, c;

const int N = 105;

int g[N][N], a[N][N];

int inverse(int a) {
    return a == 1 ? 1 : (long long)(p - p / a) * inverse(p % a) % p;
}

int cal() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            a[i][j] = g[i][j];
        }
    }
    int ret = 1;
    for (int i = 0; i < n; ++i) {
        if (!a[i][i]) {
            for (int j = i + 1; j < n; ++j) {
                if (a[j][i]) {
                    for (int k = i; k < n; ++k) {
                        swap(a[i][k], a[j][k]);
                    }
                    ret = p - ret;
                    break;
                }
            }
        }
        if (!a[i][i]) {
            return 0;
        }
        ret = (long long)ret * a[i][i] % p;
        int inv = inverse(a[i][i]);
        for (int j = i + 1; j < n; ++j) {
            if (a[j][i]) {
                int r  = (long long)inv * a[j][i] % p;
                for (int k = 0; k < n; ++k) {
                    a[j][k] = ((a[j][k] - (long long)r * a[i][k] % p) + p) % p;
                }
            }
        }
    }
    return ret;
}

int coef[1 << 5];

char buf[5];

int main() {
    freopen("finals.in", "r", stdin);
    freopen("finals.out", "w", stdout);
    scanf("%d%d%d", &n, &p, &c);
    vector<pair<int, int> > x;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int a;
            if (scanf("%d", &a) == 1) {
                g[i][j] = a;
            } else {
                scanf("%s", buf);
                x.push_back(make_pair(i, j));
            }
        }
    }
    int m = x.size();
    int min_nonzero = -1;
    for (int st = 0; st < 1 << m; ++st) {
        for (int j = 0; j < m; ++j) {
            g[x[j].first][x[j].second] = st >> j & 1;
        }
        coef[st] = cal();
        for (int stp = 0; stp < st; ++stp) {
            if ((stp & st) == stp) {
                (coef[st] -= coef[stp]) %= p;
            }
        }
        if (coef[st] < 0) {
            coef[st] += p;
        }
        if (st && coef[st] && min_nonzero == -1) {
            min_nonzero = st;
        }
    }
    if (min_nonzero == -1) {
        if (coef[0] != c) {
            printf("No");
            return 0;
        }
    } else {
        int my = 0, st = min_nonzero;
        for (int i = 0; i < m; ++i) {
            g[x[i].first][x[i].second] = st >> i & 1;
        }
        while (~st >> my & 1) {
            ++my;
        }
        g[x[my].first][x[my].second] = (long long)inverse(coef[st]) * ((c - coef[0] + p) % p) % p;
    }
assert(cal() == c);
    printf("Yes\n");
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%d%c", g[i][j], j == n - 1 ? '\n' : ' ');
        }
    }
    return 0;
}
