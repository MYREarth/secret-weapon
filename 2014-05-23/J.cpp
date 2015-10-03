#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 200005;

int n, k;

unsigned dp[N];

int top, p[N];

int main() {
    //freopen("squary.in", "r", stdin);
    //freopen("squary.out", "w", stdout);
    scanf("%d%d", &n, &k);
    for (int i = 1; i * i < n; ++i) {
        p[top++] = n - i * i;
    }
    dp[0] = 1;
    for (int i = 0; i < n; ++i) {
        for (int j = top - 1; j >= 0 && i + p[j] <= n; --j) {
            dp[i + p[j]] |= dp[i] << 1;
        }
    }
    if (dp[n] >> k & 1) {
        printf("YES\n");
    } else {
        printf("NO\n");
        return 0;
    }
    int cur = n, left = k, j = top - 1;
    vector<int> ans;
    while (cur) {
        while (cur - p[j] < 0 || (~dp[cur - p[j]] >> left - 1 & 1)) {
            --j;
        }
        ans.push_back(p[j]);
        cur -= p[j];
        --left;
    }
    sort(ans.begin(), ans.end());
    for (int i = 0; i < (int)ans.size(); ++i) {
        printf("%d%c", ans[i], i == (int)ans.size() - 1 ? '\n' : ' ');
    }
    return 0;
}
