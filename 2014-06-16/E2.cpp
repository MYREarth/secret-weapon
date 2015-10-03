#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 1005;

int dp[N];

int main() {
    for (int i = 0; i < N; ++i) {
        dp[i] = i;
    }
    for (int i = 1; 1 + 3 * (i - 1) * i < N; ++i) {
        int p = 1 + 3 * (i - 1) * i;
        for (int j = 0; j + p < N; ++j) {
            dp[j + p] = min(dp[j + p], dp[j] + 1);
        }
    }
    int n;
    while (scanf("%d", &n) == 1 && n) {
        printf("%d\n", dp[n]);
    }
    return 0;
}
