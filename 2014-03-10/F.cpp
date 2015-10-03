#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int MOD = 1000000007;

bool f[2][26][26][26][26][26];

int num(char ch) {
    if (ch == 'R') {
        return 0;
    } else if (ch == 'G') {
        return 1;
    } else if (ch == 'B') {
        return 2;
    } else if (ch == 'Y') {
        return 3;
    } else if (ch == 'C') {
        return 4;
    }
    return 5;
}

int reverse(int i) {
    return i == 1 ? 1 : (long long)(MOD - MOD / i) * reverse(MOD % i) % MOD;
}

int fac[26], rev[26];

int main() {
    fac[0] = rev[0] = 1;
    for (int i = 1; i < 26; ++i) {
        fac[i] = (long long)fac[i - 1] * i % MOD;
        rev[i] = reverse(fac[i]);
    }
    freopen("patterns.in", "r", stdin);
    freopen("patterns.out", "w", stdout);
    int n;
    scanf("%d", &n);
    int now = 0;
    f[now][0][0][0][0][0] = true;
    char p[7];
    for (int i = 0; i < n * n; ++i) {
        int next = now ^ 1;
        scanf("%s", p);
        bool col[6];
        memset(col, 0, sizeof(col));
        for (int j = 0; j < 6; ++j) {
            col[num(p[j])] = true;
        }
        for (int a = 0; a <= i; ++a) {
            for (int b = 0; a + b <= i; ++b) {
                for (int c = 0; a + b + c <= i; ++c) {
                    for (int d = 0; a + b + c + d <= i; ++d) {
                        for (int e = 0; a + b + c + d + e <= i; ++e) {
                            if (f[now][a][b][c][d][e]) {
                                f[next][a + 1][b][c][d][e] |= col[0];
                                f[next][a][b + 1][c][d][e] |= col[1];
                                f[next][a][b][c + 1][d][e] |= col[2];
                                f[next][a][b][c][d + 1][e] |= col[3];
                                f[next][a][b][c][d][e + 1] |= col[4];
                                f[next][a][b][c][d][e] |= col[5];
                            }
                        }
                    }
                }
            }
        }
        memset(f[now], 0, sizeof(f[now]));
        now = next;
    }
    int ans = 0;
    for (int a = 0; a <= n * n; ++a) {
        for (int b = 0; a + b <= n * n; ++b) {
            for (int c = 0; a + b + c <= n * n; ++c) {
                for (int d = 0; a + b + c + d <= n * n; ++d) {
                    for (int e = 0; a + b + c + d + e <= n * n; ++e) {
                        if (f[now][a][b][c][d][e]) {
                            int g = n * n - (a + b + c + d + e);
                            //cout << a << ' ' << b << ' ' << c << ' ' << d << ' ' << e << ' ' << g << endl;
                            int inc = (long long)fac[n * n] * rev[a] % MOD * rev[b] % MOD * rev[c] % MOD * rev[d] % MOD * rev[e] % MOD * rev[g] % MOD;
                            (ans += inc) %= MOD;
                        }
                    }
                }
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}
