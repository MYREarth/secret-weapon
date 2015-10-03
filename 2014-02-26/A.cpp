#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int main() {
    freopen("coprime.in", "r", stdin);
    freopen("coprime.out", "w", stdout);
    int n;
    scanf("%d", &n);
    int ans = 0;
    for (int i = 0; i < 6; ++i) {
        ans = max(ans, (n + i) / 2 + (n + i) / 3 - (n + i) / 6 - i / 2 - i / 3);
    }
    printf("%d\n", ans + 1);
    return 0;
}
