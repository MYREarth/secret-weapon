#include<bitset>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 200005;
char s[N];

bitset<N * 4> ori, ans;

void transform_to(int l, char *s, bitset<N * 4> &t) {
    int n = l * 4;
    for (int i = 0; i < l; ++i) {
        int d = s[i] >= '0' && s[i] <= '9' ? s[i] - '0' : s[i] - 'A' + 10;
        for (int j = 3; j >= 0; --j) {
            t[n - (i + 1) * 4 + j] = d >> j & 1;
        }
    }
}

void transform_from(int n, bitset<N * 4> &t, char *s) {
    while (t[n - 1] == 0) {
        --n;
    }
    for (int i = 0; i <= n / 4; ++i) {
        s[i] = 0;
    }
    for (int i = n - 1; i >= 0; --i) {
        int u = i >> 2;
        s[u] |= (int)(t[i]) << (i & 3);
    }
    s[((n - 1) >> 2) + 1] = '\0';
    reverse(s, s + (((n - 1) >> 2) + 1));
    for (int i = 0; i < (((n - 1) >> 2) + 1); ++i) {
        if (s[i] < 10) {
            s[i] = s[i] + '0';
        } else {
            s[i] = s[i] + 'A' - 10;
        }
    }
}

int main() {
    scanf("%s", s);
    int l = strlen(s), n = 4 * l;
    transform_to(l, s, ori);
    long long left = ori[n - 1], cnt_front = 0;
    int first_one = -1;
    for (int i = 0; i <= n - 1; ++i) {
        if (ori[i] == 1) {
            first_one = i;
            break;
        }
    }
    for (int i = n - 1; i >= 0; --i) {
        if (i == 0) {
            if (left > cnt_front) {
                ans.set(i);
            }
        } else {
            left = left << 1;
            left |= ori[i - 1];
            if (left > cnt_front * 2 + i || left == cnt_front * 2 + i && i - 1 > first_one) {
                ans.set(i);
                left -= cnt_front * 2 + i;
                ++cnt_front;
            }
        }
    }
    transform_from(n, ans, s);
    printf("%s\n", s);
    return 0;
}
