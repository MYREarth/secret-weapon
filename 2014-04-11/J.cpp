#include<queue>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 1005, M = 10005, L = 41;

int n, m, l, s;

int mask[N];

vector<pair<int, int> > edge[N];

char train[L];

int cnt[L][26];

bool check (int u, int l, int r) {
    int m = 0;
    for (int i = 0; i < 26; ++i) {
        if (cnt[r][i] > cnt[l][i]) {
            m |= 1 << i;
        }
    }
    return (mask[u] & m) == m;
}

const int INF = 1000000000;

int dp[N][L][L];

int main() {
    freopen("waste.in", "r", stdin);
    while (scanf("%d%d%d%d", &n, &m, &l, &s) == 4 && n) {
        --s;
        for (int i = 0; i < n; ++i) {
            mask[i] = 0;
            int k;
            char col[27];
            scanf("%d", &k);
            if (k) {
                scanf("%s", col);
                for (int j = 0; j < k; ++j) {
                    mask[i] |= 1 << (col[j] - 'a');
                }
            }
        }
        for (int i = 0; i < n; ++i) {
            edge[i].clear();
        }
        for (int i = 0; i < m; ++i) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            --u, --v;
            edge[v].push_back(make_pair(u, w));
            edge[u].push_back(make_pair(v, w));
        }
        scanf("%s", train);
        for (int i = 0; i < l; ++i) {
            for (int j = 0; j < 26; ++j) {
                cnt[i + 1][j] = cnt[i][j];
            }
            ++cnt[i + 1][train[i] - 'a'];
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j <= l; ++j) {
                for (int k = 0; k <= l; ++k) {
                    dp[i][j][k] = INF;
                }
                dp[i][j][j] = 0;
            }
        }
        int li = l;
        for (int len = 1; len <= l; ++len) {
            for (int l = 0; l + len <= li; ++l) {
                int r = l + len;
                for (int i = 0; i < n; ++i) {
                    if (check(i, l, r)) {
                        dp[i][l][r] = 0;
                    } else {
                        for (int j = l + 1; j < r; ++j) {
                            dp[i][l][r] = min(dp[i][l][r], dp[i][l][j] + dp[i][j][r]);
                        }
                    }
                }
                priority_queue<pair<int, int> > heap;
                for (int i = 0; i < n; ++i) {
                    heap.push(make_pair(-dp[i][l][r], i));
                }
                while (heap.size()) {
                    int d = -heap.top().first, u = heap.top().second;
                    heap.pop();
                    if (dp[u][l][r] != d) {
                        continue;
                    }
                    for (int j = 0; j < (int)edge[u].size(); ++j) {
                        int v = edge[u][j].first, nd = d + edge[u][j].second;
                        if (dp[v][l][r] > nd) {
                            dp[v][l][r] = nd;
                            heap.push(make_pair(-dp[v][l][r], v));
                        }
                    }
                }
            }
        }
        printf("%d\n", dp[s][0][l] == INF ? -1 : dp[s][0][l]);
    }
    return 0;
}
