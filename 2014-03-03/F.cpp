#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 1005;

int x[N], y[N], ord[N][N], next[N][N];
bool vis[N][N];

int sign(int i) {
    return y[i] > 0 || y[i] == 0 && x[i] < 0;
}

bool by_ang(int i, int j) {
    int s1 = sign(i), s2 = sign(j);
    if (s1 != s2) {
        return s1 < s2;
    } else {
        return (long long)x[i] * y[j] - (long long)y[i] * x[j] < 0;
    }
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; ++i) {
            scanf("%d%d", x + i, y + i);
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                vis[i][j] = false;
            }
        }
        for (int i = 0; i < n; ++i) {
            int cx = x[i], cy = y[i];
            for (int j = 0; j < n; ++j) {
                x[j] -= cx, y[j] -= cy;
            }    
            int top = 0;
            for (int j = 0; j < n; ++j) {
                if (j != i) {
                    ord[i][top++] = j;
                }
            }
            sort(ord[i], ord[i] + n - 1, by_ang);
            ord[i][n - 1] = ord[i][0];
            for (int j = 0; j < n - 1; ++j) {
                x[n] = -x[ord[i][j]], y[n] = -y[ord[i][j]];
                int nxt1 = ord[i][j + 1], nxt2 = lower_bound(ord[i], ord[i] + n - 1, n, by_ang) - ord[i];
                if (nxt2 == n - 1) {
                    nxt2 = 0;
                }
                nxt2 = ord[i][nxt2];
                int best = nxt2 == ord[i][j] || (long long)-x[nxt1] * y[nxt2] + (long long)x[nxt2] * y[nxt1] < 0 ? nxt1 : nxt2; 
                next[i][ord[i][j]] = best;
            }
        }
        long long a = 0, b = n * (n - 1);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == j || vis[i][j]) {
                    continue;
                }
                int sx = i, sy = j, cnt = 0;
                while (!vis[sx][sy]) {
                    vis[sx][sy] = true;
                    ++cnt;
                    int sz = next[sy][sx];
                    sx = sy, sy = sz; 
                }
                a += (long long)cnt * cnt;
            }
        }
        long long g = __gcd(a, b);
        a /= g, b /= g;
        if (b == 1) {
            cout << a << endl;
        } else {
            cout << a << '/' << b << endl;
        }
    }
    return 0;
}
