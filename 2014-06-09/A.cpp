#include<cassert>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const long long MOD = 7340033;

const long long G = 3;

long long powmod(long long x, long long n) {
    long long ret = 1, mul = x;
    while (n) {
        if (n & 1) {
            ret = ret * mul % MOD;
        }
        n >>= 1;
        mul = mul * mul % MOD;
    }
    return ret;
}

bool is_primitive_root(long long n) {
    return powmod(n, 1ll << 20) != 1 && powmod(n, 7ll << 19) != 1;
}

int m, n;

long long inverse(long long a) {
    //return a == 1 ? 1 : (MOD - MOD / a) * (MOD % a) % MOD;
    return a == 1 ? 1 : (MOD - MOD / a) * inverse(MOD % a) % MOD;
}

struct Poly {
    vector<long long> num;

    Poly() {
    }

    Poly(long long a) {
        num.push_back(a);
    }

    void in(int len) {
        for (int i = 0; i <= len; ++i) {
            int a;
            scanf("%d", &a);
            num.push_back(a);
        }
    }

    int size() const {
        return num.size();
    }

    void push_back(long long a) {
        num.push_back(a);
    }

    long long& operator[] (int i) {
        return num[i];
    }

    const long long operator[] (int i) const {
        return num[i];
    }

    Poly trunc(int len) {
        Poly ret;
        ret.num.resize(len);
        for (int i = 0; i < len && i < (int)num.size(); ++i) {
            ret[i] = num[i];
        }
        return ret;
    }
};

Poly operator * (const Poly &a, const long long &k) {
    Poly ret;
    for (int i = 0; i < (int)a.size(); ++i) {
        ret.push_back(a[i] * k % MOD);
    }
    return ret;
}

Poly operator - (const Poly &a, const Poly &b) {
    Poly ret;
    for (int i = 0; i < (int)a.size() || i < (int)b.size(); ++i) {
        long long u = i < (int)a.size() ? a[i] : 0,
                  v = i < (int)b.size() ? b[i] : 0;
        ret.push_back((u - v + MOD) % MOD);
    }
    return ret;
}

const int M = 1ll << 19;

long long fa[M], fb[M], fc[M];

void FFT(long long P[], int oper, int n) {
    for (int i = 1, j = 0; i < n - 1; i++) {
        for (int s = n; j ^= s >>= 1, ~j & s;);
        if (i < j){
            swap(P[i], P[j]);
        }
    }
    for (int d = 0; (1 << d) < n; d++) {
        int m = 1 << d, m2 = m * 2;
        int p0 = (MOD - 1) / m2 * oper;
        if (p0 < 0) {
            p0 = MOD - 1 + p0;
        }
        long long unit_p0 = powmod(G, p0);
        for (int i = 0; i < n; i += m2) {
            long long unit = 1;
            for (int j = 0; j < m; ++j) {
                long long &P1 = P[i + j + m], &P2 = P[i + j];
                long long t = unit * P1 % MOD;
                P1 = P2 + MOD - t;
                if (P1 >= MOD) {
                    P1 -= MOD;
                }
                P2 += t;
                if (P2 >= MOD) {
                    P2 -= MOD;
                }
                unit = unit * unit_p0 % MOD;
            }
        }
    }
}

long long inv_n;

Poly operator * (const Poly &a, const Poly &b) {
    int n = max(a.size(), b.size()) * 2;
    for (int i = 0; i < n; ++i) {
        fa[i] = 0, fb[i] = 0;
    }
    for (int i = 0; i < (int)a.size(); ++i) {
        fa[i] = a[i];
    }
    for (int i = 0; i < (int)b.size(); ++i) {
        fb[i] = b[i];
    }
    FFT(fa, 1, n);
    FFT(fb, 1, n);
    for (int i = 0; i < n; ++i) {
        fc[i] = (long long)fa[i] * fb[i] % MOD;
    }
    FFT(fc, -1, n);
    Poly ret;
    inv_n = inverse(n);
    for (int i = 0; i < n; ++i) {
        ret.push_back(fc[i] * inv_n % MOD);
    }
    return ret;
}

int main() {
    scanf("%d%d", &m, &n);
    Poly p;
    p.in(n);
    if (p[0] == 0) {
        printf("The ears of a dead donkey\n");
        return 0;
    }
    Poly q(inverse(p[0]));
    while (q.size() <= m) {
        q = q * 2 - (q * q * p.trunc(2 * q.size())).trunc(2 * q.size());
    }
    for (int i = 0; i < m; ++i) {
        printf("%d%c", (int)q[i], i == m - 1 ? '\n' : ' ');
    }
    //Poly a = (p.trunc(m) * q).trunc(m);
    //for (int i = 1; i < m; ++i) {
    //    assert(a[i] == 0);
    //}
    //assert(a[0] == 1);
    return 0;
}
