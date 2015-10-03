#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

typedef unsigned long long HASH;

const int N = 10005;
const HASH MAGIC = 10007;

int n, m, k;
char s1[N], s2[N];

#define pow POW

HASH pow[N], hash1[N], hash2[N];

void hashz(char *s, int n, HASH hash[]) {
    for (int i = 0; i < n; ++i) {
        hash[i + 1] = hash[i] * MAGIC + s[i];
    }
}

inline HASH gethash(const HASH hash[], const int &i, const int &j) {
    return hash[j] - hash[i] * pow[j - i];
}

HASH a[N], b[N];

int main() {
    //freopen("strings.in", "r", stdin);
    //freopen("strings.out", "w", stdout);
    scanf("%s%s%d", s1, s2, &k);
    n = strlen(s1), m = strlen(s2);
    hashz(s1, n, hash1), hashz(s2, m, hash2);
    pow[0] = 1;
    for (int i = 1; i <= max(n, m); ++i) {
        pow[i] = pow[i - 1] * MAGIC;
    }
    int ans = 0;
    for (int i = 1; i <= n && i <= m - k + 1; ++i) {
        int top1 = 0, top2 = 0;
        for (int j = 0; j + i <= n; ++j) {
            a[top1++] = gethash(hash1, j, j + i);
        }
        sort(a, a + top1);
        for (int j = 0; j + i <= m; ++j) {
            b[top2++] = gethash(hash2, j, j + i);
        }
        sort(b, b + top2);
        int p = 0;
        for (int j = 0; j < top1; ++j) {
            int cnt = 0;
            while (p < top2 && b[p] <= a[j]) {
                cnt += b[p] == a[j];
                ++p;
            }
            ans += cnt == k;
        }
    }
    printf("%d\n", ans);
    return 0;
}
