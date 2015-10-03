#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 3000;
int n, m, a[N][N], b[N][N], y[N];

int main() {
    freopen("cross.in", "r", stdin);
    freopen("cross.out", "w", stdout);
    scanf("%d%d", &n, &m);
    if (n == 1 || m == 1) {
        int t = n + m - 1;
        bool has1 = false, has2 = false;
        for (int i = 0; i < t; ++i) {
            int a;
            scanf("%d", &a);
            if (a == 1) {
                has1 = true;
            } else {
                has2 = true;
            }
        }
        if (has1 && !has2) {
            printf("0\n");
        } else if (!has1 && has2) {
            printf("1\n");
        } else {
            printf("-1\n");
        }
        return 0;
    }
    bool flip = n % 2 != 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int tmp;
            scanf("%d", &tmp);
            --tmp;
            if (flip) {
                a[j][i] = tmp;
            } else {
                a[i][j] = tmp;
            }
        }
    }
    if (flip) {
        swap(n, m);
    }
    for (int i = 1; i < n; ++i) {
        for (int j = 1; j < m; ++j) {
            b[i][j] = a[i - 1][j - 1] ^ a[i - 1][j] ^ a[i][j - 1] ^ a[i][j];
        }
    }
    for (int i = 1; i < n; ++i) {
        if (i > 1) {
            for (int j = 1; j < m; ++j) {
                b[i][j] ^= b[i - 1][j];
                if (j > 1) {
                    b[i][j] ^= b[i - 1][j - 1];
                }
            }
        }
        for (int j = 2; j < m; ++j) {
            b[i][j] ^= b[i][j - 1];
        }
    }
    b[0][0] = a[0][0];
    for (int j = 1; j < m; ++j) {
        b[0][j] = a[0][j];
        for (int i = 1; i < n; ++i) {
            b[0][j] ^= b[i][j];
        }
    }
    for (int i = 1; i < n; ++i) {
        b[i][0] = a[i][0];
        for (int j = 1; j < m; ++j) {
            b[i][0] ^= b[i][j];
        }
    }
/*
for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
        printf("%d", a[i][j]);
    }
    printf("\n");
}
printf("\n");
for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
        printf("%d", b[i][j]);
    }
    printf("\n");
}
printf("\n");
*/
    int all = b[0][0], ans = -1;
    for (int z = 0; z < 2; ++z) {
        int tmp = z, sumy = 0;
        for (int j = 1; j < m; ++j) {
            y[j] = all ^ b[0][j] ^ z;
            tmp += y[j];
            sumy ^= y[j];
        }
        bool flag = true;
        if (m % 2 == 0) {
            int sumx = 0;
            for (int i = 1; i < n; ++i) {
                int x = all ^ b[i][0] ^ z;
                sumx ^= x;
                tmp += x;
                for (int j = 1; j < m; ++j) {
                    tmp += b[i][j] ^ z ^ x ^ y[j];
                }
            }
            if ((sumx ^ sumy ^ z) != all) {
                flag = false;
            }
        } else {
            int cal[2];
            memset(cal, 0, sizeof(0));
            cal[0] = tmp; cal[1] = 1ll << 30;
            for (int i = 1; i < n; ++i) {
                if (b[i][0] != all) {
                    flag = false;
                    break;
                }
                int cnt[2];
                memset(cnt, 0, sizeof(cnt));
                for (int x = 0; x < 2; ++x) {
                    cnt[x] += x;
                    for (int j = 1; j < m; ++j) {
                        cnt[x] += b[i][j] ^ z ^ x ^ y[j];
                    }
                }
                int ncal[2];
                ncal[0] = min(cal[0] + cnt[0], cal[1] + cnt[1]);
                ncal[1] = min(cal[0] + cnt[1], cal[1] + cnt[0]);
                cal[0] = ncal[0], cal[1] = ncal[1];
            }
            tmp = cal[all ^ z ^ sumy];
        }
        if (flag) {
            if ((ans == -1 || tmp < ans) && tmp <= n * m) {
                ans = tmp;
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}
