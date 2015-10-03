#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 10005;

int n, a[N];

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        vector<pair<int, int> > ans;
        scanf("%d", &n);
        for (int i = 0; i < n; ++i) {
            scanf("%d", a + i);
        }
        for (int i = n; i > 1; --i) {
            int pos = -1;
            for (int j = 0; j < i; ++j) {
                if (a[j] == i) {
                    pos = j;
                    break;
                }
            }
            if (pos == i - 1) {
                continue;
            }
            while (pos != i - 1) {
                int left = pos + 1, right = i - 1 - pos, len = min(left, right);
                ans.push_back(make_pair(pos - len + 1, pos + len));
                for (int j = 0; j < len; ++j) {
                    swap(a[pos - j], a[pos + len - j]);
                }
                pos += len;
            }
        }
        printf("%d\n", (int)ans.size());
        for (int i = 0; i < (int)ans.size(); ++i) {
            printf("%d %d\n", ans[i].first + 1, ans[i].second + 1);
        }
    }
    return 0;
}
