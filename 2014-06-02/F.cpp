#include<deque>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int n;

const int N = 2005;

long long a[N], sum[N];

int ord[N];

bool by_sum(int i, int j) {
    return sum[i] < sum[j];
}

const long long INF = 1ll << 60;

long long dp[N][N];

long double cal(int j, int k1, int k2) {
    long long d1 = sum[k1] - sum[j], d2 = sum[k2] - sum[j],
              a1 = dp[j][k1], a2 = dp[j][k2];
    if (d1 == d2) {
        if (a1 <= a2) {
            return -1e100;
        } else {
            return 1e100;
        }
    } else {
        return (long double)(a2 - a1) / (d1 - d2);
    }
}

long long cal2(int i, int j, int k) {
    return (sum[j] - sum[i]) * (sum[k] - sum[j]) + dp[j][k];
}

int main() {
    scanf("%d", &n);
    sum[0] = 0;
    for (int i = 0; i < n; ++i) {
        scanf("%lld", a + i);
        sum[i + 1] = sum[i] + a[i];
        ord[i + 1] = i + 1;
    }
    sort(ord, ord + n + 1, by_sum);
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= n; ++j) {
            dp[i][j] = -INF;
        }
    }
    for (int i = 0; i <= n; ++i) {
        dp[i][n] = 0;
    }
    for (int i = n - 1; i >= 0; --i) {
        vector<int> que, line;
        for (int j = 0; j <= n; ++j) {
            int u = ord[j];
            if (u > i) {
                line.push_back(u);
            } else if (u < i) {
                que.push_back(u);
            }
        }
        reverse(que.begin(), que.end());
        deque<int> q;
        for (int j = 0; j < (int)line.size(); ++j) {
            int u = line[j];
            while (q.size() > 1 && cal(i, q[q.size() - 2], q[q.size() - 1]) > cal(i, q[q.size() - 1], u)) {
                q.pop_back();
            }
            q.push_back(u);
        }
        for (int j = 0; j < (int)que.size(); ++j) {
            int u = que[j];
            while (q.size() > 1 && cal2(u, i, q[0]) <= cal2(u, i, q[1])) {
                q.pop_front();
            }
            dp[u][i] = cal2(u, i, q[0]);
        }
    }
    long long ans = -INF;
    for (int i = 1; i <= n; ++i) {
        ans = max(ans, dp[0][i]);
    }
    printf("%lld\n", ans);
    return 0;
}
