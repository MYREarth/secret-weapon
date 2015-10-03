#include <algorithm>
#include <cstdio>
#include <cstring>
#include <climits>
#include <vector>

const int N = 50000;

int n, color[N];
std::vector <int> tree[N];

bool selected[N];

int size[N], balance[N];
std::vector <int> nodes;

void prepare(int p, int u) {
    size[u] = 1;
    balance[u] = 0;
    nodes.push_back(u);
    for (auto &v : tree[u]) {
        if (v != p && !selected[v]) {
            prepare(u, v);
            size[u] += size[v];
            balance[u] = std::max(balance[u], size[v]);
        }
    }
}

int root, depth[N];

typedef long long Long;

int info_count = 0;

struct Info {
    int node, depth, id;

    Info(int node, int depth) : node(node), depth(depth), id(++ info_count) {}
};

// <node, depth>
std::vector <Info> ancestors[N];

void search(int p, int u) {
    depth[u] = ~p ? depth[p] + 1 : 0;
    ancestors[u].push_back(Info(::root, depth[u]));
    for (int &v : tree[u]) {
        if (v != p && !selected[v]) {
            search(u, v);
        }
    }
}

const int M = N * 20 + 1;

std::pair <int, int> key[M];
int weight[M], children[M][2];
Long self[M], subtree[M];

void update(int &x) {
    subtree[x] = subtree[children[x][0]] | self[x] | subtree[children[x][1]];
}

void rotate(int &x, int t) {
    int y = children[x][t];
    children[x][t] = children[y][1 ^ t];
    children[y][1 ^ t] = x;
    update(x);
    update(y);
    x = y;
}

void insert(int &x, std::pair <int, int> &k, int id, int c) {
    if (x) {
        int t = key[x] < k;
        insert(children[x][t], k, id, c);
        if (weight[children[x][t]] < weight[x]) {
            rotate(x, t);
        }
    } else {
        x = id;
        key[x] = k;
        weight[x] = rand();
        children[x][0] = children[x][1] = 0;
        self[x] = 1LL << c;
    }
    update(x);
}

void erase(int &x, std::pair <int, int> &k) {
    if (x) {
        if (key[x] != k) {
            erase(children[x][key[x] < k], k);
        } else {
            if (children[x][0] || children[x][1]) {
                rotate(x, weight[children[x][0]] > weight[children[x][1]]);
                erase(x, k);
            } else {
                x = 0;
                return;
            }
        }
        update(x);
    }
}

Long query(int &x, int d) {
    if (x) {
        if (key[x].first > d) {
            return query(children[x][0], d);
        }
        return subtree[children[x][0]] | self[x] | query(children[x][1], d);
    }
    return 0;
}

void divide(int root) {
    nodes.clear();
    prepare(-1, root);
    std::pair <int, int> new_root(balance[root], root);
    for (int &node : nodes) {
        new_root = std::min(new_root, std::make_pair(std::max(balance[node], size[root] - size[node]), node));
    }
    root = new_root.second;
    selected[root] = true;
    ::root = root;
    search(-1, root);
    for (auto &v : tree[root]) {
        if (!selected[v]) {
            divide(v);
        }
    }
}

int roots[N];

void update_node(int u, int c) {
    for (auto &info : ancestors[u]) {
        std::pair <int, int> k(info.depth, u);
        erase(roots[info.node], k);
        insert(roots[info.node], k, info.id, c);
    }
    color[u] = c;
}

int main() {
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
    subtree[0] = 0;
    weight[0] = INT_MAX;
    scanf("%d%*d%*d", &n);
    for (int i = 0; i < n; ++ i) {
        scanf("%d", color + i);
        color[i] --;
    }
    for (int i = 0; i < n - 1; ++ i) {
        int a, b;
        scanf("%d%d", &a, &b);
        a --, b--;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }
    memset(selected, 0, sizeof(selected));
    divide(0);
    memset(roots, 0, sizeof(roots));
    for (int i = 0; i < n; ++ i) {
        update_node(i, color[i]);
    }
    int q;
    scanf("%d", &q);
    while (q --) {
        int type, v;
        scanf("%d%d", &type, &v);
        v --;
        if (type == 1) {
            int new_color;
            scanf("%d", &new_color);
            new_color --;
            update_node(v, new_color);
        } else {
            int r;
            scanf("%d", &r);
            Long result = 0;
            for (auto &info : ancestors[v]) {
                if (info.depth <= r) {
                    result |= query(roots[info.node], r - info.depth);
                }
            }
            printf("%d\n", __builtin_popcountll(result));
        }
    }
    return 0;
}
