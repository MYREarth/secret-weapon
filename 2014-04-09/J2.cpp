#include<map>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 100005;

map<int, long long> mem[N];

long long solve(long long n, long long m, long long k) {
    if (mem[n].count(m)) {
        return mem[n][m];
    }
    long long ret = 0;
    if (k < n) {
        ret = m;
    } else if (k % n == 0) {
//cout << "A" << ' ' << n << ' ' << m << ' ' << k << ' ' << m * (k / n * 2 - 1) << endl;
        ret = m * (k / n * 2 - 1);
    } else if (m == 1) {
//cout << "B" << ' ' << n << ' ' << m << ' ' << k << ' ' << m * (k / n * 2 + 1) << endl;
        ret = m * (k / n * 2 + 1);
    } else if (m == 0) {
        ret = 0;
    } else {
        long long lx = 0, rx = m, mx, t = k % n;
        while (lx + 1 < rx) {
            mx = lx + rx >> 1;
            long long tt = solve(n - t, mx, k - t);
            if (2 * m - mx <= tt) {
                rx = mx;
            } else {
                lx = mx;
            }
        }
        ret = min(max(solve(n - t, lx, k - t), 2 * m - lx) + ((k / n) * 2 - 1) * (m - lx), max(solve(n - t, rx, k - t), 2 * m - rx) + (k / n * 2 - 1) * (m - rx));
    }
//cout << lx << ' ' << rx << ' ' << n << ' ' << m << ' ' << k << ' ' << ret << endl;
    return mem[n][m] = ret;
}

int main() {
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    long long n, m, k;
    cin >> n >> m >> k;
    cout << solve(n, m, k) << endl;
    //cout << (2 * m * k + n - 1) / n - m << endl;
    return 0;
}
