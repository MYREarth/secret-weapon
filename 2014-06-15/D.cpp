#include<map>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

typedef unsigned long long INT;

vector<INT> p;

bool check(const INT &a, const INT &b) {
    return (1ull << 63) / a >= b;
}

map<INT, INT> mem;

void update(const INT &ans, const INT &mul) {
    if (!mem.count(mul) || mem[mul] > ans) {
        mem[mul] = ans;
    }
}

void go(int i, INT used, INT ans, int last, INT mul) {
    update(ans, mul);
    for (int j = 1; j <= last; ++j) {
        if (!check(ans, p[i])) {
            return;
        }
        ans *= p[i];
        INT g = __gcd((INT)j, mul);
        if (!check(mul / g, (used + j) * g / j)) {
            return;
        }
        mul /= g, mul *= (used + j) * g / j;
        go(i + 1, used + j, ans, j, mul);
    }
}

int main() {
    for (int i = 2; (int)p.size() < 63; ++i) {
        bool check = true;
        for (int j = 0; j < (int)p.size(); ++j) {
            if (i % p[j] == 0) {
                check = false;
                break;
            }
        }
        if (check) {
            p.push_back(i);
        }
    }
    go(0, 0, 1, 63, 1);
    mem[1] = 2;
    INT n;
    while (scanf("%llu", &n) == 1) {
        printf("%llu %llu\n", n, mem[n]);
    }
    return 0;
}
