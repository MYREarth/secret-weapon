#include<map>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int BAR1 = 1000005;
bool vis[BAR1];
long double ans[BAR1];

const long double eps = 1e-25;

map<int, long double> mem;

long double getans(int n) {
    if (n < BAR1) {
        if (vis[n]) {
            return ans[n];
        }
        vis[n] = true;
    } else if (mem.count(n)) {
        return mem[n];
    }
    long double ret = getans(n >> 1) + getans((n + 1) >> 1) + n;
    int a = n / 2, b = n - a;
    long double p1 = 1, p2 = 1;
    for (int i = 0; i < a && p1 >= eps; ++i) {
        p1 = p1 * (a - i) / (n - i);
        ret -= p1;
    }
    for (int i = 0; i < b && p2 >= eps; ++i) {
        p2 = p2 * (b - i) / (n - i);
        ret -= p2;
    }
    if (n < BAR1) {
        ans[n] = ret;
    } else {
        mem[n] = ret;
    }
    return ret;
}

int main() {
    freopen("mergesort.in", "r", stdin);
    freopen("mergesort.out", "w", stdout);
    int t;
    scanf("%d", &t);
    while (t--) {
        int n;
        scanf("%d", &n);
        printf("%.12f\n", (double)getans(n));
    }
    return 0;
}
