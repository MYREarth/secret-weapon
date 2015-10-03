#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 1005, M = 50005;

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
    //freopen("abpoems.in", "r", stdin);
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%s%s%s", pa, pb, w);
        int la = strlen(pa), lb = strlen(pb), caa = count(pa, la), cba = count(pb, lb), lw = strlen(w), cw = count(w, lw);
        //la = 1, lb = 1000, caa = 1, cba = 500;
        //la = 999, lb = 1000, caa = 999, cba = 1;
        la = 999, lb = 1000, caa = 0, cba = 1000;
        p[0] = (long double)cw / lw;
        for (int i = 1; i < M; ++i) {
            p[i] = ((caa - cba) * p[i - 1] + cba) / ((la - lb) * p[i - 1] + lb);
        }
//bool flag = false;
        for (int i = 0; i < M; ++i) {
            r[i] = (la - lb) * p[i] + lb;
/*
if (i && fabs(r[i] - r[i - 1]) < 1e-9 && !flag) {
    flag = true;
    cout << i << endl;
}
*/
        }
/*
for (int i = 0; i < 10; ++i) {
    printf("%.12f %.12f\n", (double)r[M - 1 - i], (double)p[M - 1 - i]);
}
*/
        if (fabs(r[M - 2] - r[M - 1]) < 0.1) {
            long double ans = r[M - 1];
            if (la == lb) {
                ans = la;
                printf("%.12f\n", (double)ans);
            } else {
                int a = la - lb, b = lb - caa + cba, c = -cba,
                    d = b * b - 4 * a * c;
                long double p;
                if (d < 0) {
                    p = -1;
                } else if (d == 0) {
                    p = -(long double)b / (2 * a);
                } else if (d > 0) {
                    long double p1 = (-b + sqrt((long double)d)) / (2 * a), p2 = (-b - sqrt((long double)d)) / (2 * a);
                    if (p1 < -1e-9 || p1 > 1 + 1e-9) {
                        p = p2;
                    } else {
                        p = p1;
                    }
                }
                if (p < -1e-9 || p > 1 + 1e-9) {
                    printf("%.12f\n", (double)ans);
                } else {
                    long double pans = (la - lb) * p + lb;
                    if (fabs(pans - ans) < 0.1) {
                        ans = pans;
                    }
                    printf("%.12f\n", (double)ans);
                }
            }
        } else {
            printf("-\n");
        }
    }
    return 0;
}
