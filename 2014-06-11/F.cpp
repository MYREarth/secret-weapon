#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int len(long long a) {
    int ret = 0;
    while (a) {
        a /= 10;
        ++ret;
    }
    return ret - 1;
}

long long dp[19][1 << 11][11];

#define pow POW

long long pow[19];

inline void transform(int &st) {
    int ret = 0;
    for (int i = 0; i < 11; ++i) {
        if (st >> i & 1) {
            ret |= 1 << (i * 10 % 11);
        }
    }
    st = ret;
}

long long cal(long long num, int i, int st, int re, bool eql, bool first) {
//cout << num << ' ' << i << ' ' << st << ' ' << re << ' ' << eql << ' ' << first << endl;
    if (i == -1) {
        return st & 1;
    }
    if (!eql && !first) {
        if (dp[i][st][re] != -1) {
            return dp[i][st][re];
        }
    }
    long long ret = 0;
    int d = num / pow[i] % 10;
    for (int j = 0; j < 10; ++j) {
        if (eql && j > d) {
            continue;
        }
        if (j == 0 && first) {
            ret += cal(num, i - 1, st, re, false, true);
            continue;
        }
        int nr = (re * 10 + j) % 11, nst = st;
        transform(nst);
        if (nst >> nr & 1) {
            nst |= 1;
        }
        nst |= 1 << nr;
        ret += cal(num, i - 1, nst, nr, eql && j == d, false);
    }
    if (!eql && !first) {
        dp[i][st][re] = ret;
    }
    return ret;
}

int main() {
    pow[0] = 1;
    for (int i = 1; i < 19; ++i) {
        pow[i] = pow[i - 1] * 10;
    }
    memset(dp, -1, sizeof(dp));
    int t;
    scanf("%d", &t);
    while (t--) {
        long long a, b;
        scanf("%lld %lld", &a, &b);
        swap(a,b);
        --b;
        printf("%lld\n", cal(a, len(a), 0, 0, true, true) - cal(b, len(b), 0, 0, true, true));
    }
    return 0;
}
