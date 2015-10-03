#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int gcd[105][105];

int num[105], top1, top2;
int vis[105], stamp, startstamp;

int main() {
    for (int i = 1; i <= 100; ++i) {
        for (int j = 1; j <= 100; ++j) {
            gcd[i][j] = __gcd(i, j);
        }
    }
    int n;
    while (scanf("%d", &n) == 1 && n) {
        top1 = 0;
        startstamp = stamp;
        for (int i = 0; i < n; ++i) {
            int a;
            scanf("%d", &a);
            ++stamp;
            top2 = 0;
            for (int j = 0; j < top1; ++j) {
                int b = gcd[a][num[j]];
                if (vis[b] != stamp) {
                    vis[b] = stamp;
                    num[top2++] = b;
                }
            }
            if (vis[a] != stamp) {
                vis[a] = stamp;
                num[top2++] = a;
            }
            top1 = top2;
        }
        int ans = 0;
        for (int i = 0; i <= 100; ++i) {
            if (vis[i] > startstamp) {
                ++ans;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
