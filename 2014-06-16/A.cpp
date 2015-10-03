#include<vector>
#include<cstdio>
#include<string>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 50005, BAR = 100000;
pair<string, int> s[N];
char buf[6];

#define next NEXT

int next[N][5];

int top;
pair<int, int> ans[BAR];

int n;

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%s", buf);
        s[i].first = buf, s[i].second = i + 1;
    }
    sort(s, s + n);
    for (int i = 0; i < 5; ++i) {
        next[n - 1][i] = n;
    }
    for (int i = n - 2; i >= 0; --i) {
        for (int j = 0; j < 5; ++j) {
            next[i][j] = s[i].first[j] == s[i + 1].first[j] ? next[i + 1][j] : i + 1;
        }
    }
    top = 0;
    for (int i = 0; i < n && top < BAR; ++i) {
        int cur = i;
        while (cur < n && top < BAR) {
            int maxs = cur;
            for (int j = 0; j < 5; ++j) {
                if (s[i].first[j] == s[cur].first[j]) {
                    maxs = max(maxs, next[cur][j]);
                }
            }
            if (maxs == cur) {
                ans[top++] = make_pair(s[i].second, s[cur].second);
                ++cur;
            } else {
                cur = maxs;
            }
        }
    }
    printf("%d\n", top);
    for (int i = 0; i < top; ++i) {
        printf("%d %d\n", ans[i].first, ans[i].second);
    }
    return 0;
}
