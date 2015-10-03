#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int main() {
    freopen("cash.in", "r", stdin);
    freopen("cash.out", "w", stdout);
    int sum, n;
    scanf("%d%d", &sum, &n);
    vector<int> ans(n);
    for (int i = 0; i < n; ++i) {
        if (sum >= 50) {
            sum -= 50;
            ans[i] += 50;
        }
    }
    for (int i = 0; i < n; ++i) {
        if (sum >= 400) {
            sum -= 400;
            ans[i] += 400;
        } else {
            ans[i] += sum;
            sum = 0;
        }
    }
    ans[0] += sum;
    while (ans.size() && ans.back() == 0) {
        ans.pop_back();
    }
    printf("%d\n", ans.size());
    for (int i = 0; i < (int)ans.size(); ++i) {
        printf("%d%c", ans[i], i == (int)ans.size() - 1 ? '\n' : ' ');
    }
    return 0;
}
