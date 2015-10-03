#include<queue>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

#define next NEXT

int n, m;
const int N = 305 * 2, M = N * N;
int top, head[N], to[M], next[M], cap[M], len[M];

void addedge(int u, int v, int c1, int l1) {
    int c2 = 0, l2 = -l1;
    to[top] = v, next[top] = head[u], cap[top] = c1, len[top] = l1, head[u] = top++;
    to[top] = u, next[top] = head[v], cap[top] = c2, len[top] = l2, head[v] = top++;
}

int nn, source, target, ssource, starget;
long long fa[N], p[N], mark[N];

const long long INF = 1ll << 60;

bool go(long long &cost) {
    for (int i = 0; i < nn; ++i) {
        fa[i] = -1;
        mark[i] = INF;
    }
    mark[ssource] = 0;
    priority_queue<pair<int, int> > heap;
    heap.push(make_pair(-mark[ssource], ssource));
    while (heap.size()) {
        int dd = -heap.top().first, u = heap.top().second;
        heap.pop();
        if (dd != mark[u]) {
            continue;
        }
        for (int j = head[u]; ~j; j = next[j]) {
            int v = to[j];
            if (cap[j] && mark[v] > mark[u] + p[u] - p[v] + len[j]) {
                fa[v] = j;
                mark[v] = mark[u] + p[u] - p[v] + len[j];
                heap.push(make_pair(-mark[v], v));
            }
        }
    }
    if (mark[starget] == INF) {
        return false;
    }
    cost = 0;
    int q = starget;
    while (q != ssource) {
        cost += len[fa[q]];
        --cap[fa[q]];
        ++cap[fa[q] ^ 1];
        q = to[fa[q] ^ 1];
    }
    for (int i = 0; i < nn; ++i) {
        if (mark[i] == INF) {
            p[i] = INF;
        } else {
            p[i] += mark[i];
        }
    }
    return true;
}

long long flow() {
    long long ret = 0, cost;
    while (go(cost)) {
        ret += cost;
    }
    return ret;
}

bool in[N], out[N];

int main() {
    memset(head, -1, sizeof(head));
    freopen("kingandroads.in", "r", stdin);
    freopen("kingandroads.out", "w", stdout);
    scanf("%d%d", &n, &m);
    source = n * 2, target = source + 1;
    for (int i = 0; i < m; ++i) {
        int u, v, l;
        scanf("%d%d%d", &u, &v, &l);
        --u, --v;
        addedge(u, v + n, 1, l);
        out[v] = true, in[u] = true;
    }
    for (int i = 0; i < n; ++i) {
        if (!in[i] || !out[i]) {
            printf("NIE\n");
            return 0;
        }
    }
    ssource = target + 1, starget = ssource + 1;
    for (int i = 0; i < n; ++i) {
        addedge(ssource, i, 1, 0);
        addedge(source, starget, 1, 0);
        addedge(source, i, m, 0);
    }
    for (int i = 0; i < n; ++i) {
        addedge(ssource, target, 1, 0);
        addedge(i + n, starget, 1, 0);
        addedge(i + n, target, m, 0);
    }
    addedge(target, source, m, 0);
    nn = starget + 1;
    cout << flow() << endl;
    return 0;
}
