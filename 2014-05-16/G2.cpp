#include<set>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 100005;
int n;
char s[N];

typedef unsigned long long HASH;

const int MAGIC = 37;

#define pow POW

HASH h[N], pow[N];

HASH gethash(int i, int l) {
    return h[i + l] - h[i] * pow[l];
}

set<HASH> vis;

int main() {
    scanf("%s", s);
    n = strlen(s);
    pow[0] = 1;
    for (int i = 1; i <= n; ++i) {
        pow[i] = pow[i - 1] * MAGIC;
    }
    for (int i = 0; i < n; ++i) {
        h[i + 1] = h[i] * MAGIC + s[i] - 'a' + 1;
    }
    for (int l = 1; l * 3 <= n; ++l) {
        int cnt = 0;
        for (int i = 0; i + l <= n; ++i) {
            HASH h = gethash(i, l);
            if (vis.count(h)) {
                continue;
            }
            vis.insert(h);
            int last = i, num = 1;
            for (int j = i + 1; j + l <= n && num < 3; ++j) {
                if (j < last + l) {
                    continue;
                }
                if (gethash(j, l) == h) {
                    ++num;
                    last = j;
                }
            }
            cnt += num >= 3;
        }
        printf("%d ", cnt);
    }
    return 0;
}
