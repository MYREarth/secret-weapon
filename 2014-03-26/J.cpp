#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const long long MOD = 1000000007ll;

long long pow(long long a, long long n) {
    long long ret = 1, mul = a;
    while (n) {
        if (n & 1) {
            (ret *= mul) %= MOD;
        }
        (mul *= mul) %= MOD;
        n >>= 1;
    }
    return ret;
}

long long rev(long long a) {
    return a == 1 ? 1ll : (MOD - MOD / a) * rev(MOD % a) % MOD;
}

int main() {
    freopen("xoring.in", "r", stdin);
    freopen("xoring.out", "w", stdout);
    long long n, c, m;
    cin >> n >> c >> m;
    if (n == 0) {
        cout << c << endl;
        return 0;
    }
    vector<long long> rk;
    for (int i = 0; i < m; ++i) {
        long long t;
        scanf("%lld", &t);
        for (int j = 0; j < (int)rk.size(); ++j) {
            if ((t ^ rk[j]) < t) {
                t ^= rk[j];
            }
        }
        if (t != 0) {
            rk.push_back(t);
            sort(rk.begin(), rk.end());
            reverse(rk.begin(), rk.end());
        }
    }
    long long d = rk.size();
    long long ans = (pow(c, 1ll << n) + ((1ll << d) - 1) % MOD * pow(c, 1ll << n - 1)) % MOD * rev((1ll << d) % MOD) % MOD;
    cout << ans << endl;
    return 0;
}
