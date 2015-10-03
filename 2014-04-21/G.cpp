#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

#define next NEXT


int n, m;

const int dx[] = {0, 0, -1, 1}, dy[] = {-1, 1, 0, 0};

bool inmap(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m;
}

const int N = 1005;

int next[N][N][4][5];

int wall[N][N];
char map[N][N];

void init() {
    for (int d = 0; d < 4; ++d) {
        int sx = 0, tx = n - 1, sy = 0, ty = m - 1;
        if (dx[d] == 1) {
            swap(sx, tx);
        }
        if (dy[d] == 1) {
            swap(sy, ty);
        }
        for (int i = sx; ; i += (dx[d] ? -dx[d] : 1)) {
            for (int j = sy; ; j += (dy[d] ? -dy[d] : 1)) {
                for (int num = 0; num < 5; ++num) {
                    int x = i + dx[d], y = j + dy[d];
                    if (!inmap(x, y)) {
                        next[i][j][d][num] = -1;
                        continue;
                    }
                    if (map[x][y] == '1' + num) {
                        next[i][j][d][num] = ((x == i) ? y : x);
                    } else {
                        next[i][j][d][num] = next[x][y][d][num];
                    }
                }
                if (j == ty) {
                    break;
                }
            }
            if (i == tx) {
                break;
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            wall[i + 1][j + 1] = (wall[i + 1][j] + wall[i][j + 1] - wall[i][j] + (map[i][j] == '#'));
        }
    }
}

bool blocked(int x1, int y1, int x2, int y2) {
    if (x1 > x2) {
        swap(x1, x2);
    }
    if (y1 > y2) {
        swap(y1, y2);
    }
    int ret = (wall[x2 + 1][y2 + 1] - wall[x1][y2 + 1] - wall[x2 + 1][y1] + wall[x1][y1]);
    return ret != 0;
}

const int K = 105;
int k;
int dir[K], len[K];

int l;
char s[K];

int tx[K], ty[K];

pair<int, int> getnext(int x, int y, int d, int num) {
//cout << "getnext" << ' ' << x << ' ' << y << ' ' << d << ' ' << num << endl;
    if (dx[d] == 0) {
        return make_pair(x, next[x][y][d][num]);
    } else {
        return make_pair(next[x][y][d][num], y);
    }
}

bool between(pair<int, int> p, int x1, int y1, int x2, int y2, int d) {
    int x = p.first, y = p.second;
//cout << "between" << ' ' << x << ' ' << y << endl;
    if (x == -1 || y == -1) {
        return false;
    }
    if (dx[d] == 1) {
        return (y == y1 && y1 == y2) && (x1 < x && x <= x2);
    }
    if (dx[d] == -1) {
        return (y == y1 && y1 == y2) && (x2 <= x && x < x1);
    }
    if (dy[d] == 1) {
        return (y1 < y && y <= y2) && (x1 == x && x == x2);
    }
    if (dy[d] == -1) {
        return (y2 <= y && y < y1) && (x == x1 && x1 == x2);
    }
    return false;
}

bool check(int sx, int sy) {
    int x = sx, y = sy, p = 0;
    if (map[x][y] == '#') {
        return false;
    }
    if (map[x][y] == s[p]) {
        ++p;
    }
    tx[0] = x, ty[0] = y;
    for (int i = 0; i < k; ++i) {
        tx[i + 1] = tx[i] + dx[dir[i]] * len[i];
        ty[i + 1] = ty[i] + dy[dir[i]] * len[i];
        if (!inmap(tx[i + 1], ty[i + 1])) {
            return false;
        }
        if (blocked(tx[i], ty[i], tx[i + 1], ty[i + 1])) {
            return false;
        }
    }
//cout << "CHECK" << endl;
//cout << sx << ' ' << sy << endl;
    for (int i = 0; i < k; ++i) {
        while (p != l && between(getnext(x, y, dir[i], s[p] - '1'), x, y, tx[i + 1], ty[i + 1], dir[i])) {
            pair<int, int> to = getnext(x, y, dir[i], s[p] - '1');
            x = to.first, y = to.second;
//cout << ' ' << x << ' ' << y << ' ' << map[x][y] << endl;
            ++p;
        }
        x = tx[i + 1];
        y = ty[i + 1];
//cout << x << ' ' << y << endl;
    }
//cout << "succ" << ' ' << p << endl;
    return p == l;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i) {
        scanf("%s", map[i]);
    }
    init();
    scanf("%d", &k);
    for (int i = 0; i < k; ++i) {
        int l;
        char op[2];
        scanf("%s%d", op, &l);
        if (*op == 'L') {
            dir[i] = 0;
        } else if (*op == 'R') {
            dir[i] = 1;
        } else if (*op == 'U') {
            dir[i] = 2;
        } else if (*op == 'D') {
            dir[i] = 3;
        }
        len[i] = l;
    }
    scanf("%s", s);
    l = strlen(s);
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            ans += check(i, j);
        }
    }
    printf("%d\n", ans);
    return 0;
}
/*
CHECK
1 1
getnext 1 1 0 1
between 1 0
getnext 1 1 0 1
 1 0 2
getnext 1 0 0 0
between 1 0
1 0
getnext 1 0 1 0
between 1 1
getnext 1 0 1 0
 1 1 1
getnext 1 1 1 2
between 1 0
1 2
getnext 1 2 2 2
between 0 2
getnext 1 2 2 2
 0 2 3
0 2
succ 4
CHECK
3 1
getnext 3 1 0 0
between 3 0
getnext 3 1 0 0
 3 0 1
getnext 3 0 0 1
between 3 0
3 0
getnext 3 0 1 1
between 3 0
3 2
getnext 3 2 2 1
between 0 2
2 2
succ 1
CHECK
3 2
getnext 3 2 0 1
between 3 0
3 1
getnext 3 1 1 1
between 3 0
3 3
getnext 3 3 2 1
between 0 3
2 3
succ 1
1
*/
