#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int P = 40320, V = 28;

const int N = 1005;

int n;

int dp[N][N][2];

int main() {
    freopen("lord.in", "r", stdin);
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        vector<pair<int, int> > bear;
        for (int i = 0; i < n; ++i) {
            int time, dir;

            int d, m, s;
            char op[2];
            scanf("%d*%d'%d\"%s", &d, &m, &s, op);

            int sign = op[0] == 'N' ? -1 : 1;
            time = (3600 * 90 + sign * (d * 3600 + m * 60 + s)) * (P / 90 / 4 / V);

            scanf("%d*%d'%d\"%s", &d, &m, &s, op);
            sign = op[0] == 'W' ? -1 : 1;
            dir = sign * (d * 3600 + m * 60 + s);
            if (dir < 0) {
                dir = 360 * 3600 + dir;
            }

            bear.push_back(make_pair(dir, time));
        }
        bear.push_back(make_pair(0, 0));
        bear.push_back(make_pair(360 * 3600, 0));
        sort(bear.begin(), bear.end());
        n = bear.size() - 1;
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= n; ++j) {
                for (int c = 0; c < 2; ++c) {
                    dp[i][j][c] = -1;
                }
            }
        }
        dp[0][n][1] = 0, dp[0][n][0] = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = n; j > i + 1; --j) {
                for (int d = 0; d < 2; ++d) {
                    if (dp[i][j][d] == -1) {
                        continue;
                    }
                    int cur = d ? bear[j].first : bear[i].first;
                    for (int c = 0; c < 2; ++c) {
                        int to = c ? bear[j - 1].first : bear[i + 1].first,
                            dis = min(abs(cur - to), 360 * 3600 - abs(cur - to)),
                            time = dis + dp[i][j][d],
                            limit = c ? bear[j - 1].second : bear[i + 1].second;
                        if (time > limit) {
                            continue;
                        }
                        int ni = c ? i : i + 1, nj = c ? j - 1 : j;
                        if (dp[ni][nj][c] == -1 || dp[ni][nj][c] > time) {
                            dp[ni][nj][c] = time;
                        }
                    }
                }
            }
        }
        bool alive = false;
        for (int i = 0; i < n; ++i) {
            alive = alive || dp[i][i + 1][0] != -1 || dp[i][i + 1][1] != -1;
        }
        puts(alive ? "ALIVE" : "EATEN");
    }
    return 0;
}
