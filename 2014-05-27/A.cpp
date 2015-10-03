#include<cmath>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 1005, M = 20005;

char pa[N], pb[N], w[N];

int count(char *s, int l) {
    int ret = 0;
    for (int i = 0; i < l; ++i) {
        ret += s[i] == 'a';
    }
    return ret;
}

long double p[M], r[M];

int main() {
    freopen("abpoems.in", "r", stdin);
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%s%s%s", pa, pb, w);
        int la = strlen(pa), lb = strlen(pb), caa = count(pa, la), cba = count(pb, lb), lw = strlen(w), cw = count(w, lw);
        //la = 2, lb = 1000, caa = 1, cba = 999;
        p[0] = (long double)cw / lw;
        for (int i = 1; i < M; ++i) {
            p[i] = ((caa - cba) * p[i - 1] + cba) / ((la - lb) * p[i - 1] + lb);
        }
        for (int i = 0; i < M; ++i) {
            r[i] = (la - lb) * p[i] + lb;
        }
/*
for (int i = 0; i < 10; ++i) {
    printf("%.12f %.12f\n", (double)r[M - 1 - i], (double)p[M - 1 - i]);
}
*/
        if (la == lb) {
            printf("%.12f\n" (double)la);
        } else {
            int a = la - lb, b = lb - caa + cba, c = -cba,
                d = (b * b - 4 * a * c);
            if (d < 0) {
            } else if (d == 0) {
            } else {
            }
        }
    }
    return 0;
}
