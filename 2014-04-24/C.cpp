#include<cmath>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

struct Triangle {
    long long a[3];

    Triangle(long long b, long long c, long long d) {
        a[0] = b, a[1] = c, a[2] = d;
        sort(a, a + 3);
        long long g = std::abs(__gcd(__gcd(a[0], a[1]), a[2]));
        if (g) {
           a[0] /= g, a[1] /= g, a[2] /= g;
        }
    }

    bool check() {
        return a[0] > 0 && a[0] + a[1] > a[2];
    }
};

int ang_type(long long a, long long b) {
    if (a >= b || a <= -b) {
        return 2;
    }
    if (a == 0) {
        return 0;
    }
    if (a > 0) {
        return -1;
    }
    return 1;
}

long long sqrt2(long long a) {
    long long  b = sqrt(a);
    for (long long i = max(0ll, b - 10); i <= b + 10; ++i) {
        if (i * i == a) {
            return i;
        }
    }
    return -1;
}

int main() {
    long long p, q, u, v;
    cin >> p >> q >> u >> v;
    if (ang_type(p, q) > ang_type(u, v)) {
        swap(p, u);
        swap(q, v);
    }
    if (ang_type(u, v) == 2) {
        printf("-1\n");
        return 0;
    }
    Triangle tmp(0, 0, 0);
    if (ang_type(u, v) == 1) {
        if (ang_type(p, q) >= 0) {
            printf("-1\n");
            return 0;
        }
        long long a = v * v - u * u, b = q * q - p * p, g = __gcd(a, b);
        a /= g, b /= g;
        if (sqrt2(a) == -1 || sqrt2(b) == -1) {
            printf("-1\n");
            return 0;
        }
        long long k1 = sqrt2(a), k2 = sqrt2(b);
        tmp = Triangle(q * k1, v * k2, p * k1 + u * k2);
    } else if (ang_type(u, v) == 0) {
        if (ang_type(p, q) == 0) {
            printf("-1\n");
            return 0;
        }
        long long k = sqrt2(q * q - p * p);
        if (k == -1) {
            printf("-1\n");
            return 0;
        }
        tmp = Triangle(q, p, k);
    } else {
        long long a = v * v - u * u, b = q * q - p * p, g = __gcd(a, b);
        a /= g, b /= g;
        if (sqrt2(a) == -1 || sqrt2(b) == -1) {
            printf("-1\n");
            return 0;
        }
        long long k1 = sqrt2(a), k2 = sqrt2(b);
        tmp = Triangle(q * k1, v * k2, p * k1 + u * k2);
    }
    if (tmp.check()) {
        cout << tmp.a[0] << ' ' << tmp.a[1] << ' ' << tmp.a[2] << endl;
    } else {
        printf("-1\n");
    }
    return 0;
}
