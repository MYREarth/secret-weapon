#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 6;
int n, m;

int pos[N][N];

int cnt;
pair<int, int> unzip[5005];
int zip[1 << 19 | 1];
bool isfinal[5005];

int trans[5005][N][2];

void init() {
    int cnt1 = 0;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < i; ++j) {
            pos[i][j] = pos[j][i] = cnt1++;
        }
    }
    cnt = 0;
    int mm = m * (m - 1) / 2;
    for (int st = 0; st < (1 << mm); ++st) {
        bool discard = false;
        for (int a = 0; a < m && !discard; ++a) {
            for (int b = 0; b < m && !discard; ++b) {
                if (a != b && (~st >> pos[a][b] & 1)) {
                    for (int c = 0; c < m && !discard; ++c) {
                        if (c != a && c != b && (st >> pos[a][c] & 1) && (st >> pos[b][c] & 1)) {
                            discard = true;
                        }
                    }
                }
            }
        }
        if (discard) {
            continue;
        }
        for (int i = 0; i < m; ++i) {
            discard = false;
            for (int j = i + 1; j < m; ++j) {
                if (st >> pos[i][j] & 1) {
                    discard = true;
                }
            }
            if (discard) {
                continue;
            }
            for (int block = 0; block <= 1; ++block) {
                isfinal[cnt] = (i == m - 1) && !block;
                unzip[cnt] = make_pair(st << 1 | block, i);
                zip[(st << 1 | block) << 3 | i] = cnt++;
            }
        }
    }
    memset(trans, -1, sizeof(trans));
    for (int state = 0; state < cnt; ++state) {
        int st = unzip[state].first >> 1, i = unzip[state].second, block = unzip[state].first & 1;
        for (int j = 0; j < m; ++j) {
            //black
            {
                int nst = st;
                for (int k = 0; k < m; ++k) {
                    if (j == k) {
                        continue;
                    }
                    if (nst >> pos[j][k] & 1) {
                        nst ^= 1 << pos[j][k];
                    }
                }
                if (j == i) {
                    int ni = -1;
                    for (int k = 0; k < m; ++k) {
                        if (j == k) {
                            continue;
                        }
                        if (st >> pos[j][k] & 1) {
                            ni = k;
                        }
                    }
                    if (ni != -1) {
                        trans[state][j][0] = zip[(nst << 1 | 1) << 3 | ni];
                    }
                } else {
                    trans[state][j][0] = zip[(nst << 1 | 1) << 3 | i];
                }
            }
            //white
            {
                int nst = st;
                if (!block && j != 0) {
                    for (int a = 0; a < m; ++a) {
                        if (a == j || st >> pos[a][j] & 1) {
                            for (int b = 0; b < m; ++b) {
                                if (b == j - 1 || st >> pos[b][j - 1] & 1) {
                                    if (a != b) {
                                        nst |= 1 << pos[a][b];
                                    }
                                }
                            }
                        }
                    }
                }
                int ni = i;
                for (int k = i + 1; k < m; ++k) {
                    if (nst >> pos[k][i] & 1) {
                        ni = k;
                    }
                }
                trans[state][j][1] = zip[(nst << 1) << 3 | ni];
            }
        }
    }
}

int ma[N][N];

double dp[2][5005];

double p() {
    memset(dp, 0, sizeof(dp));
    int now = 0;
    dp[now][0] = 1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            double p0 = (double)ma[i][j] / 10, p1 = 1 - p0;
            int next = now ^ 1;
            for (int st = 0; st < cnt; ++st) {
                if (trans[st][j][0] != -1) {
                    dp[next][trans[st][j][0]] += dp[now][st] * p0;
                }
                if (trans[st][j][1] != -1) {
                    dp[next][trans[st][j][1]] += dp[now][st] * p1;
                }
                dp[now][st] = 0;
            }
            now = next;
        }
    }
    double ret = 0;
    for (int st = 0; st < cnt; ++st) {
        if (isfinal[st]) {
            ret += dp[now][st];
        }
    }
    return ret;
}

int main() {
   // freopen("maze.in", "r", stdin);
   // freopen("maze.out", "w", stdout);
    scanf("%d%d", &n, &m);
    init();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            double d;
            scanf("%lf", &d);
            ma[i][j] = d * 10 + 1e-6;
        }
    }
    double p_pass = p();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (i == 0 && j == 0 || i == n - 1 && j == m - 1 || ma[i][j] == 0) {
                printf("%.6f", 0.0);
            } else if (ma[i][j] == 10) {
                printf("%.6f", 1.0);
            } else {
                int rem = ma[i][j];
                ma[i][j] = 10;
                double p_blocked_pass = p();
                ma[i][j] = rem;
                double p_block = (double)ma[i][j] / 10;
                printf("%.6f", p_blocked_pass * p_block / p_pass);
            }
            printf("%c", j == m - 1 ? '\n' : ' ');
        }
    }
    return 0;
}

