#include<cstdio>
#include<string>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int BAR = 5000000;

int n, k;

string rands() {
    string ret;
    for (int i = 0; i < n; ++i) {
        ret += (char)((rand() % 2) + '0');
    }
    return ret;
}

int main() {
    freopen("L2.in", "w", stdout);
    scanf("%d", &n);
    k = min((long long)BAR / n, (1ll << n) - 2);
    printf("%d %d\n", n, k);
    printf("%s %s\n", rands().c_str(), rands().c_str());
    for (int i = 0; i < k; ++i) {
        printf("%s\n", rands().c_str());
    }
    return 0;
}
