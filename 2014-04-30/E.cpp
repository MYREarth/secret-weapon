#include<deque>
#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 645;

int n, m;

char map[N][N];

bool onboard(int x, int y) {
    return x == 0 || y == 0 || x == n - 1 || y == m - 1;
}

int dis[N][N][4];

const int dx[] = {0, 0, -1, 1}, dy[] = {-1, 1, 0, 0};

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i) {
        scanf("%s", map[i]);
    }
    int sx, sy;
    scanf("%d%d", &sx, &sy);
    --sx, --sy;
    deque<pair<pair<int, int>, int> > q;
    for (int i = 0; i < 4; ++i) {
        dis[sx][sy][i] = 1;
        q.push_back(make_pair(make_pair(sx, sy), i));
    }
    while (q.size()) {
        int x = q.front().first.first, y = q.front().first.second, od = q.front().second;
        q.pop_front();
        for (int d = 0; d < 4; ++d) {
            int tx = x + dx[d], ty = y + dy[d];
            if (tx >= 0 && ty >= 0 && tx < n && ty < m && map[tx][ty] == '0') {
                int nd = dis[x][y][od] + (d != od);
                if (dis[tx][ty][d] == 0 || dis[tx][ty][d] > nd) {
                    dis[tx][ty][d] = nd;
                    if (nd == dis[x][y][od]) {
                        q.push_front(make_pair(make_pair(tx, ty), d));
                    } else {
                        q.push_back(make_pair(make_pair(tx, ty), d));
                    }
                }
            }
        }
    }
    int ans = -1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (onboard(i, j) && map[i][j] == '0') {
                for (int k = 0; k < 4; ++k) {
                    if (dis[i][j][k] != 0) {
                        if (ans == - 1 || ans > dis[i][j][k]) {
                            ans = dis[i][j][k];
                        }
                    }
                }
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}
