#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int n;

double fpow(long double p, int n) {
    long double ret = 1, mul = p;
    while (n) {
        if (n & 1) {
            ret *= mul;
        }
        mul *= mul;
        n >>= 1;
    }
    return ret;
}

int sign(long double x, double eps = 1e-9) {
    return x < -eps ? -1 : x > eps;
}

void cal(long double &pl, long double &pr, int t, char op, long double p) {
    long double swap, unswap;
    unswap = (1 + fpow(1 - p - p, t)) / 2;
    swap = 1 - unswap;
    if (op == 'L') {
        pl = unswap, pr = swap;
    } else {
        pl = swap, pr = unswap;
    }
}

int main() {
    scanf("%d", &n);
    long double l = 1, r = 0, exp = 0;
    for (int i = 0; i < n; ++i) {
        int t;
        char op[2];
        double p;
        scanf("%d%s%lf", &t, op, &p);
        long double pl, pr;
        cal(pl, pr, t, op[0], p);
        exp += l * pl + r * pr;
        l = pr, r = pl;
    }
    printf("%.12f\n", (double)exp);
    return 0;
}
