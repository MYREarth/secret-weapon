#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const long long BAR = 1000000000000ll;
vector<long long> p;

int main() {
    for (long long i = 1; ; ++i) {
        p.push_back(1 + 3 * (i - 1) * i);
        if (p.back() > BAR) {
            break;
        }
    }
    long long n;
    while (scanf("%lld", &n) == 1 && n) {
        int ans = 0;
        if (n % 3 == 0) {
            if (n % 2 == 1) {
                ans = 3;
            } else {
                ans = 6;
            }
        } else if (n % 3 == 1) {
            if (*lower_bound(p.begin(), p.end(), n) == n) {
                ans = 1;
            } else {
                if (n % 2 == 1) {
                    ans = 7;
                } else {
                    ans = 4;
                }
            }
        } else {
            if (n % 2 == 0) {
                bool flag = false;
                int j = upper_bound(p.begin(), p.end(), n) - p.begin();
                for (int i = 0; i <= j; ++i) {
                    while (p[i] + p[j] > n) {
                        --j;
                    }
                    if (p[i] + p[j] == n) {
                        flag = true;
                        break;
                    }
                }
                if (flag) {
                    ans = 2;
                } else {
                    ans = 8;
                }
            } else {
                ans = 5;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
