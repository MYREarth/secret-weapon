#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

long long n;
vector<long long> primes;
long long ans;

void go(int i, long long mul, long long sign) {
    if (i == primes.size()) {
        ans += sign * (n / mul);
        return;
    }
    go(i + 1, mul, sign);
    go(i + 1, mul * primes[i], -sign);
}

int main() {
    freopen("square.in", "r", stdin);
    freopen("square.out", "w", stdout);
    long long s;
    scanf("%lld", &s);
    if (s % 2 == 1) {
        printf("0\n");
        return 0;
    }
    s += 2;
    n = s / 2;
    for (long long i = 2; i * i <= s; ++i) {
        if (s % i == 0) {
            primes.push_back(i);
            while (s % i == 0) {
                s /= i;
            }
        }
    }
    if (s != 1) {
        primes.push_back(s);
        s = 1;
    }
    ans = 0;
    go(1, 1, 1);
    printf("%lld\n", ans);
    return 0;
}
