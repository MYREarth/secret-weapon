#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

double dist(double x, double y) {
    return sqrt(x * x + y * y);
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int a, b, x1, y1, x2, y2;
        char f1[2], f2[2];
        scanf("%d%d", &a, &b);
        scanf("%d%d%s", &x1, &y1, f1);
        scanf("%d%d%s", &x2, &y2, f2);
        double ans = 0;
        if (f1[0] == f2[0]) {
            ans = dist(x1 - x2, y1 - y2);
            ans = min(ans, min(dist(a + x2 - x1, b + y2 - y1), dist(a + x2 - x1, y2 - b - y1)));
            ans = min(ans, min(dist(x2 - a - x1, b + y2 - y1), dist(x2 - a - x1, y2 - b - y1)));
        } else {
            ans = min(dist(a - x1 + x2, y1 - (b - y2)), dist(a + x1 - x2, y1 - (b - y2)));
            ans = min(ans, min(dist(x1 - x2, b - y1 + b - y2), dist(x1 - x2, y1 + y2)));
        }
        printf("%.12f\n", ans);
    }
    return 0;
}
