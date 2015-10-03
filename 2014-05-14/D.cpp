#include<cmath>
#include<vector>
#include<cstdio>
#include<complex>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 100005, MOD = 1000000007;

int n;

bool vis[N];

int p[N], w[N];

char s[N];

vector<int> use, loop[N];

typedef complex<long double> Complex;

const int L = 20;

Complex a[1 << L], b[1 << L], c[1 << L];

const long double pi = acos((long double)-1);

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
        long double p0 = pi / m * oper;
        unit_p0 = Complex(cos(p0), sin(p0));
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

vector<int> solve (vector<int> w, vector<int> s) {
    int n = 1, m = w.size();
    while (n < m * 4) {
        n <<= 1;
    }
    for (int i = 0; i < n; ++i) {
        a[i] = Complex(0, 0);
        b[i] = Complex(0, 0);
    }
    for (int i = 0; i < m; ++i) {
        a[i] = Complex(w[i], 0);
        a[i + m] = Complex(w[i], 0);
        b[i] = Complex(s[m - i - 1], 0);
    }
    FFT(a, n, 1);
    FFT(b, n, 1);
    for (int i = 0; i < n; ++i) {
        c[i] = a[i] * b[i];
    }
    FFT(c, n, -1);
    vector<int> ret;
    for (int i = 0; i < m; ++i) {
        ret.push_back((long long)((c[i + m - 1].real() / n) + 0.5) % MOD);
    }
    return ret;
}

int main() {
    freopen("permutation.in", "r", stdin);
    freopen("permutation.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", p + i);
        --p[i];
    }
    for (int i = 0; i < n; ++i) {
        scanf("%d", w + i);
    }
    scanf("%s", s);
    for (int i = 0; i < n; ++i) {
        if (vis[i]) {
            continue;
        }
        vector<int> ww, ss;
        int tmp = i;
        while (!vis[tmp]) {
            vis[tmp] = true;
            ww.push_back(w[tmp]);
            ss.push_back(s[tmp] - '0');
            tmp = p[tmp];
        }
        vector<int> cal = solve(ww, ss);
        int k = cal.size();
        if (loop[k].size() == 0) {
            use.push_back(k);
            loop[k] = *(new vector<int>(k));
        }
        for (int j = 0; j < (int)cal.size(); ++j) {
            (loop[k][j] += cal[j]) %= MOD;
        }
    }
    int m;
    scanf("%d", &m);
    for (int i = 0; i < m; ++i) {
        int sum = 0;
        for (int j = 0; j < (int)use.size(); ++j) {
            int u = use[j];
            (sum += loop[u][i % u]) %= MOD;
        }
        printf("%d\n", sum);
    }
    return 0;
}
