#include<cmath>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int hp_p, hp_e, t, p, vp[10], pp[10][10], d[10][10], p_e, a, c[6][6];

const int N = 101;
bool vis[N][N];

double dp[N][N];

double solve(int hp_p, int hp_e) {
    if (vis[hp_p][hp_e]) {
        return dp[hp_p][hp_e];
    }
    vis[hp_p][hp_e] = true;
    dp[hp_p][hp_e] = 0;
    for (int i = 0; i < t; ++i) {
        for (int j = 0; j < p; ++j) {
            double self = 0, win = 0;
            for (int k = 0; k <= vp[i]; ++k) {
                double cp = c[vp[i]][k] * pow((double)pp[i][j] / 100, k) * pow((double)(100 - pp[i][j]) / 100, vp[i] - k);
                int dmg = k * d[i][j];
                if (hp_e <= dmg) {
                    win += cp;
                } else {
                    double cp1 = cp * (1 - (double)p_e / 100);
                    if (dmg) {
                        win += cp1 * solve(hp_p, hp_e - dmg);
                    } else {
                        self += cp1;
                    }
                    double cp2 = cp * (double)p_e / 100;
                    if (hp_p > a) {
                        win += cp2 * solve(hp_p - a, hp_e - dmg);
                    }
                }
            }
            if (self < 1 - 1e-6) {
                win /= (1 - self);
            }
            dp[hp_p][hp_e] = max(dp[hp_p][hp_e], win);
        }
    }
    return dp[hp_p][hp_e];
}

int main() {
    for (int i = 0; i <= 5; ++i) {
        c[i][i] = c[i][0] = 1;
        for (int j = 1; j < i; ++j) {
            c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
        }
    }
    freopen("whats.in", "r", stdin);
    freopen("whats.out", "w", stdout);
    scanf("%d%d", &hp_p, &hp_e);
    scanf("%d%d", &t, &p);
    for (int i = 0; i < t; ++i) {
        scanf("%d", vp + i);
        for (int j = 0; j < p; ++j) {
            scanf("%d%d", &pp[i][j], &d[i][j]);
        }
    }
    scanf("%d%d", &p_e, &a);
    printf("%.12f\n", solve(hp_p, hp_e));
    return 0;
}
