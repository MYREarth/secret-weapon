#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 300005;

int n;
long double r, ri[N], sum = 0;

int main() {
    long double ans = 0;
    cin >> n >> r;
    for (int i = 0; i < n; ++i) {
        cin >> ri[i];
        ri[i] /= r;
        ans += 2 * ri[i] * sum;
        sum += ri[i];
    }
    printf("%.12f\n", (double)ans);
    return 0;
}
