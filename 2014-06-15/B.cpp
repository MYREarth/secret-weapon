#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 10005;

const double eps = 1e-9;

double x, p, ans;

double f[N], rf[N];

inline double cal(const double &p, const int &a, const int &b) {
    double ret = p * a - (1 - p) * b * (1 - x);
    //cout << a << ' ' << b << ' ' << ret << endl;
    return ret;
}

int main() {
    scanf("%lf%lf", &x, &p);
    x /= 100, p /= 100;
    if (x < eps || p < eps) {
        ans = 0;
    } else {
        f[1] = p, rf[1] = 1 - p;
        for (int i = 2; i < N; ++i) {
            f[i] = p * f[i - 1] / (1 - (1 - rf[i - 1]) * (1 - p));
            rf[i] = (1 - p) * rf[i - 1] / (1 - (1 - f[i - 1]) * p);
        }
        int a = 1, b = 1;
        double curp = f[1], curv = cal(curp, a, b), best = 0;
        while (a + b + 1 < N) {
            while (a + b + 1 < N) {
                double np = curp * p / (1 - (1 - p) * (1 - rf[a + b - 1])),
                       nv = cal(np, a + 1, b);
                if (nv > curv) {
                    curv = nv;
                    curp = np;
                    ++a;
                } else {
                    break;
                }
            }
            if (curv > best) {
                best = curv;
                curp = 1 - ((1 - curp) * (1 - p) / (1 - p * (1 - f[a + b])));
                curv = cal(curp, a, ++b);
            } else {
                break;
            }
        }
        ans = best;
    }
    printf("%.12f\n", ans);
    return 0;
}
