#include <algorithm>
#include <cstdio>
#include <cstring>
#include <climits>
#include <map>
#include <utility>
#include <vector>

typedef long long Long;
typedef std::pair <int, int> Pair;

const int N = 1000;

int first_edge[N], length[N], to[N << 1], next_edge[N << 1];

void add_edge(int u, int v) {
    static int edge_count = 0;
    to[edge_count] = v;
    next_edge[edge_count] = first_edge[u];
    first_edge[u] = edge_count ++;
}

bool marked[N];
int  size[N], balance[N], parent[N], depth[N];
std::vector <int> nodes;

void prepare(int p, int u) {
    nodes.push_back(u);
    size[u] = 1;
    depth[u] = ~p ? depth[p] + 1: 0;
    parent[u] = p;
    balance[u] = 0;
    for (int it = first_edge[u]; ~it; it = next_edge[it]) {
        int v = to[it];
        if (v != p && !marked[v]) {
            prepare(u, v);
            size[u] += size[v];
            balance[u] = std::max(balance[u], size[v]);
        }
    }
}

struct Info {
    int ancestor, depth, belong;

    Info(int ancestor, int depth, int belong) : ancestor(ancestor), depth(depth), belong(belong) {}
};

std::vector <Info> ancestors[N];

std::vector <Long> vertices[N], edges[N << 1];
std::map <int, int> depths[N];

int ancestor, belong;

int search(int p, int u) {
    int result = 0;
    depth[u] = ~p ? depth[p] + 1 : 0;
    depths[::ancestor][u] = depth[u];
    ancestors[u].push_back(Info(::ancestor, depth[u], ::belong));
    for (int it = first_edge[u]; ~it; it = next_edge[it]) {
        int v = to[it];
        if (!marked[v] && v != p) {
            result = std::max(result, search(u, v) + 1);
        }
    }
    return result;
}

void divide(int root) {
    nodes.clear();
    prepare(-1, root);
    Pair new_root(INT_MAX, -1);
    for (int &v: nodes) {
        new_root = std::min(new_root, Pair(std::max(balance[v], size[root] - size[v]), v));
    }
    root = new_root.second;
    marked[root] = true;
    depths[root][root] = 0;
    ancestors[root].push_back(Info(root, 0, -1));
    int max_depth = 0;
    depth[root] = 0;
    for (int it = first_edge[root]; ~it; it = next_edge[it]) {
        int v = to[it];
        if (!marked[v]) {
            ::belong = it;
            ::ancestor = root;
            int ret = search(root, v);
            edges[it].resize(ret + 1);
            max_depth = std::max(max_depth, ret);
            divide(v);
        }
    }
    vertices[root].resize(max_depth + 1);
}

void modify(std::vector <Long> &list, int k, int v) {
    for (; k < list.size(); k += ~k & k + 1) {
        list[k] += v;
    }
}

void _update_edge(int u, int v, int w) {
    // depth[u] < depth[v]
    for (Info &info : ancestors[v]) {
        int p = info.ancestor;
        auto iterator_u = depths[p].find(u);
        auto iterator_v = depths[p].find(v);
        if (iterator_u != depths[p].end() && iterator_u->second < iterator_v->second) {
printf("insert vertices %d %d %d\n", p, iterator_u->second, w);
            modify(vertices[p], iterator_u->second, w);
            modify(edges[info.belong], iterator_u->second, w);
        }
    }
}

Long query(std::vector <Long> &list, int k) {
    Long result = 0;
    for (; k >= 0; k -= ~k & k + 1) {
        result += list[k];
    }
    return result;
}

void update_edge(int u, int v, int w) {
    _update_edge(u, v, w);
    _update_edge(v, u, w);
}

int main() {
    int n, q;
    scanf("%d%d", &n, &q);
    memset(first_edge, -1, sizeof(first_edge));
    for (int i = 0; i < n - 1; ++ i) {
        int a, b;
        scanf("%d%d%d", &a, &b, length + i);
        a --;
        b --;
        add_edge(a, b);
        add_edge(b, a);
    }

    memset(marked, 0, sizeof(marked));
    divide(0);
    memset(marked, 0, sizeof(marked));
    prepare(-1, 0);

    for (int i = 0; i < n - 1; ++ i) {
        update_edge(to[i << 1], to[i << 1 | 1], length[i]);
    }

    while (q --) {
        int type, u, v;
        scanf("%d%d", &type, &u);
        u --;
        if (type == 1) {
            int w;
            scanf("%d%d", &v, &w);
            v --;
            while (u != v) {
                int &p = depth[u] > depth[v] ? u : v;
                update_edge(p, parent[p], w);
                p = parent[p];
            }
        } else {
            int radius;
            scanf("%d", &radius);
            Long result = 0;
            for (Info &info : ancestors[u]) {
                int p = info.ancestor;
                if (radius > info.depth) {
printf("%d %d\n", p, info.depth);
                    result += query(vertices[p], radius - info.depth - 1);
                    if (info.belong != -1) {
                        result -= query(edges[info.belong], radius - info.depth - 1);
                    }
                }
printf("!! %lld\n", result);
            }
puts("===");
            printf("%lld\n", result);
        }
    }
    return 0;
}
