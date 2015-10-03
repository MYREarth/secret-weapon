#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

long long rt(long long n, long long l = 1, long long r = 1000000000) {
    while (l < r) {
        long long m = l + r + 1 >> 1;
        if (m * m > n) {
            r = m - 1;
        } else {
            l = m;
        }
    }
    return l;
}

int main() {
    long long a, b, p;
    scanf("%lld", &p);
    if (p % 4 == 1) {
        puts("YES");
    } else {
        puts("NO");
        return 0;
    }
    a = 1, b = rt(p);
    long long s;
    while (true) {
        s = a * a + b * b;
        if (s == p) {
            break;
        } else if (s < p) {
            a = rt(p - b * b, a + 1, b - 1);
        } else {
            b = rt(p - a * a, a + 1, b - 1);
        }
    }
    printf("%lld %lld\n", a, b);
    return 0;
}

