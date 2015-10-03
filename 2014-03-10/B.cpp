#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 30005;
int n, x[N];

void left(long long t) {
    for (int i = 0; i < 62; ++i) {
        if (t >> i & 1) {
            long long l = 1ll << i;
            for (int j = 0; j < n; ++j) {
                if (j >= l) {
                    x[j] ^= x[j - l];
                }
            }
        }
    }
}

void right(long long t) {
    for (int i = 0; i < 62; ++i) {
        if (t >> i & 1) {
            long long l = 1ll << i;
            for (int j = n - 1; j >= 0; --j) {
                if (j >= l) {
                    x[j] ^= x[j - l];
                }
            }
        }
    }
}

const int L = 100005;
int match[L];
char s[L];

long long cal(int l, int r) {
    long long ret = 0, tmp = 0;
    for (int i = l; i <= r; ++i) {
        if (s[i] >= '0' && s[i] <= '9') {
            tmp = tmp * 10 + (s[i] - '0');
        } else if (s[i] == '(') {
            long long tmp2 = cal(i + 1, match[i] - 1);
            ret += tmp * tmp2;
            tmp = 0;
            i = match[i];
        } else if (s[i] == 'L') {
            ++ret;
        } else {
            --ret;
        }
    }
    return ret;
}

int main() {
    freopen("xoring.in", "r", stdin);
    freopen("xoring.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", x + i);
    }
    scanf("%s", s);
    int l = strlen(s);
    memset(match, -1, sizeof(match));
    vector<int> stack;
    for (int i = 0; i < l; ++i) {
        if (s[i] >= '0' && s[i] <= '9' || s[i] == 'R' || s[i] == 'L') {
            continue;
        }
        if (s[i] == '(') {
            stack.push_back(i);
        } else {
            match[stack.back()] = i;
            stack.pop_back();
        }
    }
    long long c = cal(0, l - 1);
    if (c > 0) {
        left(c);
    } else if (c < 0) {
        right(-c);
    }
    for (int i = 0; i < n; ++i) {
        printf("%d%c", x[i], i == n - 1 ? '\n' : ' ');
    }
    return 0;
}
