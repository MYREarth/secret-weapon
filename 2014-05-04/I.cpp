#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 4005;
int n;
long long a[N], s[N];

int dp[N][N], fa[N][N];

int ord[N];

bool by_sum(int i, int j) {
    return s[i] < s[j] || s[i] == s[j] && i < j;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%lld", a + i);
    }
    ord[n] = n;
    for (int i = n - 1; i >= 0; --i) {
        ord[i] = i;
        s[i] = s[i + 1] + a[i];
    }
    sort(ord, ord + n + 1, by_sum);
    for (int i = 0; i < n; ++i) {
        dp[i][n] = 1;
        fa[i][n] = n;
    }
    for (int j = n - 1; j >= 0; --j) {
        int ord_k = 0, best = -(1 << 30), f = -1;
        for (int ord_i = n; ord_i >= 0; --ord_i) {
            int i = ord[ord_i];
            if (i >= j) {
                continue;
            }
            while (ord_k <= n && (ord[ord_k] <= j || s[j] * 2 - s[i] > s[ord[ord_k]])) {
                if (ord[ord_k] > j) {
                    if (dp[j][ord[ord_k]] + 1 > best) {
                        f = ord[ord_k];
                    }
                    best = max(best, dp[j][ord[ord_k]] + 1);
                }
                ++ord_k;
            }
            dp[i][j] = best;
            fa[i][j] = f;
        }
    }
    int ans = 0, cnt = -1;
    for (int i = 0; i <= n; ++i) {
        if (dp[0][i] > ans) {
            cnt = i;
        }
        ans = max(ans, dp[0][i]);
    }
    printf("%d\n", ans);
    vector<int> anss;
    int l = 0, r = cnt;
    while (r != n) {
        int k = fa[l][r];
        l = r, r = k;
        anss.push_back(l);
    }
    for (int i = 0; i < (int)anss.size(); ++i) {
        printf("%d%c", anss[i], i == (int)anss.size() - 1 ? '\n' : ' ');
    }
    return 0;
}
