#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

vector<double> a, f;

int n;

const double pi = acos(-1);

double g(double xlow, double xhigh) {
    double x0 = xlow, x1 = xhigh, ret = 0;
    for (int i = 0; i < (int)f.size(); ++i) {
        ret += f[i] * (x1 - x0);
        x0 *= xlow, x1 *= xhigh;
    }
    return ret * pi;
}


int main() {
    while (scanf("%d", &n) == 1) {
        a.clear();
        for (int i = 0; i <= n; ++i) {
            double p;
            scanf("%lf", &p);
            a.push_back(p);
        }
        f.clear();
        f.resize(2 * n + 1);
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= n; ++j) {
                f[i + j] += a[i] * a[j];
            }
        }
        for (int i = 0; i <= 2 * n; ++i) {
            f[i] /= (i + 1);
        }
        double xlow, xhigh, inc;
        scanf("%lf%lf%lf", &xlow, &xhigh, &inc);
        double vol = g(xlow, xhigh);
        static int id = 0;
        printf("Case %d: %.2f\n", ++id, vol);
        if (vol < inc) {
            //printf("insufficient volume\n");
        } else {
            int num = min((int)(vol / inc), 8);
            for (int i = 0; i < num; ++i) {
                double l = xlow, r = xhigh;
                while (r - l > 1e-6) {
                    double m = (l + r) / 2;
                    if (g(xlow, m) > inc * (i + 1)) {
                        r = m;
                    } else {
                        l = m;
                    }
                }
                printf("%.2f%c", l - xlow, i == num - 1 ? '\n' : ' ');
            }
        }
    }
    return 0;
}
