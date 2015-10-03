#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cassert>
using namespace std;

typedef unsigned long long RND;

const int N = 1000;

int n;
long long b, m, p[N], rp[N];

long long mulmod(long long a, long long b, long long m) {
    long long ret = 0;
    while (a) {
        if (a & 1) {
            (ret += b) %= m;
        }
        (b <<= 1) %= m;
        a >>= 1;
    }
    return ret;
}

bool a[N], c[N];

const int BAR = 10000000;
int B;
long long s[BAR];

typedef unsigned long long HASH;

const HASH MOD = 1000000000000000000ll + 3;

HASH ad[N], mi[N];

HASH f[BAR];

int ord[BAR];

bool by_hash(int i, int j) {
    return s[i] < s[j] || s[i] == s[j] && f[i] < f[j];
}

int cnt = 0;

bool work() {
cout << ++cnt << endl;
    memset(a, 0, sizeof(a));
    RND start = rand();
    srand(start);
    HASH k = 0;
    long long cur = 0, hash = -1;
    for (int i = 0; i < B; ++i) {
        s[i] = cur;
        f[i] = k;
        int t = rand() % 1000;
        if (a[t]) {
            a[t] = false;
            if ((cur += rp[t]) >= m) {
                cur -= m;
            }
            if ((k += ad[t]) >= MOD) {
                k -= MOD;
            }
        } else {
            a[t] = true;
            if ((cur += p[t]) >= m) {
                cur -= m;
            }
            if ((k += mi[t]) >= MOD) {
                k -= MOD;
            }
        }
    }
    sort(ord, ord + B, by_hash);
    for (int i = 0; i + 1 < B; ++i) {
        int j = i + 1;
        while (j < B && s[ord[i]] == s[ord[j]]) {
            ++j;
        }
        --j;
        if (i != j || f[ord[i]] != f[ord[j]]) {
            hash = s[ord[i]];
            break;
        }
        i = j;
    }
    if (hash == -1) {
        return false;
    }
    srand(start);
    memset(a, 0, sizeof(a));
    cur = 0, k = 0;
    long long cal = 0;
    HASH mem;
    for (int i = 0; i < B; ++i) {
        if (cur == hash) {
            if (cal == 0) {
                mem = k;
                for (int j = 0; j < 1000; ++j) {
                    c[j] = a[j];
                }
                cal = 1;
            } else if (k != mem) {
                bool same = true;
                for (int j = 0; j < 1000; ++j) {
                    same = same && c[j] == a[j];
                }
                if (same) {
                    continue;
                }
                for (int j=999;j>=0;j--)
                    printf("%d",c[j]);
                printf("\n");
                for (int j=999;j>=0;j--)
                    printf("%d",a[j]);
                printf("\n");
                return(true);
            }
        }
        int t = rand() % 1000;
        if (a[t]) {
            a[t] = false;
            if ((cur += rp[t]) >= m) {
                cur -= m;
            }
            if ((k += ad[t]) >= MOD) {
                k -= MOD;
            }
        } else {
            a[t] = true;
            if ((cur += p[t]) >= m) {
                cur -= m;
            }
            if ((k += mi[t]) >= MOD) {
                k -= MOD;
            }
        }
    }
    return false;
}

int main()
{
    //freopen("hash.in", "r", stdin);
    //freopen("hash.out", "w", stdout);
    scanf("%lld%lld", &b, &m);
    //B = min(10005, (int)sqrt((long double)m));
    B = 1000000;
    n = 1000;
    p[0] = 1;
    rp[0] = m - 1;
    for (int i = 1; i < n; ++i) {
        p[i] = mulmod(p[i - 1], b, m);
        rp[i] = (m - p[i]) % m;
    }
    ad[0] = 1, mi[0] = MOD - ad[0];
    for (int i = 1; i < n; ++i) {
        ad[i] = (ad[i - 1] << 1) % MOD;
        mi[i] = MOD - ad[i];
    }
    for (int i = 0; i < B; ++i) {
        ord[i] = i;
    }
    while (!work());
    return 0;
}

