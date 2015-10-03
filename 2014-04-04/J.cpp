#include<queue>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int n, m;

int ans = -1;

int xs, ys, xt, yt;

int a[52][52];

int dis[52][52][52][52];

int main() {
    scanf("%d%d", &n, &m);
    scanf("%d%d%d%d", &xs, &ys, &xt, &yt);
    int lup, ldown, lleft, lright;
    scanf("%d%d%d%d", &lup, &ldown, &lleft, &lright);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            scanf("%d", &a[i][j]);
        }
    }
    memset(dis, -1, sizeof(dis));
    dis[0][0][0][0] = 0;
    for (int i = 0; i <= lup; ++i) {
        for (int j = 0; j <= ldown; ++j) {
            for (int l = 0; l <= lleft; ++l) {
                for (int r = 0; r <= lright; ++r) {
                    if (dis[i][j][l][r] == -1) {
                        continue;
                    }
                    int x = xs - i + j, y = ys - l + r;
                    if (x == xt && y == yt) {
                        ans = max(ans, dis[i][j][l][r]);
                    }
                    if (x - 1 > 0) {
                        dis[i + 1][j][l][r] = max(dis[i + 1][j][l][r], dis[i][j][l][r] + a[x - 1][y]);
                    }
                    if (x + 1 <= n) {
                        dis[i][j + 1][l][r] = max(dis[i][j + 1][l][r], dis[i][j][l][r] + a[x + 1][y]);
                    }
                    if (y - 1 > 0) {
                        dis[i][j][l + 1][r] = max(dis[i][j][l + 1][r], dis[i][j][l][r] + a[x][y - 1]);
                    }
                    if (y + 1 <= m) {
                        dis[i][j][l][r + 1] = max(dis[i][j][l][r + 1], dis[i][j][l][r] + a[x][y + 1]);
                    }
                }
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}
