#include<cmath>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 100005;

int n, r;
int x[N], y[N];

bool by_x(int i, int j) {
    return x[i] < x[j];
}

bool by_y(int i, int j) {
    return y[i] < y[j];
}

long double calc(long double a,long double b,long double x,long double r)
{
    return((a+sqrt(r*r-x*x))*(b+x));
}

long double cal(long double a, long double b, long double rr) {
    long double l=0,r=rr;
    for (int T=1;T<=100;T++)
    {
        long double lx=(2*l+r)/3,rx=(l+2*r)/3;
        if (calc(a,b,lx,rr)<calc(a,b,rx,rr))
            l=lx;
        else
            r=rx;
    }
    return(calc(a,b,(l+r)/2,rr));
}

#define y0 Y0
#define y1 Y1

int ord[N], x0[4], x1[4], y0[4], y1[4];

int main() {
    freopen("approximate.in", "r", stdin);
    freopen("approximate.out", "w", stdout);
    while (scanf("%d", &n) == 1 && n) {
        scanf("%d", &r);
        for (int i = 0; i < n; ++i) {
            scanf("%d%d", x + i, y + i);
            ord[i] = i;
        }
        int m = min(n, 4);
        sort(ord, ord + n, by_x);
        for (int i = 0; i < m; ++i) {
            x0[i] = ord[i];
            x1[i] = ord[n - 1 - i];
        }
        sort(ord, ord + n, by_y);
        for (int i = 0; i < m; ++i) {
            y0[i] = ord[i];
            y1[i] = ord[n - 1 - i];
        }
        long double ans = 0;
        int c[4];
        for (c[0] = 0; c[0] < m; ++c[0]) {
            for (c[1] = 0; c[1] < m; ++c[1]) {
                for (c[2] = 0; c[2] < m; ++c[2]) {
                    for (c[3] = 0; c[3] < m; ++c[3]) {
                        if (x[x0[c[0]]] > x[x1[c[1]]] || y[y0[c[2]]] > y[y1[c[3]]]) {
                            continue;
                        }
                        int d[4], f[4];
                        d[0] = x0[c[0]], d[1] = x1[c[1]], d[2] = y0[c[2]], d[3] = y1[c[3]];
                        for (int i = 0; i < 4; ++i) {
                            f[i] = 1;
                            for (int j = 0; j < 4; ++j) {
                                if (i != j && d[i] == d[j]) {
                                    --f[i];
                                }
                            }
                        }
                        bool flag = false;
                        for (int i = 0; i < 4; ++i) {
                            if (f[i] < 0) {
                                flag = true;
                            }
                        }
                        if (flag || d[0] == d[1] || d[2] == d[3]) {
                            continue;
                        }
                        int minx, maxx, miny, maxy;
                        minx = (x[x0[c[0]]] - (f[0] * r));
                        maxx = (x[x1[c[1]]] + (f[1] * r));
                        miny = (y[y0[c[2]]] - (f[2] * r));
                        maxy = (y[y1[c[3]]] + (f[3] * r));
                        int same = 0;
                        for (int i = 0; i < 4; ++i) {
                            if (f[i] == 0) {
                                ++same;
                            }
                        }
                        same /= 2;
                        long double a = (long double)maxx - minx, b = (long double)maxy - miny;
                        ans = max(ans, cal(max(a, b), min(a, b), same * r));
                    }
                }
            }
        }
        printf("%.12f\n", (double)ans);
    }
    return 0;
}
