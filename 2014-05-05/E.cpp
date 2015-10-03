#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int data[3][6] = {1, 2, 3, 4, 5, 6, 1, 4, 5, 3, 2, 6, 2, 6, 1, 3, 4, 5};

const int N = 105;
vector<int> ans[N][3];

void build(int n) {
    int u = n * 2, v = n * 2 - 1;
    int a = 0, b, c = ans[n - 1][2][0] == ans[n - 1][0][0] ? n - 1 : 0;
    for (b = 1; b < n; ++b) {
        if (ans[n - 1][1][b - 1] != ans[n - 1][0][a] && ans[n - 1][1][b - 1] != ans[n - 1][2][c] &&
            ans[n - 1][1][b] != ans[n - 1][0][a] && ans[n - 1][1][b] != ans[n - 1][2][c]) {
            break;
        }
    }
    if (b == n) {
        return;
    }
    ans[n][0] = ans[n - 1][0];
    ans[n][1] = ans[n - 1][1];
    ans[n][2] = ans[n - 1][2];

    ans[n][0].insert(ans[n][0].begin(), u);
    ans[n][0].insert(ans[n][0].begin() + n + 1, v);
    if (c == 0) {
        ans[n][2].insert(ans[n][2].begin(), u);
        ans[n][2].insert(ans[n][2].begin() + n + 1, v);
    } else {
        ans[n][2].insert(ans[n][2].begin() + n, u);
        ans[n][2].push_back(v);
    }
    ans[n][1].insert(ans[n][1].begin() + b, u);
    ans[n][1].insert(ans[n][1].begin() + b + n, v);
}

int g[N * 2][N * 2], stamp;

bool markedge(int u, int v) {
    if (g[u][v] == stamp) {
        return false;
    }
    g[u][v] = stamp;
    return true;
}

bool check(int n) {
    ++stamp;
    for (int i = 0; i < 3; ++i) {
        if (ans[n][i].size() != n * 2) {
            return false;
        }
        for (int j = 0; j < n; ++j) {
            if (!markedge(ans[n][i][j], ans[n][i][j + 1])) {
                return false;
            }
            if (j && !markedge(ans[n][i][j], ans[n][i][j + n])) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 6; ++j) {
            ans[3][i].push_back(data[i][j]);
        }
    }
    for (int i = 3; i <= 100; ++i) {
        if (!check(i)) {
            cout << "ERROR!" << i << endl;
            return 0;
        }
        if (i != 100) {
            build(i + 1);
        }
    }
    freopen("embedding.in", "r", stdin);
    freopen("embedding.out", "w", stdout);
    int n;
    while (scanf("%d", &n) == 1 && n) {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < n * 2; ++j) {
                printf("%d%c", ans[n][i][j], j == n * 2 - 1 ? '\n' : ' ');
            }
        }
    }
    return 0;
}
