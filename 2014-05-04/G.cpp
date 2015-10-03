#include<map>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int n, s;

struct Vector {
    bool num[32];

    Vector() {
        memset(num, 0, sizeof(num));
    }

    bool& operator [] (int i) {
        return num[i];
    }
};

struct Matrix {
    bool num[32][32];

    Matrix() {
        memset(num, 0, sizeof(num));
    }

    bool* operator [] (int i) {
        return num[i];
    }
};

Matrix operator * (Matrix a, Matrix b) {
    Matrix ret;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                ret[i][j] ^= a[i][k] & b[k][j];
            }
        }
    }
    return ret;
}

Vector operator * (Vector a, Matrix b) {
    Vector ret;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            ret[j] ^= a[i] & b[i][j];
        }
    }
    return ret;
}

long long toll(Vector a) {
    long long ret = 0;
    for (int i = 0; i < n; ++i) {
        ret = ret << 1 | a[i];
    }
    return ret;
}

Vector toVe(long long a) {
    Vector ret;
    for (int i = n - 1; i >= 0; --i) {
        ret[n - 1 - i] = a >> i & 1;
    }
    return ret;
}

const int K = 33;
char buf[K];

long long in() {
    int ret = 0;
    scanf("%s", buf);
    for (int i = 0; i < n; ++i) {
        ret = ret << 1 | (buf[i] == 'r');
    }
    return ret;
}

int main() {
    while (scanf("%d%d", &n, &s) == 2 && n && s) {
        Matrix X, XR;
        for (int i = 1; i < n; ++i) {
            X[i][i - 1] = 1;
        }
        for (int i = 0; i + 1 < n; ++i) {
            XR[i][i + 1] = 1;
        }
        XR[n - 1][0] = 1;
        for (int i = 0; i < s; ++i) {
            int p;
            scanf("%d", &p);
            X[p - 1][n - 1] = 1;
            if (p != 1) {
                XR[p - 2][0] = 1;
            }
        }
        Vector a = toVe(in()), b = toVe(in());
        Vector c = b;
        map<long long, long long> mem;
        for (int i = 0; i <= (1 << 16); ++i) {
            auto t = toll(c);
            if (!mem.count(t)) {
                mem[t] = i;
            }
            c = c * XR;
        }
        Matrix X16 = X;
        for (int i = 1; i <= 16; ++i) {
            X16 = X16 * X16;
        }
        long long ans = -1;
        Vector d = a;
        for (int i = 0; i < (1 << 16); ++i) {
            if (mem.count(toll(d))) {
                ans = (1ll << 16) * i + mem[toll(d)];
                break;
            }
            d = d * X16;
        }
        if (ans == -1) {
            printf("*\n");
        } else {
            printf("%lld\n", ans);
        }
    }
    return 0;
}
