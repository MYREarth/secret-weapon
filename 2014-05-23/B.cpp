#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 30;

#define pow POW

int pow;

int n, mod;

struct Data {
    int pre[N][N], suf[N], cnt, len, all;

    Data (int num = -1) {
        memset(pre, 0, sizeof(pre));
        memset(suf, 0, sizeof(suf));
        cnt = 0;
        len = -1;
        all = 0;

        if (num != -1) {
            len = pow;
            all = num % n;
            cnt += num % n == 0;
            if (num == 0) {
                ++pre[pow][0];
            } else {
                ++suf[num % n];
                ++pre[pow][num % n];
            }
        }
    }

};

inline void update(int &a, const int &b) {
    if ((a += b) >= mod) {
        a -= mod;
    }
}

Data merge(const Data &a, const Data &b) {
    if (a.len == -1) {
        return b;
    }
    if (b.len == -1) {
        return a;
    }
    Data ret;
    update(ret.cnt, (a.cnt + b.cnt) % mod);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int k = (n - i * j % n) % n;
            update(ret.cnt, (long long)a.suf[i] * b.pre[j][k] % mod);
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            ret.pre[i][j] = a.pre[i][j];
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            update(ret.pre[a.len * i % n][(a.all * i + j) % n], b.pre[i][j]);
        }
    }
    for (int i = 0; i < n; ++i) {
        ret.suf[i] = b.suf[i];
    }
    for (int i = 0; i < n; ++i) {
        update(ret.suf[(i * b.len + b.all) % n], a.suf[i]);
    }
    ret.len = a.len * b.len % n;
    ret.all = (a.all * b.len + b.all) % n;
    return ret;
};

Data mem[26];

const int L = 105;
char op[26][L];

int main() {
    freopen("divisible.in", "r", stdin);
    freopen("divisible.out", "w", stdout);
    scanf("%d%d", &n, &mod);
    pow = 10 % n;
    int k;
    scanf("%d", &k);
    for (int i = 0; i < k; ++i) {
        scanf("%s", op[i]);
    }
    for (int _ = k - 1; _ >= 0; --_) {
        int i = op[_][0] - 'A', l = strlen(op[_]);
        for (int j = 3; j < l; ++j) {
            if (isdigit(op[_][j])) {
                mem[i] = merge(mem[i], Data(op[_][j] - '0'));
            } else {
                mem[i] = merge(mem[i], mem[op[_][j] - 'A']);
            }
        }
    }
    printf("%d\n", mem[0].cnt % mod);
    return 0;
}
