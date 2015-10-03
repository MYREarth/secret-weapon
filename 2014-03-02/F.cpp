#include<map>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 70000;

long long ans[N + 1], cnt[N + 1];
map<long long, int> mem;

long long cal(long long t) {
    if (ans[t] != -1) {
        return ans[t];
    }
    long long ret = t, add = 1;
    for (int i = t - 1; i > 0; --i) {
        long long tmp = add; 
        if (tmp % i == 0) {
            add += tmp / i;
        } else {
            ret += i - tmp % i;
            add += tmp / i + 1;
        }
    }
    mem[ret] = t;
    return ans[t] = ret;
}

void create(int t) {
    cnt[t] += t;
    long long add = 1;
    for (int i = t - 1; i > 0; --i) {
        long long tmp = add;
        if (tmp % i == 0) {
            add += tmp / i;
        } else {
            cnt[i] += i - tmp % i;
            add += tmp / i + 1;
        }
    }
}

long long make(long long n) {
    int next = -1;
    if (mem.count(n)) {
        next = mem[n];
    } else {
        int r = mem.lower_bound(n)->second, l = (--mem.lower_bound(n))->second;
        while (l < r) {
            int m = l + r + 1 >> 1;
            long long c = cal(m);
            if (c > n) {
               r = m - 1;
            } else {
               l = m;
            } 
        }
        next = l;
    }
    create(next);
    return n -= cal(next);
}

int main() {
    for (int i = 0; i <= N; ++i) {
        ans[i] = -1;
    }
    for (int i = 1; i <= 8000; ++i) {
        cal(i);
    }
    cal(N);
    long long n;
    scanf("%lld", &n);
    while (n) {
        n = make(n);
    }
    for (int i = 0; i < N; ++i) {
        if (cnt[i]) {
            printf("%d %lld\n", i, cnt[i]);
        }
    }
    return 0;
}

