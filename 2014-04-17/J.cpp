#include<bitset>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int L = 900, N = 30;

int n, m;

bool see[N][N][N][N];

bitset<L> map, block[N][N << 1];

const int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};

int det(int x1, int y1, int x2, int y2) {
    return x1 * y2 - x2 * y1;
}

int sign(int x) {
    return x < 0 ? -1 : x > 0;
}

bool check(int x1, int y1, int x2, int y2, int x3, int y3) {
    x1 = x1 * 2 + 1, y1 = y1 * 2 + 1, x2 = x2 * 2 + 1, y2 = y2 * 2 + 1;
    x3 = x3 * 2, y3 = y3 * 2;
    bool appear[3];
    memset(appear, 0, sizeof(appear));
    for (int dx = 0; dx <= 1; ++dx) {
        for (int dy = 0; dy <= 1; ++dy) {
            int x = x3 + dx * 2, y = y3 + dy * 2;
            appear[sign(det(x - x1, y - y1, x2 - x1, y2 - y1)) + 1] = true;
        }
    }
    return appear[1] || appear[0] && appear[2];
}

char buf[55];

int main() {
    freopen("jealous.in","r",stdin);
    freopen("jealous.out","w",stdout);
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i) {
        scanf("%s", buf);
        for (int j = 0; j < m; ++j) {
            if (buf[j] == '#') {
                map.set(i * m + j);
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = -m + 1; j < m; ++j) {
            for (int dx = 0; dx <= i; ++dx) {
                for (int dy = 0; dy <= abs(j); ++dy) {
                    bool cross = false;
                    if (j < 0) {
                        cross = check(0, abs(j), i, 0, dx, dy);
                    } else {
                        cross = check(0, 0, i, j, dx, dy);
                    }
                    if (cross) {
                        block[i][j + m - 1].set(dx * m + dy);
                    }
                }
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            for (int x = 0; x < n; ++x) {
                for (int y = 0; y < m; ++y) {
                    if (x < i || x == i && y < j) {
                        see[i][j][x][y] = see[x][y][i][j];
                    } else {
                        int dx = x - i, dy = y - j;
                        see[i][j][x][y] = !((block[dx][dy + m - 1] << (i * m + min(j, y))) & map).any();
                    }
                }
            }
        }
    }
    vector<pair<int, int> > ans;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (map[i * m + j]) {
                continue;
            }
            vector<pair<int, int> > pos;
            pos.push_back(make_pair(i, j));
            for (int d = 0; d < 4; ++d) {
                int x = i, y = j;
                do {
                    x += dx[d], y += dy[d];
                    if (x >= 0 && x < n && y >= 0 && y < m && !map[x * m + y]) {
                        pos.push_back(make_pair(x, y));
                    } else {
                        break;
                    }
                } while (true);
            }
            bool find = false;
            for (int x = 0; x < n && !find; ++x) {
                for (int y = 0; y < m && !find; ++y) {
                    if (map[x * m + y] || x == i && y == j) {
                        continue;
                    }
                    bool guard = true;
                    for (int k = 0; k < (int)pos.size() && guard; ++k) {
                        guard = see[x][y][pos[k].first][pos[k].second];
                    }
                    if (guard) {
                        find = true;
                    }
                }
            }
            if (!find) {
                ans.push_back(make_pair(i, j));
            }
        }
    }
    printf("%d\n", (int)ans.size());
    for (int i = 0; i < (int)ans.size(); ++i) {
        printf("%d %d\n", ans[i].first + 1, ans[i].second + 1);
    }
    return 0;
}
