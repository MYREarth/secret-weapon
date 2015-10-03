#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 1000005, INF = 1000000000;

int n, a[N], b[N];

int f[N];

bool visa[N], visb[N];

int belong[N], num[N];

int cnta, size[N], delta[N], len[N];

int lb[N], ub[N], rem[N];

bool solve() {
}

int main() {
    f[1] = 1;
    for (int i = 2; i < N; ++i) {
        if (f[i] == 0) {
            f[i] = i;
            for (long long j = (long long)i * i; j < N; j += i) {
                f[j] = i;
            }
        }
    }

    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", a + i);
        --a[i];
    }
    for (int i = 0; i < n; ++i) {
        scanf("%d", b + i);
        --b[i];
    }

    cnta = 0;
    for (int i = 0; i < n; ++i) {
        if (!visa[i]) {
            int t = i, col = cnta++, cnt = 0;
            while (!visa[t]) {
                belong[t] = col, num[t] = cnt++;
                visa[t] = true;
                t = a[t];
            }
            len[col] = cnt;
        }
    }

    for (int i = 0; i < cnta; ++i) {
        size[i] = 0, delta[i] = -1;
    }

    for (int i = 0; i < n; ++i) {
        if (!visb[i]) {
            for (int t = i; !visb[t] && !fail; t = b[t]) {
                visb[t] = true;
                v.push_back(num[t]);
            }
            int t = i, col = belong[t];
            vector<int> v;
            bool fail = false;
            while (!visb[t]) {
                v.push_back(num[t]);
                visb[t] = true;
                t = b[t];
                if (belong[t] != col) {
                    fail = true;
                    break;
                }
            }
            if (fail) {
                printf("NIE\n");
                return 0;
            }
            v.push_back(v.front());
            int d = v[1] - v[0];
            if (d < 0) {
                d = len[col] + d;
            }
            for (int j = 0; j + 1 < (int)v.size(); ++j) {
                int nd = v[j + 1] - v[j];
                if (nd < 0) {
                    nd += len[col];
                }
                if (nd != d) {
                    fail = true;
                    break;
                }
            }
            if (delta[col] == -1) {
                delta[col] = d;
            }
            if (delta[col] != d) {
                fail = true;
            }
            if (fail) {
                printf("NIE\n");
                return 0;
            }
        }
    }

    memset(rem, -1, sizeof(rem));
    for (int i = 0; i < cnta; ++ i) {
        if (rem[len[i]] != -1 && rem[len[i]] != delta[i]) {
            puts("NIE");
            return 0;
        }
        rem[len[i]] = delta[i];
    }
    bool valid = true;
    for (int i = 1; i <= n && valid; ++ i) {
        int ret = -1;
        for (int j = i; j <= n && valid; j += i) {
            if (rem[j] != -1) {
                if (ret != -1 && rem[j] % i != ret) {
                    valid = false;
                }
                ret = rem[j] % i;
            }
        }
    }

    puts(valid ? "TAK" : "NIE");
    return 0;
}
