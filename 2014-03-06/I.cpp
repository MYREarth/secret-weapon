#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 3005;

int l1, l2;
char s1[N], s2[N];

short cal[N][N], la[N][N], lb[N][N];

int main() {
    freopen("subpair.in", "r", stdin);
    freopen("subpair.out", "w", stdout);
    scanf("%s%s", s1, s2);
    l1 = strlen(s1), l2 = strlen(s2);
    for (int i = 0; i < l1; ++i) {
        for (int j = 0; j < l2; ++j) {
            cal[i + 1][j + 1] = s1[i] == s2[j] ? 1 + cal[i][j] : 0;
        }
    }
    for (int i = 0; i < l1; ++i) {
        for (int j = 0; j < l2; ++j) {
            la[i + 1][j + 1] = max(max(max(la[i + 1][j], la[i][j + 1]), cal[i + 1][j + 1]), la[i][j]);
        }
    }
    memset(cal, 0, sizeof(cal));
    for (int i = l1 - 1; i >= 0; --i) {
        for (int j = l2 - 1; j >= 0; --j) {
            cal[i][j] = s1[i] == s2[j] ? 1 + cal[i + 1][j + 1] : 0;
        }
    }
    for (int i = l1 - 1; i >= 0; --i) {
        for (int j = l2 - 1; j >= 0; --j) {
            lb[i][j] = max(max(lb[i + 1][j + 1], max(lb[i + 1][j], lb[i][j + 1])), cal[i][j]);
        }
    }
    int ans = -1, ansx = -1, ansy = -1;
    for (int i = 0; i <= l1; ++i) {
        for (int j = 0; j <= l2; ++j) {
            if (la[i][j] + lb[i][j] > ans) {
                ans = la[i][j] + lb[i][j];
                ansx = i, ansy = j;
            }
        }
    }
    int p1 = -1;
    for (int i = l1 - 1; i >= ansx; --i) {
        for (int j = l2 - 1; j >= ansy; --j) {
            if (cal[i][j] == lb[ansx][ansy]) {
                p1 = i;
            }
        }
    }
    memset(cal, 0, sizeof(cal));
    for (int i = 0; i < l1; ++i) {
        for (int j = 0; j < l2; ++j) {
            cal[i + 1][j + 1] = s1[i] == s2[j] ? 1 + cal[i][j] : 0;
        }
    }
    int p2 = -1;
    for (int i = 0; i < ansx; ++i) {
        for (int j = 0; j < ansy; ++j) {
            if (cal[i + 1][j + 1] == la[ansx][ansy]) {
                p2 = i;
            }
        }
    }
    for (int i = 0; i < la[ansx][ansy]; ++i) {
        printf("%c", s1[p2 - la[ansx][ansy] + 1 + i]);
    }
    printf("\n");
    for (int j = 0; j < lb[ansx][ansy]; ++j) {
        printf("%c", s1[p1 + j]);
    }
    printf("\n");
    return 0;
}
