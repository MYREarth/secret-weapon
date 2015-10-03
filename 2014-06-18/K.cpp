#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;


const int N = 50;
int n;

vector<int> h[N];

int m;

const int M = 50 * 50, INF = 1000000000;
vector<int> s[M];
int dp[M][N];

void update(int &a, int b) {
    a = max(a, b);
}

int main() {
    while (scanf("%d", &n) == 1) {
        vector<int> hei;
        for (int i = 0, k; i < n; ++i) {
            h[i].clear();
            scanf("%d", &k);
            for (int j = 0, a; j < k; ++j) {
                scanf("%d", &a);
                if (j == 0 || a != h[i].back()) {
                    h[i].push_back(a);
                    hei.push_back(a);
                }
            }
        }
        sort(hei.begin(), hei.end());
        hei.erase(unique(hei.begin(), hei.end()), hei.end());
        m = hei.size();
        for (int i = 0; i < m; ++i) {
            s[i].clear();
            for (int j = 0; j < n; ++j) {
                dp[i][j] = -INF;
            }
        }
        int split = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < (int)h[i].size(); ++j) {
                int u = lower_bound(hei.begin(), hei.end(), h[i][j]) - hei.begin();
                s[u].push_back(i);
                ++split;
            }
        }
        split -= n;
        for (int i = 0; i < (int)s[0].size(); ++i) {
            int u = s[0][i];
            dp[0][u] = 0;
        }
        for (int i = 0; i + 1 < m; ++i) {
            for (int j = 0; j < (int)s[i].size(); ++j) {
                int u = s[i][j];
                if (s[i + 1].size() == 1) {
                    int v = s[i + 1][0];
                    update(dp[i + 1][v], dp[i][u] + (u == v));
                } else {
                    bool same = false;
                    for (int k = 0; k < (int)s[i + 1].size(); ++k) {
                        int v = s[i + 1][k];
                        same = same || u == v;
                    }
                    for (int k = 0; k < (int)s[i + 1].size(); ++k) {
                        int v = s[i + 1][k];
                        update(dp[i + 1][v], dp[i][u] + (same && u != v));
                    }
                }
            }
        }
        int ans = 0;
        for (int i = 0; i < (int)s[m - 1].size(); ++i) {
            int u = s[m - 1][i];
            ans = max(ans, dp[m - 1][u]);
        }
        static int id = 0;
        printf("Case %d: %d\n", ++id, n - 1 + 2 * (split - ans));
    }
    return 0;
}
