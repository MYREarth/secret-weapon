#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int n;
vector<int> ans, stack;

void go(int last) {
    for (int i = 0; i < (int)stack.size() - 1; ++i) {
        int u = stack[i];
        ans.push_back(u);
        ans.push_back(u);
    }
    for (int j = last + 1; j <= n; ++j) {
        stack.push_back(j);
        ans.push_back(j);
        go(j);
        ans.push_back(j);
        stack.pop_back();
    }
}

bool vis[1 << 18][18];

int main() {
    scanf("%d", &n);
    go(0);
    printf("%d\n", (int)ans.size());
    if (ans.size() != (n << n)) {
        while (true) {
            continue;
        }
    }
    for (int i = 0; i < (int)ans.size(); ++i) {
        printf("%d%c", ans[i], i == (int)ans.size() - 1 ? '\n' : ' ');
    }
    int cur = 0, st = 0;
    for (int i = 0; i < (int)ans.size(); ++i) {
        int u = ans[i] - 1;
        cur = u, st ^= 1 << u;
        if (vis[st][cur]) {
            while(true) {
                continue;
            }
        }
        vis[st][cur] = true;
    }
    return 0;
}
