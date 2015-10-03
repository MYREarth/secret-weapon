#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int n, k, p;

const int N = 1000;
double dp[N];

int main() {
    scanf("%d%d%d", &n, &k, &p);
    double r = (double)p / k;
    dp[0] = 0, dp[1] = 1;
    for (int i = 2; i <= n; ++i) {
        dp[i] = 0;
        for (int j = 0; j < i - 1; ++j) {
            dp[i] += (1 - r) * (dp[1 + j] + dp[i - j - 1]) + r * (dp[1 + j] + (i - j - 2 >= 0 ? dp[i - j - 2] : 0.0));
        }
        dp[i] /= (i - 1);
    }
    printf("%.12f\n", (dp[n] * (1 - r) + dp[n - 1] * r) / n);
    return 0;
}
