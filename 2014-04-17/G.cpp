#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int n, m;

const int N = 1005, M = 10;

int d;

double p[N][M], sum[M];

int ord[N];

bool by_d(int i, int j) {
    return p[i][d] < p[j][d];
}

int ans[N];

double norm[M];

bool issmall[M];

double cost[N];

bool by_c(int i, int j) {
    return cost[i] < cost[j];
}

int main() {
    freopen("genome.in", "r", stdin);
    freopen("genome.out", "w", stdout);
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i) {
        ord[i] = i;
        for (int j = 0; j < m; ++j) {
            scanf("%lf", &p[i][j]);
            sum[j] += p[i][j];
        }
    }
    memset(ans, -1, sizeof(ans));
    d = 0;
    for (int i = 0; i < m; ++i) {
        if (sum[i] > sum[d]) {
            d = i;
        }
    }
    sort(ord, ord + n, by_d);
    int divide = -1;
    double ccost = 0;
    for (int i = 0; i < n - 1; ++i) {
        /*
        if (i < n * 0.28 || i > n * 0.52) {
            continue;
        }
        */
        double ncost = p[ord[i + 1]][d] - p[ord[i]][d];
        if (divide == -1 || ccost < ncost) {
            divide = i + 1;
            ccost = ncost;
        }
    }
    memset(sum, 0, sizeof(sum));
    for (int i = 0; i < divide; ++i) {
        ans[ord[i]] = 0;
        for (int j = 0; j < m; ++j) {
            sum[j] += p[ord[i]][j];
        }
    }
    double s = 0, s1 = 0;
    for (int i = 0; i < m; ++i) {
        s1 += sum[i];
        if (i == d) {
            continue;
        }
        s += sum[i];
    }
    for (int i = 0; i < m; ++i) {
        if (sum[i] / s1 * 100 < 16) {
            issmall[i] = true;
        }
        norm[i] = sum[i] / s * 100;
    }
    for (int _ = divide; _ < n; ++_) {
        int i = ord[_];
        double s = 0;
        for (int j = 0; j < m; ++j) {
            if (j == d) {
                continue;
            }
            s += p[i][j];
        }
        for (int j = 0; j < m; ++j) {
            p[i][j] = p[i][j] / s * 100;
        }
        cost[i] = 0;
        for (int j = 0; j < m; ++j) {
            if (j == d) {
                continue;
            }
            cost[i] += fabs(p[i][j] - norm[j]) * (issmall[j] * 5 + 1);
        }
    }
    sort(ord + divide, ord + n, by_c);
    int divide2 = -1;
    double dcost = 0;
    for (int i = divide; i < n - 1; ++i) {
        double ncost = (cost[ord[i + 1]] - cost[ord[i]]);
        if (divide2 == -1 || dcost < ncost) {
            divide2 = i + 1;
            dcost = ncost;
        }
    }
    for (int i = divide; i < divide2; ++i) {
        ans[ord[i]] = 1;
    }
    for (int i = divide2; i < n; ++i) {
        ans[ord[i]] = 2;
    }
    for (int i = 0; i < n; ++i) {
        printf("%d\n", ans[i]);
    }
    return 0;
}
