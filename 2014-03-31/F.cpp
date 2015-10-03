#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 1005;
int n, s, k;

vector<int> row[N];

int cost[N][N];

int tr[N];

int ask(int pos) {
    int ret = 0;
    while (pos) {
        ret += tr[pos];
        pos -= pos & -pos;
    }
    return ret;
}

void inc(int pos) {
    while (pos <= n) {
        ++tr[pos];
        pos += pos & -pos;
    }
}

const int K = 55, INF = 1000000000;
int dp[N][K];

int main() {
    freopen("flight.in", "r", stdin);
    freopen("flight.out", "w", stdout);
    scanf("%d%d%d", &n, &s, &k);
    for (int i = 0; i < n; ++i) {
        int r;
        scanf("%d", &r);
        row[r - 1].push_back(i + 1);
    }
    for (int i = 0; i < s; ++i) {
        memset(tr, 0, sizeof(tr));
        for (int j = i; j < s; ++j) {
            cost[i][j] = i == j ? 0 : cost[i][j - 1];
            for (int l = 0; l < (int)row[j].size(); ++l) {
                cost[i][j] += ask(row[j][l]);
            }
            for (int l = 0; l < (int)row[j].size(); ++l) {
                inc(row[j][l]);
            }
        }
    }
    for (int i = 0; i <= s; ++i) {
        for (int j = 0; j <= k; ++j) {
            dp[i][j] = INF;
        }
    }
    dp[0][0] = 0;
    for (int i = 0; i < s; ++i) {
        for (int j = 0; j < k; ++j) {
            if (dp[i][j] == INF) {
                continue;
            }
            for (int l = i; l < s; ++l) {
                dp[l + 1][j + 1] = min(dp[l + 1][j + 1], dp[i][j] + cost[i][l]);
            }
        }
    }
    printf("%d\n", dp[s][k]);
    return 0;
}
