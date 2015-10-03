#include<cassert>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int MOD = 1000000007;

long long pow(long long n) {
    long long ret = 1, mul = 2;
    while (n) {
        if (n & 1) {
            (ret *= mul) %= MOD;
        }
        n >>= 1;
        (mul *= mul) %= MOD;
    }
    return ret;
}

long long solve(long long n, long long l, long long r, long long k) {
    long long pl = l, pr = n - r + 1;
    if (pl > n || pr < 1) {
        return 1;
    } else {
        if (pr - pl >= k) {
            return min(min(k, n - l + 1) + 1, min(k, n - r + 1) + 1) % MOD;
        } else if (pl > pr) {
            return pow(min(min(k, n - l + 1), min(k, n - r + 1)));
        } else {
            long long d = pr - pl + 1;
            return pow(min(min(k - d, n - d - l + 1), min(k - d, n - d - r + 1)));
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) {
        long long n, l, r, k;
        cin >> n >> l >> r >> k;
        assert(solve(n, l, r, k) == solve(n, r, l, k));
        cout << solve(n, l, r, k) << endl;
    }
    return 0;
}
