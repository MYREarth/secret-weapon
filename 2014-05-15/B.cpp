#include<map>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

#define next __NEXT

const int N = 750000, M = N << 1;

int n, k;
int top, head[N], to[M], next[M];

void addedge(int u, int v) {
    to[top] = v, next[top] = head[u], head[u] = top++;
}

long long cal;

void merge(map<int, int> *a, map<int, int> *b, int dep) {
    for (map<int, int> :: iterator it = (*a).begin(); it != (*a).end(); ++it) {
        int d = (k - (it->first - dep)) + dep;
        if ((*b).count(d)) {
            cal += (long long)it->second * (*b)[d];
        }
    }
    for (map<int, int> :: iterator it = (*a).begin(); it != (*a).end(); ++it) {
        (*b)[it->first] += it->second;
    }
}

map<int, int> *mem[N];
int fa[N], dep[N];

int main() {
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        --u, --v;
        addedge(u, v);
        addedge(v, u);
    }
    vector<int> q;
    q.push_back(0);
    fa[0] = -1;
    for (int i = 0; i < n; ++i) {
        int u = q[i];
        for (int j = head[u]; ~j; j = next[j]) {
            int v = to[j];
            if (v != fa[u]) {
                fa[v] = u;
                dep[v] = dep[u] + 1;
                q.push_back(v);
            }
        }
    }
    for (int i = n - 1; i >= 0; --i) {
        int u = q[i];
        mem[u] = new map<int, int>;
        (*mem[u])[dep[u]] = 1;
        for (int j = head[u]; ~j; j = next[j]) {
            int v = to[j];
            if (v == fa[u]) {
                continue;
            }
            if (mem[u]->size() < mem[v]->size()) {
                swap(mem[u], mem[v]);
            }
            merge(mem[v], mem[u], dep[u]);
        }
    }
    printf("%lld\n", cal);
    return 0;
}
