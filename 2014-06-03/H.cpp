#include<queue>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 1000005;

int n;

char s[N];

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%s", s);
        n = strlen(s);
        int mins[2], c[2];
        mins[0] = mins[1] = c[0] = c[1] = 0;
        for (int i = 0; i < n; ++i) {
            int u = s[i] - '0';
            --c[u], ++c[u ^ 1];
            mins[0] = min(mins[0], c[0]);
            mins[1] = min(mins[1], c[1]);
        }
        int ans1 = -mins[0] + -mins[1];
        priority_queue<int> heap[2];
        for (int i = 0; i < -mins[0]; ++i) {
            heap[0].push(0);
        }
        for (int i = 0; i < -mins[1]; ++i) {
            heap[1].push(0);
        }
        for (int i = 0; i < n; ++i) {
            int u = s[i] - '0';
            int t = heap[u].top();
            heap[u].pop();
            heap[u ^ 1].push(--t);
        }
        int ans2 = 0;
        for (int i = 0; i < 2; ++i) {
            while (heap[i].size()) {
                ans2 = max(ans2, -heap[i].top());
                heap[i].pop();
            }
        }
        printf("%d %d\n", ans1, ans2);
    }
    return 0;
}
