#include<vector>
#include<cstdio>
#include<string>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int L = 105;

string dp[L][L];

int main() {
    string ZZZ;
    for (int i = 0; i < L; ++i) {
        ZZZ += 'Z';
    }
    string s;
    cin >> s;
    int n = s.size();
    for (int i = 1; i <= n; ++i) {
        for (int j = i - 1; j <= n; ++j) {
            dp[i][j] = ZZZ;
        }
    }
    for (int i = 1; i <= n; ++i) {
        dp[i][i] = dp[i][i - 1] = "";
    }
    for (int l = 0; l < n; ++l) {
        for (int j = 1; j + l - 1 <= n; ++j) {
            int k = j + l - 1;
            if (j > 1) {
                dp[j - 1][k] = min(dp[j - 1][k], s[j - 2] + dp[j][k]);
            }
            if (k < n) {
                dp[j][k + 1] = min(dp[j][k + 1], dp[j][k] + s[k]);
            }
            if (j > 1 && k < n && s[j - 2] == s[k]) {
                dp[j - 1][k + 1] = min(dp[j - 1][k + 1], dp[j][k]);
            }
        }
    }
    cout << dp[1][n] << endl;
    return 0;
}
