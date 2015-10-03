#include<vector>
#include<cstdio>
#include<string>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int MOD = 1000000007;

const int L = 21, P = 55;
int t, n, p, q;
bool usel[P], usem[P];
char l[P][L], m[P][L];

bool isprefix(const char* s2, const char* s1) {
    int l1 = strlen(s1), l2 = strlen(s2);
    if (l1 > l2) {
        return false;
    }
    for (int i = 0; i < l1; ++i) {
        if (s1[i] != s2[i]) {
            return false;
        }
    }
    return true;
}

bool issuffix(const char* s2, const char* s1) {
    int l1 = strlen(s1), l2 = strlen(s2);
    if (l1 > l2) {
        return false;
    }
    for (int i = 0; i < l1; ++i) {
        if (s1[l1 - 1 - i] != s2[l2 - 1 - i]) {
            return false;
        }
    }
    return true;
}

int reverse(int a) {
    return a == 1 ? 1 : (long long)(MOD - MOD / a) * reverse(MOD % a) % MOD;
}

int pow(int t, int n) {
    int ret = 1, mul = t;
    while (n) {
        if (n & 1) {
            ret = (long long)ret * mul % MOD;
        }
        mul = (long long)mul * mul % MOD;
        n >>= 1;
    }
    return ret;
}

int sum(int t, int n) {
    return t == 1 ? n + 1 : (long long)(pow(t, n + 1) - 1) * reverse(t - 1) % MOD;
}

bool check(int i, int j, int k) {
    int l1 = strlen(l[i]);
    for (int o = 0; o < k; ++o) {
        if (l[i][l1 - k + o] != m[j][o]) {
            return false;
        }
    }
    return true;
}

int main() {
    scanf("%d%d", &t, &n);
    scanf("%d", &p);
    for (int i = 0; i < p; ++i) {
        scanf("%s", l[i]);
        usel[i] = true;
    }
    for (int i = 0; i < p; ++i) {
        for (int j = 0; j < p && usel[i]; ++j) {
            if (i != j && usel[j] && isprefix(l[i], l[j])) {
                usel[i] = false;
            }
        }
    }
    scanf("%d", &q);
    for (int i = 0; i < q; ++i) {
        scanf("%s", m[i]);
        usem[i] = true;
    }
    for (int i = 0; i < q; ++i) {
        for (int j = 0; j < q && usem[i]; ++j) {
            if (i != j && usem[j] && issuffix(m[i], m[j])) {
                usem[i] = false;
            }
        }
    }
    int ans = sum(t, n);
    for (int i = 0; i < p; ++i) {
        if (!usel[i]) {
            continue;
        }
        if (strlen(l[i]) <= n) {
            ans = (ans - sum(t, n - strlen(l[i]))) % MOD;
        }
    }
    for (int i = 0; i < q; ++i) {
        if (!usem[i]) {
            continue;
        }
        if (strlen(m[i]) <= n) {
            ans = (ans - sum(t, n - strlen(m[i]))) % MOD;
        }
    }
    for (int i = 0; i < p; ++i) {
        if (!usel[i]) {
            continue;
        }
        for (int j = 0; j < q; ++j) {
            if (!usem[j]) {
                continue;
            }
            int l1 = strlen(l[i]), l2 = strlen(m[j]);
            if (l1 + l2 <= n) {
                ans = (ans + sum(t, n - (l1 + l2))) % MOD;
            }
            for (int k = 1; k <= l1 && k <= l2; ++k) {
                if (l1 + l2 - k <= n && check(i, j, k)) {
                    ans = (ans + 1) % MOD;
                }
            }
        }
    }
    if (ans < 0) {
        ans += MOD;
    }
    printf("%d\n", ans);
    return 0;
}

