#include<cmath>
#include<vector>
#include<cstdio>
#include<complex>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 100005 << 2;

int n, cnt[N];

long long ans;

typedef complex<double> Complex;

Complex sincos(double ang) {
    return Complex(cos(ang), sin(ang));
}

const double pi = acos(-1);

void FFT(Complex P[], int n, int oper) {
    for (int i = 1, j = 0; i < n - 1; ++i) {
        for (int s = n; j ^= s >>= 1, ~j & s;);
        if (i < j) {
            swap(P[i], P[j]);
        }
    }
    Complex unit_p0;
    for (int d = 0; (1 << d) < n; ++d) {
        int m = 1 << d, m2 = m * 2;
        double p0 = pi / m * oper;
        unit_p0 = sincos(p0);
        for (int i = 0; i < n; i += m2) {
            Complex unit = 1;
            for (int j = 0; j < m; ++j) {
                Complex &P1 = P[i + j + m], &P2 = P[i + j];
                Complex t = unit * P1;
                P1 = P2 - t;
                P2 = P2 + t;
                unit = unit * unit_p0;
            }
        }
    }
}

Complex a[N], b[N];
long long s[N], t[N];

void solve() {
    int m = 1;
    while (m < n * 2) {
        m <<= 1;
    }
    for (int i = 0; i < m; ++i) {
        a[i] = cnt[i];
    }
    FFT(a, m, 1);
    for (int i = 0; i < m; ++i) {
        b[i] = a[i] * a[i];
    }
    FFT(b, m, -1);
    for (int i = 0; i < m; ++i) {
        s[i] = (long long)(b[i].real() / m + 0.5);
    }
    for (int i = 0; i < n; ++i) {
        s[i * 2] -= cnt[i] * cnt[i];
    }
    for (int i = 0; i < m; ++i) {
        s[i] /= 2;
    }
    for (int i = 0; i < n; ++i) {
        t[i] = 0;
    }
    for (int i = 0; i < m; ++i) {
        int first = i, second = i + n;
        if (first % 2 == 0) {
            first /= 2;
            first %= n;
            t[first] += s[i];
        }
        if (second % 2 == 0) {
            second /= 2;
            second %= n;
            t[second] += s[i];
        }
    }
    for (int i = 0; i < n; ++i) {
        ans += t[i] * cnt[i];
    }
}

char st[N];

int main() {
    freopen("triangle.in", "r", stdin);
    freopen("triangle.out", "w", stdout);
    scanf("%d%s", &n, st);
    if (n < 3) {
        printf("0\n");
        return 0;
    }
    for (int i = 0; i < n; ++i) {
        cnt[i] = st[i] == 'W';
    }
    solve();
    for (int i = 0; i < n; ++i) {
        cnt[i] = st[i] == 'B';
    }
    solve();
    if (n % 3 == 0) {
        int l = n / 3;
        for (int i = 0; i < l; ++i) {
            int j = i + l, k = j + l;
            if (st[i] == st[j] && st[j] == st[k]) {
                ans -= 2;
            }
        }
    }
    printf("%lld\n", ans);
    return 0;
}
