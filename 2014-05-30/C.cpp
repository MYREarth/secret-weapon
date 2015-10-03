#include <cstdio>
#include <cstring>
#include <vector>

const int MOD = (int)1e9 + 9;

const int N = 5000;

int getInverse(int a) {
    return a == 1 ? 1 : (long long)(MOD - MOD / a) * getInverse(MOD % a) % MOD;
}

struct Polyonmial {
    Polyonmial(int degree = 0) : coefficient(degree, 0) {}

    int& operator[](int i) {
        return coefficient[i];
    }

    int operator[](int i) const {
        return coefficient[i];
    }

    int degree() const {
        return coefficient.size();
    }

    Polyonmial &shift() {
        int d = degree();
        coefficient.resize(d + 1);
        for (int i = d - 1; i >= 0; -- i) {
            coefficient[i + 1] = coefficient[i];
        }
        coefficient[0] = 0;
        return *this;
    }

    Polyonmial inverse(int n) {
        // mod x^n
        Polyonmial a(n);
        Polyonmial &b = *this;
        int m = b.degree();
        a[0] = 1;
        Polyonmial c(n);
        for (int i = 0; i < n; ++ i) {
            c[i] = (long long)a[i] * getInverse(b[0]) % MOD;
            for (int j = 0; j < m && i + j < n; ++ j) {
                a[i + j] += MOD - (long long)c[i] * b[j] % MOD;
                if (a[i + j] >= MOD) {
                    a[i + j] -= MOD;
                }
            }
        }
        return c;
    }

    void dump() {
        for (int i = 0; i < degree(); ++ i) {
            printf("%12d", coefficient[i]);
        }
        puts("");
    }

    std::vector <int> coefficient;
};

Polyonmial operator - (const Polyonmial &a, const Polyonmial &b) {
    Polyonmial c(std::max(a.degree(), b.degree()));
    for (int i = 0; i < c.degree(); ++ i) {
        int &result = c[i];
        if (i < a.degree()) {
            result += a[i];
        }
        if (i < b.degree()) {
            result += MOD - b[i];
        }
        if (result >= MOD) {
            result -= MOD;
        }
    }
    return c;
}

Polyonmial operator * (const Polyonmial &a, const Polyonmial &b) {
    Polyonmial c(a.degree() + b.degree() - 1);
    for (int i = 0; i < a.degree(); ++ i) {
        for (int j = 0; j < b.degree(); ++ j) {
            c[i + j] += (long long)a[i] * b[j] % MOD;
            if (c[i + j] >= MOD) {
                c[i + j] -= MOD;
            }
        }
    }
    return c;
}

int n, m;
Polyonmial p, q;

int main() {
    freopen("comb.in", "r", stdin);
    freopen("comb.out", "w", stdout);
    scanf("%d%d", &m, &n);
    //memset(ways, 0, sizeof(ways));
    //for (int k = 2; k <= m; ++ k) {
    //    ways[k][1] = 1;
    //    for (int i = 2; i <= n; ++ i) {
    //        for (int j = 1; j < i; ++ j) {
    //            ways[k][i] += (long long)ways[k][j] * ways[k - 1][i - j] % MOD;
    //            if (ways[k][i] >= MOD) {
    //                ways[k][i] -= MOD;
    //            }
    //        }
    //    }
    //}
    //for (int i = 1; i <= n; ++ i) {
    //    printf("%d\n", ways[m][i]);
    //}

    // p = 0, q = 1
    q.coefficient.resize(1);
    q[0] = 1;
    for (int i = 2; i <= m; ++ i) {
        p = q - p;
        std::swap(p, q);
        p.shift();
    }
    p = p * q.inverse(n + 1);
    for (int i = 1; i <= n; ++ i) {
        printf("%d\n", p[i]);
    }
    return 0;
}
