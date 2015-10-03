#include<queue>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n, f, b;
        scanf("%d%d%d", &n, &f, &b);
        int ans = 0;
        priority_queue<int> heap;
        for (int i = 0; i < n; ++i) {
            int p, s;
            scanf("%d%d", &p, &s);
            if (s == 0) {
                heap.push(-(p + f));
            } else {
                ans = max(ans, f - p);
                heap.push(-(f - p + f * 2));
            }
        }
        for (int i = 0; i < b; ++i) {
            int u = -heap.top();
            heap.pop();
            ans = max(ans, u);
            heap.push(-(u + f * 2));
        }
        printf("%d\n", ans);
    }
    return 0;
}
