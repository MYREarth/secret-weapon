#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int n;

vector<pair<int, int> > ans;

int main() {
    freopen("comparator.in", "r", stdin);
    freopen("comparator.out", "w", stdout);
    while (scanf("%d", &n) == 1 && n) {
        ans.clear();
        vector<int> zero, one;
        for (int i = 0; i < n; ++i) {
            int a;
            scanf("%d", &a);
            if (a) {
                one.push_back(i);
            } else {
                zero.push_back(i);
            }
        }
        if (one.size() == 0 || zero.size() == 0 || zero.back() < one.front()) {
            printf("-1\n");
            continue;
        }
        for (int i = 0; i < (int)zero.size() - 1; ++i) {
            ans.push_back(make_pair(zero[i], zero.back()));
        }
        for (int i = 1; i < (int)one.size(); ++i) {
            ans.push_back(make_pair(one.front(), one[i]));
        }
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (i == one.front() || i == zero.back() || j == one.front() || j == zero.back()) {
                    continue;
                }
                ans.push_back(make_pair(i, j));
            }
        }
        for (int i = 0; i < (int)zero.size(); ++i) {
            if (i != one.front()) {
                ans.push_back(make_pair(i, zero.back()));
            }
        }
        for (int i = n - 1; i >= (int)zero.size(); --i) {
            if (i != zero.back()) {
                ans.push_back(make_pair(one.front(), i));
            }
        }
        for (int i = 0; i < (int)zero.size(); ++i) {
            for (int j = i + 1; j < (int)zero.size(); ++j) {
                ans.push_back(make_pair(i, j));
            }
        }
        for (int i = 0; i < (int)one.size(); ++i) {
            for (int j = i + 1; j < (int)one.size(); ++j) {
                ans.push_back(make_pair(i + zero.size(), j + zero.size()));
            }
        }
        printf("%d\n", (int)ans.size());
        for (int i = 0; i < (int)ans.size(); ++i) {
            printf("%d %d\n", ans[i].first + 1, ans[i].second + 1);
        }
        /*
        int cnt = 0;
        for (int st = 0; st < (1 << n); ++st) {
            int b[10];
            for (int j = 0; j < n; ++j) {
                b[n - 1 - j] = st >> j & 1;
            }
            for (int k = 0; k < (int)ans.size(); ++k) {
                int u = ans[k].first, v = ans[k].second;
                if (u >= v) {
                    printf("ERROR!!!\n");
                }
                if (b[u] > b[v]) {
                    swap(b[u], b[v]);
                }
            }
            bool flag = false;
            for (int j = 0; j + 1 < n; ++j) {
                flag = flag || b[j] > b[j + 1];
            }
            if (flag) {
                    for (int j = 0; j < n; ++j) {
                        printf("%d", st >> (n - j - 1) & 1);
                    }
                    printf(" --> ");
                    for (int j = 0; j < n; ++j) {
                        printf("%d", b[j]);
                    }
                    printf("\n");
                ++cnt;
            }
        }
        if (cnt != 1) {
            if (cnt > 100) {
                printf("WRONG!!!\n");
            }
            printf("ERROR!!!\n");
        }
        }
        */
    }
    return 0;
}
