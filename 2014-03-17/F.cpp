#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int n, k, p;

int main() {
    scanf("%d%d%d", &n, &k, &p);
    vector<int> ans(n);
    for (int i = 0; i < (n - k); ++i) {
        ans[i] = 1;
    }
    int cur = n - k, cursize = 2;
    for (int i = n - k; i < n; ++i) {
        while (cur * 100 < i * p) {
            ++cursize;
            while (cur < i && ans[cur] <= cursize) {
                ++cur;
            }
        }
        ans[i] = cursize;
    }
    long long sum = 0;
    for (int i = 0; i < (int)ans.size(); ++i) {
        sum += ans[i];
    }
    cout << sum << endl;
    for (int i = 0; i < n; ++i) {
        printf("%d%c", ans[i], i == n - 1 ? '\n' : ' ');
    }
    return 0;
}
