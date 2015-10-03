#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int n;

int main() {
    //freopen("art.in", "r", stdin);
    //freopen("art.out", "w", stdout);
    int m;
    scanf("%d", &m);
    for (int n = 1; n <= m; ++n) {
    vector<int> ans;
    for (int i = n; i >= 1; --i) {
        bool check = true;
        for (int j = 0; j < (int)ans.size(); ++j) {
            for (int k = j + 1; k < (int)ans.size(); ++k) {
                if (2 * (ans[k] - i) == ans[j] - ans[k]) {
                    check = false;
                }
            }
        }
        if (check) {
            ans.push_back(i);
        }
    }
    sort(ans.begin(), ans.end());
    printf("%d %d\n", n, (int)ans.size());
    for (int i = 0; i < (int)ans.size(); ++i) {
        printf("%d%c", ans[i], i == (int)ans.size() - 1 ? '\n' : ' ');
    }
    }
    return 0;
}
