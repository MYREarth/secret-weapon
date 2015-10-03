#include<queue>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 505;
int n, m;

int map[N][N];
char buf[N];

bool arrive[N][N];
int fa[N][N];

const int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};

vector<pair<pair<int, int>, pair<int, int> > > ans;

void retrive(int x2, int y2) {
    while (fa[x2][y2] != -1) {
        int d = fa[x2][y2];
        int x1 = x2 - dx[d], x0 = x1 - dx[d], y1 = y2 - dy[d], y0 = y1 - dy[d];
        ans.push_back(make_pair(make_pair(x0 + 1, y0 + 1), make_pair(x1 + 1, y1 + 1)));
        x2 = x0, y2 = y0;
    }
}

int tmp[N][N];

bool check(int ansx, int ansy, int dir) {
    ans.clear();
    retrive(ansx, ansy);
    dir ? retrive(ansx, ansy + 1) : retrive(ansx + 1, ansy);
    reverse(ans.begin(), ans.end());
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            tmp[i][j] = map[i][j];
        }
    }
    for (int i = 0; i < (int)ans.size(); ++i) {
        int x0 = ans[i].first.first, y0 = ans[i].first.second, x1 = ans[i].second.first, y1 = ans[i].second.second, x2 = x1 + x1 - x0, y2 = y1 + y1 - y0;
        --x0, --y0, --x1, --y1, --x2, --y2;
        if (tmp[x0][y0] == 0 && tmp[x1][y1] == tmp[x2][y2] && tmp[x1][y1] > 0) {
            swap(tmp[x0][y0], tmp[x2][y2]);
        } else {
            return false;
        }
    }
    return tmp[ansx][ansy] == 0 && (dir ? tmp[ansx][ansy + 1] == 0 : tmp[ansx + 1][ansy] == 0);
}

int main() {
    freopen("parking.in", "r", stdin);
    freopen("parking.out", "w", stdout);
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i) {
        scanf("%s", buf);
        for (int j = 0; j < m; ++j) {
            map[i][j] = buf[j] == 'X' ? -1 : 0;
        }
    }
    int k;
    scanf("%d", &k);
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < 2; ++j) {
            int x, y;
            scanf("%d%d", &x, &y);
            --x, --y;
            map[x][y] = i + 1;
        }
    }
    memset(arrive, 0, sizeof(arrive));
    memset(fa, 0, sizeof(fa));
    queue<pair<int, int> > q;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (map[i][j] == 0) {
                q.push(make_pair(i, j));
                arrive[i][j] = true;
                fa[i][j] = -1;
            }
        }
    }
    while (q.size()) {
        int x = q.front().first, y = q.front().second;
        q.pop();
        for (int d = 0; d < 4; ++d) {
            int x1 = x + dx[d], y1 = y + dy[d], x2 = x1 + dx[d], y2 = y1 + dy[d];
            if (x1 >= 0 && x1 < n && x2 >= 0 && x2 < n && y1 >= 0 && y1 < m && y2 >= 0 && y2 < m) {
                if (map[x1][y1] == map[x2][y2] && !arrive[x2][y2] && map[x1][y1] != -1) {
                    arrive[x2][y2] = true;
                    fa[x2][y2] = d;
                    q.push(make_pair(x2, y2));
                }
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (i + 1 < n) {
                if ((map[i][j] != map[i + 1][j] || map[i][j] == 0 && map[i + 1][j] == 0) && arrive[i][j] && arrive[i + 1][j]) {
                    if (check(i, j, 0)) {
                        printf("Yes\n");
                        printf("%d\n", (int)ans.size());
                        if (ans.size()) {
                            for (int k = 0; k < (int)ans.size(); ++k) {
                                printf("%d %d %d %d\n", ans[k].first.first, ans[k].first.second, ans[k].second.first, ans[k].second.second);
                            }
                        }
                        return 0;
                    }
                }
            }
            if (j + 1 < m) {
                if ((map[i][j] != map[i][j + 1] || map[i][j] == 0 && map[i][j + 1] == 0) && arrive[i][j] && arrive[i][j + 1]) {
                    if (check(i, j, 1)) {
                        printf("Yes\n");
                        printf("%d\n", (int)ans.size());
                        if (ans.size()) {
                            for (int k = 0; k < (int)ans.size(); ++k) {
                                printf("%d %d %d %d\n", ans[k].first.first, ans[k].first.second, ans[k].second.first, ans[k].second.second);
                            }
                        }
                        return 0;
                    }
                }
            }
        }
    }
    printf("No\n");
    return 0;
}
