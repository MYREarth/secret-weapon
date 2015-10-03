#include<queue>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int n, m;

const int N = 100005, M = 200005 << 1, MOD = 1000000007;

int top, head[N], to[M], next[M];

void addedge(int u, int v) {
    to[top] = v, next[top] = head[u], head[u] = top++;
}

int dgr[N];
bool use[N];

priority_queue<pair<int, int> > heap;


int main() {
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        --u, --v;
        addedge(u, v), addedge(v, u);
        ++dgr[u], ++dgr[v];
    }
    for (int i = 0; i < n; ++i) {
        use[i] = true;
        heap.push(make_pair(dgr[i], i));
    }
    int cnt = 0, ans = 1;
    while (heap.size()) {
        int d = heap.top().first, u = heap.top().second;
        heap.pop();
        if (!use[u] || d != dgr[u]) {
            continue;
        }
        int size = 1;
        bool clique = true;
        for (int j = head[u]; ~j; j = next[j]) {
            int v = to[j];
            if (use[v]) {
                ++size;
                clique &= dgr[v] == dgr[u];
            }
        }
        if (clique) {
            ++cnt;
            ans = (long long)ans * size % MOD;
            for (int j = head[u]; ~j; j = next[j]) {
                use[to[j]] = false;
            }
            use[u] = false;
        } else {
            use[u] = false;
            for (int j = head[u]; ~j; j = next[j]) {
                int v = to[j];
                if (use[v]) {
                    heap.push(make_pair(--dgr[v], v));
                }
            }
        }
    }
    printf("%d\n%d\n", cnt, ans);
    return 0;
}
