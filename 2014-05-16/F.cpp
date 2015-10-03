#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 1000;
int n, m;
vector<pair<int, int> > ans[N][N], ord;

int main() {
    freopen("condoms.in", "r", stdin);
    freopen("condoms.out", "w", stdout);
    scanf("%d", &n);
    m = n * 3 / 2;
    int d = m - n;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < d; ++j) {
            ord.push_back(make_pair(i, j));
            ans[i][j].push_back(make_pair(i, 0));
            ans[i][j].push_back(make_pair(n + j, 0));
        }
    }
    if (n % 2 == 1) {
        for (int i = 0; i < n; ++i) {
            ord.push_back(make_pair(i, n - 1));
            ans[i][n - 1].push_back(make_pair(i, 0));
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < d; ++j) {
            ord.push_back(make_pair(i, d + j));
            ans[i][d + j].push_back(make_pair(i, 0));
            ans[i][d + j].push_back(make_pair(n + j, 1));
        }
    }
    for (int _ = 0; _ < n * n; ++_) {
        int i = ord[_].first, j = ord[_].second;
        printf("%d %d %d", i + 1, j + 1, (int)ans[i][j].size());
        for (int k = 0; k < (int)ans[i][j].size(); ++k) {
            printf(" %d %d", ans[i][j][k].first + 1, ans[i][j][k].second);
        }
        printf("\n");
    }
    return 0;
}
