#include<cmath>
#include<vector>
#include<cstdio>
#include<cstring>
#include<complex>
#include<iostream>
#include<algorithm>
using namespace std;

void readin(int l, int s[], int a[]) {
    char buf[10];
    for (int i = 0; i < l; ++i) {
        scanf("%s", buf);
        a[i] = buf[7] - '0';
        for (int j = 0; j < 7; ++j) {
            s[i] = s[i] << 1 | buf[j] - '0';
        }
    }
}

const int N = 250005;
int n, m, s[N], t[N], a[N], b[N];

#define next NEXT
int next[N];

int match[N];

bool mention[N];

typedef complex<double> Complex;

void sincos(double ang, double &y, double &x) {
    y = sin(ang), x = cos(ang);
}

const double pi = acos(-1);

void FFT(Complex P[], int n, int oper) {
    for (int i = 1, j = 0; i < n - 1; i++) {
        for (int s = n; j ^= s >>= 1, ~j & s;);
        if (i < j) {
            swap(P[i], P[j]);
        }
    }
    Complex unit_p0;
    for (int d = 0; (1 << d) < n; d++) {
        int m = 1 << d, m2 = m * 2;
        double p0 = pi / m * oper;
        sincos(p0, unit_p0.imag(), unit_p0.real());
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

const int LOG = 19;
Complex aa[1 << LOG], bb[1 << LOG], cc[1 << LOG];
int c[1 << LOG], suma[1 << LOG];

int main() {
    scanf("%d%d", &n, &m);
    readin(n, s, a);
    readin(m, t, b);
    t[m] = -1;
    next[0] = -1;
    for (int i = 1; i <= m; ++i) {
        next[i] = next[i - 1];
        while (next[i] != -1 && t[next[i]] != t[i - 1]) {
            next[i] = next[next[i]];
        }
        ++next[i];
    }
    int p = 0;
    for (int i = 0; i < n; ++i) {
        while (p != -1 && s[i] != t[p]) {
            p = next[p];
        }
        match[i] = ++p;
        //cout << i << ' ' << match[i] << endl;
    }
    bool flag = false;
    for (int i = 0; i < n; ++i) {
        if (match[i] == m) {
            mention[i - m + 1] = true;
            flag = true;
        }
    }
    if (!flag) {
        printf("No\n");
        return 0;
    } else {
        printf("Yes\n");
    }
    int bar = 1;
    while (bar < n + m) {
        bar <<= 1;
    }
    for (int i = 0; i < n; ++i) {
        aa[i] = a[i];
    }
    for (int i = m - 1; i >= 0; --i) {
        bb[m - 1 - i] = b[i];
    }
    FFT(aa, bar, 1);
    FFT(bb, bar, 1);
    for (int i = 0; i < bar; ++i) {
        cc[i] = aa[i] * bb[i];
    }
    int sumb = 0;
    for (int i = 0; i < m; ++i) {
        sumb += b[i];
    }
    for (int i = 1; i <= n; ++i) {
        suma[i] = suma[i - 1] + a[i - 1];
    }
    FFT(cc, bar, -1);
    for (int i = m - 1; i < bar; ++i) {
        c[i] = -2 * (int)(cc[i].real() / bar + 0.5) + suma[min(i + 1, n)] - suma[min(n, i + 1 - m)] + sumb;
        //cout << i << ' ' << c[i] << endl;
    }
    int anst = -1;
    for (int i = 0; i < n; ++i) {
        if (mention[i] && (anst == -1 || c[i + m - 1] < c[anst + m - 1])) {
            anst = i;
        }
    }
    printf("%d %d\n", c[anst + m - 1], anst + 1);
    return 0;
}
