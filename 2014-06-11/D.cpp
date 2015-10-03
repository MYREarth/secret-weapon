#include<vector>
#include<cstdio>
#include<string>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int l;

long long k;

const int L = 26 + 1;
char s[L], t[L];

const int N = 64;
long long f[N][L];

int main() {
    scanf("%d%lld", &l, &k);
    scanf("%s", s);
    int len = -1;
    f[0][l] = 1;
    for (int i = 1; ; ++i) {
        for (int j = 0; j <= l; ++j) {
            f[i][j] = j * f[i - 1][j];
            if (j < l) {
                f[i][j] += f[i - 1][j + 1];
            }
        }
        if (f[i][0] < k) {
            k -= f[i][0];
        } else {
            len = i;
            break;
        }
    }
    string ans;
    for (int i = 0; i < l; ++i) {
        t[i] = s[i];
    }
    for (int i = len, j = 0; i > 0; --i) {
        sort(t, t + j + 1);
        long long K = k;
        for (int k = 0; k <= j; ++k) {
            long long cost = 0, deltaj = 0;
            if (t[k] == s[j]) {
                cost = f[i - 1][j + 1];
                deltaj = 1;
            } else {
                cost = f[i - 1][j];
                deltaj = 0;
            }
            if (cost < K) {
                K -= cost;
            } else {
                ans += t[k];
                j += deltaj;
                break;
            }
        }
        k = K;
    }
    printf("%s\n", ans.c_str());
    return 0;
}

