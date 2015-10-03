#include<map>
#include<cmath>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

double in() {
    int a;
    scanf("%d", &a);
    return (double)a / 100;
}

const int M = 150;

double a[M][M];

void gauss(int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            if (fabs(a[i][i]) < fabs(a[j][i])) {
                for (int k = i; k <= n; ++k) {
                    swap(a[i][k], a[j][k]);
                }
            }
        }
        for (int j = i + 1; j < n; ++j) {
            double r = a[j][i] / a[i][i];
            for (int k = i; k <= n; ++k) {
                a[j][k] -= r * a[i][k];
            }
        }
    }
    for (int i = n - 1; i >= 0; --i) {
        a[i][n] /= a[i][i];
        a[i][i] = 1;
        for (int j = i - 1; j >= 0; --j) {
            a[j][n] -= a[i][n] * a[j][i];
            a[j][i] = 0;
        }
    }
}

#define tie TIE
double win[2], tie[2];

double g[2][2];

bool impossible(int a, int b, int g) {
    return a == g && b == g || a == g && b == g - 1 || a == g - 1 && b == g;
}

bool over(int a, int b, int g) {
    return a == g || b == g;
}

bool special(int a, int b) {
    return a == 7 && b == 5 || a == 6 && b == 5 || a == 6 && b == 6 || a == 5 && b == 6 || a == 5 && b == 7;
}

void cal() {
    for (int i = 0; i < 2; ++i) {
        memset(a, 0, sizeof(a));
        int cnt = 2;
        map<pair<int, int>, int> mem;
        for (int p0 = 0; p0 <= 4; ++p0) {
            for (int p1 = 0; p1 <= 4; ++p1) {
                if (impossible(p0, p1, 4)) {
                    continue;
                }
                if (over(p0, p1, 4)) {
                    if (p0 > p1) {
                        mem[make_pair(p0, p1)] = 0;
                    } else {
                        mem[make_pair(p0, p1)] = 1;
                    }
                } else {
                    mem[make_pair(p0, p1)] = cnt++;
                }
            }
        }
        for (int p0 = 0; p0 < 4; ++p0) {
            for (int p1 = 0; p1 < 4; ++p1) {
                if (!mem.count(make_pair(p0, p1))) {
                    continue;
                }
                int u = mem[make_pair(p0, p1)], v1, v2;
                double win = g[0][(p0 + p1) % 2];
                if (p0 == 3 && p1 == 3) {
                    v1 = mem[make_pair(3, 2)], v2 = mem[make_pair(2, 3)];
                } else {
                    v1 = mem[make_pair(p0 + 1, p1)], v2 = mem[make_pair(p0, p1 + 1)];
                }
                a[v1][u] += win, a[v2][u] += 1 - win;
            }
        }
        for (int i = 0; i < cnt; ++i) {
            a[i][i] -= 1;
        }
        a[2][cnt] = -1;
        gauss(cnt);
        win[i] = a[0][cnt];
        swap(g[0][0], g[1][0]);
        swap(g[0][1], g[1][1]);
    }

    for (int i = 0; i < 2; ++i) {
        memset(a, 0, sizeof(a));
        int cnt = 2;
        map<pair<pair<int, int>, int>, int> mem;
        for (int p0 = 0; p0 <= 7; ++p0) {
            for (int p1 = 0; p1 <= 7; ++p1) {
                if (impossible(p0, p1, 7)) {
                    continue;
                }
                if (special(p0, p1)) {
                    for (int k = 0; k < 2; ++k) {
                        if (over(p0, p1, 7)) {
                            if (p0 > p1) {
                                mem[make_pair(make_pair(p0, p1), k)] = 0;
                            } else {
                                mem[make_pair(make_pair(p0, p1), k)] = 1;
                            }
                        } else {
                            mem[make_pair(make_pair(p0, p1), k)] = cnt++;
                        }
                    }
                } else {
                    int k = (p0 + p1 + 1) / 2 % 2;
                    if (over(p0, p1, 7)) {
                        if (p0 > p1) {
                            mem[make_pair(make_pair(p0, p1), k)] = 0;
                        } else {
                            mem[make_pair(make_pair(p0, p1), k)] = 1;
                        }
                    } else {
                        mem[make_pair(make_pair(p0, p1), k)] = cnt++;
                    }
                }
            }
        }
        for (int p0 = 0; p0 < 7; ++p0) {
            for (int p1 = 0; p1 < 7; ++p1) {
                for (int k = 0; k < 2; ++k) {
                    if (!mem.count(make_pair(make_pair(p0, p1), k))) {
                        continue;
                    }
                    int u = mem[make_pair(make_pair(p0, p1), k)], v1, v2, nk = ((p0 + p1 + 1) % 2) ^ k;
                    double win = g[k][(p0 + p1) % 2];
                    if (p0 == 6 && p1 == 6) {
                        v1 = mem[make_pair(make_pair(6, 5), nk)], v2 = mem[make_pair(make_pair(5, 6), nk)];
                    } else {
                        v1 = mem[make_pair(make_pair(p0 + 1, p1), nk)], v2 = mem[make_pair(make_pair(p0, p1 + 1), nk)];
                    }
                    a[v1][u] += win, a[v2][u] += 1 - win;
                }
            }
        }
        for (int i = 0; i < cnt; ++i) {
            a[i][i] -= 1;
        }
        a[2][cnt] = -1;
        gauss(cnt);
        tie[i] = a[0][cnt];
        swap(g[0][0], g[1][0]);
        swap(g[0][1], g[1][1]);
    }
}

double prob[8][8];

bool isover_set(int a, int b) {
    return a == 7 || b == 7 || max(a, b) == 6 && abs(a - b) >= 2;
}

void solve() {
    memset(prob, 0, sizeof(prob));
    prob[0][0] = 1;
    for (int a = 0; a <= 7; ++a) {
        for (int b = 0; b <= 7; ++b) {
            if (isover_set(a, b)) {
                continue;
            }
            int who = (a + b) % 2;
            double succ;
            if (a == 6 && b == 6) {
                succ = tie[who];
            } else {
                succ = win[who];
            }
            prob[a + 1][b] += prob[a][b] * succ;
            prob[a][b + 1] += prob[a][b] * (1 - succ);
        }
    }
}

int main() {
    freopen("tennis.in", "r", stdin);
    freopen("tennis.out", "w", stdout);
    g[0][0] = in(), g[0][1] = in(), g[1][0] = 1 - in(), g[1][1] = 1 - in();
    cal();
    double ans0 = 1, ans1 = 1;
    int a, b;
    while (scanf("%d:%d", &a, &b) == 2) {
        solve();
        ans0 *= prob[a][b];
        ans1 *= prob[b][a];
        if ((a + b) % 2 == 1) {
            swap(win[0], win[1]);
            swap(tie[0], tie[1]);
        }
    }
    printf("%.18f\n", ans0 + ans1);
    return 0;
}

