#include <cassert>
#include <cstdio>
#include <cstring>

const int N = 100001;

int n, type[N], parent[N], real_parent[N], children[N][2];

void rotate(int x) {
    int t = type[x];
    int y = parent[x];
    int z = children[x][1 ^ t];
    type[x] = type[y];
    parent[x] = parent[y];
    if (type[x] != 2) {
        children[parent[x]][type[x]] = x;
    }
    type[y] = 1 ^ t;
    parent[y] = x;
    children[x][1 ^ t] = y;
    if (z) {
        type[z] = t;
        parent[z] = y;
    }
    children[y][t] = z;
}

void splay(int x) {
    while (type[x] != 2) {
        int y = parent[x];
        if (type[x] == type[y]) {
            rotate(y);
        } else {
            rotate(x);
        }
        if (type[x] == 2) {
            break;
        }
        rotate(x);
    }
}

void access(int x) {
    int z = 0;
    while (x) {
        splay(x);
        type[children[x][1]] = 2;
        children[x][1] = z;
        type[z] = 1;
        z = x;
        x = parent[x];
    }
}

int main() {
    freopen("lca.in", "r", stdin);
    freopen("lca.out", "w", stdout);
    scanf("%d", &n);
    memset(children, 0, sizeof(children));
    type[1] = 2;
    for (int i = 2; i <= n; ++ i) {
        scanf("%d", parent + i);
        real_parent[i] = parent[i];
        type[i] = 2;
    }
    int q;
    scanf("%d", &q);
    while (q --) {
        char buffer[2];
        int u, v;
        scanf("%s%d%d", buffer, &u, &v);
        if (*buffer == 'C') {
            if (u != 1) {
                access(u);
                access(real_parent[u]);
                assert(type[u] == 2);
                real_parent[u] = parent[u] = v;
            }
        } else {
            access(u);
            int z = 0;
            while (v) {
                splay(v);
                if (!parent[v]) {
                    printf("%d\n", v);
                }
                type[children[v][1]] = 2;
                children[v][1] = z;
                type[z] = 1;
                z = v;
                v = parent[v];
            }
        }
    }
    return 0;
}
