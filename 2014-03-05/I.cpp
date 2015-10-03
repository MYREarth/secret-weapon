#include<vector>
#include<cstdio>
#include<cassert>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 105;

int n;
char s1[N], s2[N];

int b[N], d[N];

inline int num(char ch) {
    if (ch == 'A') {
        return 0;
    } else if (ch == 'T') {
        return 1;
    } else if (ch == 'G') {
        return 2;
    } else {
        return 3;
    }
}

int dp[N][405][2];
pair<int, int> path[N][405][2];
bool vis[N][405][2];

void update(int i, int j, int k, int val, pair<int, int> p) {
    if (!vis[i][j][k] || val < dp[i][j][k]) {
        vis[i][j][k] = true;
        dp[i][j][k] = val;
        path[i][j][k] = p;
    }
}

int ss[N];

int main() {
    scanf("%s%s", s1, s2);
    n = strlen(s1);
    b[0] = 0;
    for (int i = 1; i <= n; ++i) {
        b[i] = num(s1[i - 1]) - num(s2[i - 1]);
    }
    for (int i = 0; i <= n; ++i) {
        d[i] = ((b[i + 1] - b[i]) % 4 + 4) % 4;
    }
    vis[0][200][0] = true;
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= 400; ++j) {
            for (int k = 0; k <= 1; ++k) {
                if (vis[i][j][k]) {
                    for (int u2 = 0; u2 <= 1; ++u2) {
                        for (int u1 = -3; u1 <= 3; ++u1) {
                            int cur = (u2 * 2 + u1 + d[i]) % 4;;
                            if (cur == 0) {
                                update(i + 1, j + u1, k ^ u2, dp[i][j][k] + abs(u1) + abs(u2), make_pair(u1, u2));
                            }
                        }
                    }
                }
            }
        }
    }
    printf("%d\n", dp[n + 1][200][0] / 2);
    vector<pair<pair<int, int>, int> > ans;
    vector<int> s;
    int j = 200, k = 0;
    for (int i = n + 1; i > 0; --i) {
        int u2 = path[i][j][k].second, u1 = path[i][j][k].first;
        if (u2) {
            s.push_back(i - 1);
        }
        ss[i - 1] = u1;
        j -= u1, k ^= u2;
    }
    assert(s.size() % 2 == 0);
    sort(s.begin(), s.end());
    for (int i = 0; i < (int)s.size(); i += 2) {
        ans.push_back(make_pair(make_pair(s[i] + 1, s[i + 1]), 2));
    }
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            if (ss[i] > 0 && ss[j] < 0) {
                ans.push_back(make_pair(make_pair(i + 1, j), 3));
                --ss[i], ++ss[j];
            } else if (ss[i] < 0 && ss[j] > 0) {
                ans.push_back(make_pair(make_pair(i + 1, j), 1));
                ++ss[i], --ss[j];
            }
        }
    }
    for (int i = 0; i < (int)ans.size(); ++i) {
        printf("%d %d %d\n", ans[i].first.first, ans[i].first.second, ans[i].second);
    }
    return 0;
}
