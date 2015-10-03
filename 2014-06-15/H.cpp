#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int n;

const int N = 505;
int h[N], ord[N];

const int INF = 1000000000;

bool by_h(int i, int j) {
    return h[i] < h[j];
}

int num[N];

int cost[N][N], f[N];
bool valid[N][N];

#define left LEFT

bool left[N];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", h + i);
        ord[i] = i;
    }
    sort(ord, ord + n, by_h);
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= n; ++j) {
            cost[i][j] = INF;
        }
    }
    for (int len = 1; len <= n; ++len) {
        for (int i = 0; i < n; ++i) {
            int j = i + len;
            if (j > n) {
                break;
            }
            if (i + 1 == j) {
                cost[i][j] = 0;
                valid[i][j] = h[i] == 1;
                continue;
            }
            vector<int> pos;
            for (int k = 0; k < n; ++k) {
                if (ord[k] >= i && ord[k] < j) {
                    pos.push_back(ord[k]);
                }
            }
            int l = j - i;
            bool flag = true;
            for (int k = 0; k + 1 < l; ++k) {
                if (h[pos[k]] == h[pos[k + 1]]) {
                    flag = false;
                    break;
                }
            }
            if (!flag) {
                continue;
            }
            valid[i][j] = h[pos[l - 1]] == l;
            for (int k = 0; k < l; ++k) {
                num[pos[k]] = k;
                left[k] = true;
            }
            int ans = l;
            for (int k = 1; k < l; ++k) {
                int u = num[j - k];
                left[u] = false;
                if (u == 0) {
                    ans = 0;
                }
                if (left[0]) {
                    ans = min(ans, u);
                } else {
                    while (!left[ans]) {
                        ++ans;
                    }
                }
                if (cost[i][j - k] != INF && cost[j - k][j] != INF) {
                    cost[i][j] = min(cost[i][j], cost[i][j - k] + cost[j - k][j] + l - ans);
                }
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        f[i] = INF;
        for (int j = 0; j < i; ++j) {
            if (valid[j][i]) {
                f[i] = min(f[i], f[j] + cost[j][i]);
            }
        }
    }
    if (f[n] == INF) {
        printf("impossible\n");
    } else {
        printf("%d\n", f[n]);
    }
    return 0;
}
