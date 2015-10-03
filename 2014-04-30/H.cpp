#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

vector<pair<long long, long long> > ans;

void solve(long long sum, long long n) {
    long long a = (sum / n + 1 - n) / 2;
    if (a > 0 && (a + a + n - 1) * n == sum) {
        ans.push_back(make_pair(a, a + n - 1));
    }
}

int main() {
    long long n;
    cin >> n;
    n *= 2;
    for (long long i = 1; i * i <= n; ++i) {
        if (n % i == 0) {
            solve(n, i);
            if (n / i != i) {
                solve(n, n / i);
            }
        }
    }
    if (ans.size() != 0) {
        sort(ans.begin(), ans.end());
    }
    printf("%d\n", (int)ans.size());
    for (int i = 0; i < (int)ans.size(); ++i) {
        printf("%lld %lld\n", ans[i].first, ans[i].second);
    }
}
