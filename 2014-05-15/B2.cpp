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

int dep;

void merge(map<int, int> &a, map<int, int> &b) {
    for (map<int, int> :: iterator it = a.begin(); it != a.end(); ++it) {
        int d = (k - (it->first - dep)) + dep;
        if (b.count(d)) {
            cal += (long long)it->second * b[d];
        }
    }
    for (map<int, int> :: iterator it = a.begin(); it != a.end(); ++it) {
        b[it->first] += it->second;
    }
}

map<int, int> go(int u, int fa) {
    map<int, int> ret;
    ++dep;
    ret[dep] = 1;
    for (int j = head[u]; ~j; j = next[j]) {
        int v = to[j];
        if (v == fa) {
            continue;
        }
        map<int, int> tmp = go(v, u);
        if (tmp.size() > ret.size()) {
            merge(ret, tmp);
            ret = tmp;
        } else {
            merge(tmp, ret);
        }
    }
    --dep;
    return ret;
}

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
    go(0, -1);
    printf("%lld\n", cal);
    return 0;
}
