#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int P = 1000005, N = 61;

int f[P], pos[P];

long long dp[2][P][2];

int n, a, b, c, p, t;

int main() {
    freopen("puzzle.in", "r", stdin);
    freopen("puzzle.out", "w", stdout);
    scanf("%d%d%d%d%d%d", &n, &a, &b, &c, &p, &t);
    memset(pos, -1, sizeof(pos));
    f[0] = a, pos[a] = 0;
    int mul = a, loop = 0;
    for (int i = 1; i < P; ++i) {
        mul = ((long long)mul * b + c) % p;
        if (pos[mul] != -1) {
            loop = i;
            break;
        }
        f[i] = mul, pos[mul] = i;
    }
    int now = 0;
    for (int i = 1; i <= n; ++i) {
        int prec = now ^ 1;
        memset(dp[now], 0, sizeof(dp[now]));
        for (int j = 0; j < p; ++j) {
            int ori = (f[j] >= t), lc = (2 * j + 1) % loop, rc = (2 * j + 2) % loop;
            if (ori == 0) {
                dp[now][j][0] = dp[prec][lc][0] + dp[prec][rc][0];
                dp[now][j][1] = dp[prec][lc][1] + dp[prec][rc][1] + 1;
            } else {
                dp[now][j][0] = dp[prec][lc][0] + dp[prec][rc][1] + 1;
                dp[now][j][1] = dp[prec][lc][0] + dp[prec][rc][1];
            }
        }
        now = prec;
    }
    cout << dp[now ^ 1][0][0] << endl;
    return 0;
}
