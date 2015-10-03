#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 5005, D = 11;

int n, d;

int y[N];
double x[N][D], ans[D];

int main() {
    scanf("%d%d", &n, &d);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < d; ++j) {
            scanf("%lf", &x[i][j]);
        }
        scanf("%d", y + i);
    }
    while (true) {
        bool flag = true;
        for (int i = 0; i < n; ++i) {
            double sum = 0;
            for (int j = 0; j < d; ++j) {
                sum += x[i][j] * ans[j];
            }
            if (sum * y[i] <= 0.002) {
                flag = false;
                for (int j = 0; j < d; ++j) {
                    ans[j] += y[i] * x[i][j];
                }
            }
        }
        if (flag) {
            break;
        }
    }
    for (int i = 0; i < d; ++i) {
        printf("%.12f%c", ans[i], i == d - 1 ? '\n' : ' ');
    }
    return 0;
}
