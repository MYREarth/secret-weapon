#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 505;
int n, m;
char map[N][N];

int cnt[N][2];

const long long M1 = 250000, M2 = M1 * 2 + 1;
long long h[N];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i) {
        scanf("%s", map[i]);
    }
    long long ans = 0;
    for (int up = 0; up < n; ++up) {
        memset(cnt, 0, sizeof(cnt));
        for (int i = up; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (map[i][j] == 'R') {
                    --cnt[j][0], --cnt[j][1];
                } else if (map[i][j] == 'G') {
                    ++cnt[j][0];
                } else {
                    ++cnt[j][1];
                }
            }
            int c[2];
            c[0] = c[1] = 0;
            for (int j = 0; j < m; ++j) {
                c[0] += cnt[j][0], c[1] += cnt[j][1];
                h[j] = (c[0] + M1) * M2 + c[1] + M1;
            }
            h[m] = M1 * M2 + M1;
            sort(h, h + m + 1);
            for (int j = 0; j < m + 1; ++j) {
                int k = j;
                while (k < m + 1 && h[k] == h[j]) {
                    ++k;
                }
                ans += (long long)(k - j) * (k - j - 1) / 2;
                j = k - 1;
            }
        }
    }
    printf("%lld\n", ans);
    return 0;
}
