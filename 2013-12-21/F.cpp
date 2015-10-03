#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int main() {
    freopen("foss.in", "r", stdin);
    freopen("foss.out", "w", stdout);
    int t;
    scanf("%d", &t);
    while (t--) {
        int n;
        scanf("%d", &n);
        vector<pair<int, int> > ans;
        if (n == 3) {
            printf("1\n");
            ans.push_back(make_pair(0, 0));
            ans.push_back(make_pair(10000, 0));
            ans.push_back(make_pair(10000, 10000));
        } else if (n % 4 == 3) {
            printf("%d\n", 5 + (n - 7) / 4 * 2); 
            int t = (n - 7) / 4;
            ans.push_back(make_pair(0, 0));
            for (int i = 0; i < t; ++i) {
                ans.push_back(make_pair((i + 1) * 2, 0));
                ans.push_back(make_pair((i + 1) * 2, 1));
                ans.push_back(make_pair((i + 1) * 2 + 1, 1));
                ans.push_back(make_pair((i + 1) * 2 + 1, 0));
            }
            ans.push_back(make_pair(10000, 0));
            ans.push_back(make_pair(10000, 9999));
            ans.push_back(make_pair(9999, 9999));
            ans.push_back(make_pair(9998, 10000));
            ans.push_back(make_pair(9997, 9999));
            ans.push_back(make_pair(0, 9999));
        } else if (n % 4 == 0) {
            printf("%d\n", 4 + (n - 4) / 4 * 2);
            int t = (n - 4) / 4;
            ans.push_back(make_pair(0, 0));
            ans.push_back(make_pair(1, 0));
            for (int i = 0; i < t; ++i) {
                ans.push_back(make_pair(1, (i + 1) * 2));
                ans.push_back(make_pair(2, (i + 1) * 2));
                ans.push_back(make_pair(2, (i + 1) * 2 + 1));
                ans.push_back(make_pair(1, (i + 1) * 2 + 1));
            }
            ans.push_back(make_pair(1, 10000));
            ans.push_back(make_pair(0, 10000));
        } else if (n == 5) {
            printf("%d\n", 3 + (n - 5) / 4 * 2);
            int t = (n - 5) / 4;
            ans.push_back(make_pair(0, 0));
            for (int i = 0; i < t; ++i) {
                ans.push_back(make_pair((i + 1) * 2, 0));
                ans.push_back(make_pair((i + 1) * 2, 1));
                ans.push_back(make_pair((i + 1) * 2 + 1, 1));
                ans.push_back(make_pair((i + 1) * 2 + 1, 0));
            }
            ans.push_back(make_pair(9999, 0));
            ans.push_back(make_pair(10000, 1));
            ans.push_back(make_pair(10000, 10000));
            ans.push_back(make_pair(0, 10000));
        } else if (n % 4 == 1) {
            printf("%d\n", 6 + (n - 9) / 4 * 2);
            int t = (n - 9) / 4;
            ans.push_back(make_pair(0, 0));
            for (int i = 0; i < t; ++i) {
                ans.push_back(make_pair((i + 1) * 2, 0));
                ans.push_back(make_pair((i + 1) * 2, 1));
                ans.push_back(make_pair((i + 1) * 2 + 1, 1));
                ans.push_back(make_pair((i + 1) * 2 + 1, 0));
            }
            ans.push_back(make_pair(9999, 0));
            ans.push_back(make_pair(9999, 1));
            ans.push_back(make_pair(10000, 1));
            ans.push_back(make_pair(10000, 9999));
            ans.push_back(make_pair(9999, 9999));
            ans.push_back(make_pair(9998, 10000));
            ans.push_back(make_pair(9997, 9999));
            ans.push_back(make_pair(0, 9999));
        } else if (n % 4 == 2) {
            printf("%d\n", 5 + (n - 6) / 4 * 2);
            int t = (n - 6) / 4;
            ans.push_back(make_pair(0, 0));
            ans.push_back(make_pair(1, 0));
            for (int i = 0; i < t; ++i) {
                ans.push_back(make_pair(1, (i + 1) * 2));
                ans.push_back(make_pair(2, (i + 1) * 2));
                ans.push_back(make_pair(2, (i + 1) * 2 + 1));
                ans.push_back(make_pair(1, (i + 1) * 2 + 1));
            }
            ans.push_back(make_pair(1, 9999));
            ans.push_back(make_pair(2, 9999));
            ans.push_back(make_pair(2, 10000));
            ans.push_back(make_pair(0, 10000));
        }
        for (int i = 0; i < (int)ans.size(); ++i) {
            printf("%d %d\n", ans[i].first, ans[i].second);
        }
    }
    return 0;
}
