#include<queue>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 5000005;

int a[N], ord[N];

bool by_a(int i, int j) {
    return a[i] < a[j];
}

int fa[N], size[N];

int find(int u) {
    return u == fa[u] ? u : fa[u] = find(fa[u]);
}

int block;

void merge(int u, int v) {
    --block;
    fa[v] = u, size[u] += size[v];
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; ++i) {
            scanf("%d", a + i);
            ord[i] = i;
        }
        sort(ord, ord + n, by_a);
        for (int i = 0; i < n; ++i) {
            fa[i] = i, size[i] = 1;
        }
        int ans = a[ord[0]], cur = a[ord[0]], p = 0;
        block = n;
        queue<int> q;
        while (block > 1 || size[find(0)] > 1) {
            while (p < n && a[ord[p]] == cur) {
                int u = ord[p];
                if (u > 0 && a[u - 1] <= cur) {
                    if (find(u) != find(u - 1)) {
                        merge(find(u), find(u - 1));
                    }
                }
                if (u + 1 < n && a[u + 1] <= cur) {
                    if (find(u) != find(u + 1)) {
                        merge(find(u), find(u + 1));
                    }
                }
                if (size[find(u)] > 1 && u == find(u)) {
                    q.push(u);
                }
                ++p;
            }
            ++cur, ++ans;
            queue<int> nq;
            while (q.size()) {
                int u = q.front();
                q.pop();
                if (u != find(u)) {
                    continue;
                }
                size[u] = (size[u] + 1) >> 1;
                if (size[u] > 1) {
                    nq.push(u);
                }
            }
            q = nq;
        }
        printf("%d\n", ans);
    }
    return 0;
}
