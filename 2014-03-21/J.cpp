#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 105, INF = 1000005;
int n, m;
long long k;

int g[N][N];
vector<int> edge[N];

int val[N];
bool use[N];

struct Matrix {
    long long num[N][N];

    Matrix(int tag = 0) {
        memset(num, 0, sizeof(num));
        if (tag) {
            for (int i = 0; i < N; ++i) {
                num[i][i] = 1;
            }
        }
    }

    long long* operator[] (int i) {
        return num[i];
    }
};

const long long NINF = -(1ll << 60);
Matrix operator * (Matrix &a, Matrix &b) {
    Matrix ret;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            ret[i][j] = NINF;
            for (int k = 0; k < n; ++k) {
                ret[i][j] = max(ret[i][j], a[i][k] + b[k][j]);
            }
        }
    }
    return ret;
}

int valbar[N];

long long dp[N][N];

int main() {
    freopen("unpredictable.in", "r", stdin);
    freopen("unpredictable.out", "w", stdout);
    cin >> n >> m >> k;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            g[i][j] = INF;
        }
        g[i][i] = 0;
    }
    for (int i = 0; i < m; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        --u, --v;
        g[u][v] = 1;
        edge[u].push_back(v);
    }
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
            }
        }
    }
/*
for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
        printf("%d ", g[i][j]);
    }
    printf("\n");
}
*/
    for (int i = 0; i < n; ++i) {
        if (g[i][n - 1] != INF) {
            use[i] = true;
        }
    }
    for (int i = 0; i < n; ++i) {
        int cnt = 0, mins = N, mins2 = N;
        for (int j = 0; j < (int)edge[i].size(); ++j) {
            int v = edge[i][j];
            if (use[v]) {
                ++cnt;
                if (g[v][n - 1] < mins) {
                    mins2 = mins;
                    mins = g[v][n - 1];
                } else if (g[v][n - 1] < mins2) {
                    mins2 = g[v][n - 1];
                }
            }
        }
        if (use[i] && cnt >= 2) {
            val[i] = 1;
            valbar[i] = mins2 + 1;
        }
    }
/*
for (int i = 0; i < n; ++i) {
    cout << (use[i] ? 1 : 0) << ' ' << val[i] << ' ' << valbar[i] << endl;
}
*/
    Matrix a, f;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            f[i][j] = NINF;
        }
        f[i][i] = 0;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < (int)edge[i].size(); ++j) {
            int v = edge[i][j];
            f[i][v] = max(f[i][v], (long long)val[v]);
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            a[i][j] = NINF;
        }
    }
    for (int i = 0; i < n; ++i) {
        if (val[i] && k - 1 >= valbar[i]) {
            a[i][i] = 1;
        } else {
            a[i][i] = 0;
        }
    }
/*
for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
        printf("%d ", a[i][j] < 0 ? -1 : (int)a[i][j]);
    }
    printf("\n");
}
*/
    if (k > n) {
        long long t = k - n - 1;
        while (t) {
            if (t & 1) {
                a = a * f;
            }
/*
for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
        printf("%d ", f[i][j] < 0 ? -1 : (int)f[i][j]);
    }
    printf("\n");
}
printf("\n");
*/
            f = f * f;
            t >>= 1;
        }
        k = n;
    } else {
        --k;
    }
/*
for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
        printf("%d ", a[i][j] < 0 ? -1 : (int)a[i][j]);
    }
    printf("\n");
}
*/
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= n; ++j) {
            dp[i][j] = NINF;
        }
    }
    for (int i = 0; i < n; ++i) {
        dp[i][k] = 0;
        for (int j = 0; j < n; ++j) {
            dp[i][k] = max(dp[i][k], a[j][i]);
        }
    }
    for (int i = k; i > 0; --i) {
        for (int j = 0; j < n; ++j) {
            dp[j][i - 1] = max(dp[j][i - 1], dp[j][i]);
            for (int k = 0; k < (int)edge[j].size(); ++k) {
                int v = edge[j][k];
                dp[v][i - 1] = max(dp[v][i - 1], dp[j][i] + val[v] * (valbar[v] <= i - 1));
            }
        }
    }
/*
for (int i = k; i >= 0; --i) {
    for (int j = 0; j < n; ++j) {
        cout << j << ' ' << i << ' ' << dp[j][i] << endl;
    }
}
*/
    cout << dp[n - 1][0] << endl;
    return 0;
}
