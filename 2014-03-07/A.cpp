#include<cstdio>
#include<cstring>
#include<cassert>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 1005;

const int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
int n, m;
bool swaped;
char ans[N][N];

int stamp, used[26];

void putans(int x1, int y1, int x2, int y2) {
    if (swaped) {
        swap(x1, y1), swap(x2, y2);
    }
    ++stamp;
    for (int d = 0; d < 4; ++d) {
        int xx = x1 + dx[d], yy = y1 + dy[d];
        if (xx >= 0 && yy >= 0 && ans[xx][yy] != 0) {
            used[ans[xx][yy] - 'a'] = stamp;
        }
        xx = x2 + dx[d], yy = y2 + dy[d];
        if (xx >= 0 && yy >= 0 && ans[xx][yy] != 0) {
            used[ans[xx][yy] - 'a'] = stamp;
        }
    }
    for (int i = 0; i < 26; ++i) {
        if (used[i] != stamp) {
            ans[x1][y1] = ans[x2][y2] = i + 'a';
            return ;
        }
    }
}

void make_rect_0(int n, int m) {
    //n, m % 2 == 0 && n >= m
    int k = m / 2;
    for (int i = k; i >= 1; --i) {
        int pos = k - i;
        for (int j = 0; j < i; ++j) {
            putans(n - 1 - (k - i), pos, n - 1 - (k - i), pos + 1);
            putans(k - i, pos, k - i, pos + 1);
            pos += 2;
        }
    }
    if (!swaped) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (ans[i][j] == 0) {
                    putans(i, j, i + 1, j);
                }
            }
        }
    } else {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (ans[j][i] == 0) {
                    putans(i, j, i + 1, j);
                }
            }
        }
    }
}

void make_rect_1(int n, int m) {
    //n % 2 == 1
    int k = m / 2;
    for (int i = k; i >= 1 && (n - (k - i) > (k - i)); --i) {
        int pos = k - i;
        for (int j = 0; j < i; ++j) {
            if (i != k) {
                putans(n - (k - i), pos, n - (k - i), pos + 1);
            }
            putans(k - i, pos, k - i, pos + 1);
            pos += 2;
        }
    }
    if (!swaped) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (ans[i][j] == 0) {
                    putans(i, j, i + 1, j);
                }
            }
        }
    } else {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (ans[j][i] == 0) {
                    putans(i, j, i + 1, j);
                }
            }
        }
    }
}

bool check(int n, int m) {
    for (int i = 0; i + 1 < n; ++i) {
        bool flag = false;
        for (int j = 0; j < m; ++j) {
            flag = flag || ans[i][j] == ans[i + 1][j];
        }
        if (!flag) {
            return false;
        }
    }
    for (int i = 0; i + 1 < m; ++i) {
        bool flag = false;
        for (int j = 0; j < n; ++j) {
            flag = flag || ans[j][i] == ans[j][i + 1];
        }
        if (!flag) {
            return false;
        }
    }
    return true;
}

int main() {
    freopen("domino.in", "r", stdin);
    freopen("domino.out", "w", stdout);
    swaped = false;
    scanf("%d%d", &n, &m);
    if (n == 1 && m == 2) {
        printf("aa\n");
        return 0;
    }
    if (n == 2 && m == 1) {
        printf("a\na\n");
        return 0;
    }
    if (n * m % 2 == 1) {
        return 0;
    }
    if (min(n, m) < 5) {
        return 0;
    }
    if (n == 6 && m == 6) {
        return 0;
    }
    if (n % 2 == 0 && m % 2 == 0) {
        if (n < m) {
            swaped = true;
            swap(n, m);
        }
        make_rect_0(n, m - 2);
        putans(0, m - 2, 1, m - 2);
        putans(0, m - 1, 1, m - 1);
        putans(2, m - 2, 2, m - 1);

        putans(3, m - 3, 3, m - 2);
        putans(4, m - 3, 4, m - 2);
        putans(3, m - 1, 4, m - 1);
        for (int i = 5; i + 1 < n; i += 2) {
            putans(i, m - 2, i + 1, m - 2);
            putans(i, m - 1, i + 1, m - 1);
        }
        putans(n - 3, m - 2, n - 3, m - 1);
        putans(n - 2, m - 2, n - 1, m - 2);
        putans(n - 2, m - 1, n - 1, m - 1);
    } else {
        if (m % 2 == 1) {
            swaped = true;
            swap(n, m);
        }
        make_rect_1(n, m - 2);
        putans(0, m - 2, 1, m - 2);
        putans(0, m - 1, 1, m - 1);
        putans(2, m - 2, 2, m - 1);
        for (int i = 3; i < n; i += 2) {
            putans(i, m - 2, i + 1, m - 2);
            putans(i, m - 1, i + 1, m - 1);
        }
        putans(n - 2, m - 3, n - 2, m - 2);
        putans(n - 1, m - 3, n - 1, m - 2);
        putans(n - 2, m - 1, n - 1, m - 1);
    }
    if (swaped) {
        swap(n, m);
    }
    assert(check(n, m));
    for (int i = 0; i < n; ++i) {
        printf("%s\n", ans[i]);
    }
    return 0;
}
