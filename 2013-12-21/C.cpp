#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 1001, MOD = 1000000007;

const int NB[5][2] = {{5, 4}, {6, 3}, {7, 2}, {8, 1}, {9, 0}};

int n, cnt[10], que;
int binom[N][N];

char s[100005];

int f[6][N][4];

void trans(int i, int left, int cur, int tar) {
    if (f[i][left][cur] == 0) {
        return;
    }
//cout << i << ' ' << left << ' ' << cur << ' ' << f[i][left][cur] << endl;
    if (i != 4) {
        int num1 = NB[i][0], num2 = NB[i][1];
        for (int j = 0; j <= left; ++j) {
            int has1 = j + (cur == 1 && tar == 2), has2 = j + (cur == 0 && tar == 1);
            if (cnt[num1] > has1 || cnt[num2] > has2) {
                continue;
            }
            int use = has1 + has2 - cnt[num1] - cnt[num2];
            if (use > left) {
                continue;
            }
            (f[i + 1][left - use][tar] += (long long)binom[left][has1 - cnt[num1]] * binom[left - has1 + cnt[num1]][has2 - cnt[num2]] % MOD * f[i][left][cur] % MOD) %= MOD;
        }
    } else {
        for (int j = 0; j <= left + 1; ++j) {
            int has1 = j + (cur == 1 && tar == 2), has2 = j + (cur == 0 && tar == 1);
            if (cnt[9] > has1) {
                continue;
            }
            if (has1 - cnt[9] + max(0, has2 - cnt[0]) > left) {
                continue;
            }
            (f[i + 1][0][tar] += (long long)binom[left][has1 - cnt[9]] * f[i][left][cur] % MOD) %= MOD;
        }
    }
}

int main() {
    freopen("can.in", "r", stdin);
    freopen("can.out", "w", stdout);
    scanf("%s", s); 
    n = strlen(s) / 2;
    que = 0;
    memset(cnt, 0, sizeof(cnt));
    for (int i = 0; i < n * 2; ++i) {
        if (s[i] == '?') {
            ++que;
        } else {
            ++cnt[s[i] - '0'];
        }
    }
    for (int i = 0; i < 5; ++i) {
        int num1 = NB[i][0], num2 = NB[i][1];
        int tmp = min(cnt[num1], cnt[num2]);
        if (i == 4) {
            tmp = max(0, tmp - 1);
        }
        cnt[num1] -= tmp, cnt[num2] -= tmp;
    }
    for (int i = 0; i <= 1000; ++i) {
        binom[i][0] = binom[i][i] = 1;
        for (int j = 1; j < i; ++j) {
            binom[i][j] = (binom[i - 1][j] + binom[i - 1][j - 1]) % MOD;
        }
    }
    f[0][que][0] = 1;
    int num1 = 5, num2 = 4;
    for (int j = 0; j <= que; ++j) {
        int has1 = j + 2, has2 = j;
        if (cnt[num1] > has1 || cnt[num2] > has2) {
            continue;
        }
        int use = has1 + has2 - cnt[num1] - cnt[num2];
        if (use > que) {
            continue;
        }
        (f[1][que - use][2] += (long long)binom[que][has1 - cnt[num1]] * binom[que - has1 + cnt[num1]][has2 - cnt[num2]] % MOD * f[0][que][0] % MOD) %= MOD;
    }
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j <= que; ++j) {
            trans(i, j, 0, 0); 
            trans(i, j, 0, 1);
            trans(i, j, 1, 2);
            trans(i, j, 2, 2);
        }
    }
    printf("%d\n", f[5][0][2]);
    return 0;
}
