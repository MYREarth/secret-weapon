#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <map>
#include <vector>

#define ALL(v) (v).begin(), (v).end()

const int N = 40000;

int n, m, type[N], a[N], b[N], result[N];

const int D = 20;

int parent[D][N];

int find(int* parent, int u) {
    if (parent[u] != u) {
        parent[u] = find(parent, parent[u]);
    }
    return parent[u];
}

bool merge(int* parent, int u, int v) {
    if (find(parent, u) == find(parent, v)) {
        return false;
    }
    parent[find(parent, u)] = find(parent, v);
    return true;
}

int when[N];
std::pair <int, int> NODES[D][N << 4];

void solve(int depth, int l, int r, std::vector <int> edges) {
    int total = 0;
    std::pair <int, int> *nodes = NODES[depth];
#define ADD(v) nodes[total ++] = std::make_pair(find(parent[depth - 1], (v)), (v))
    for (auto &e: edges) {
        ADD(a[e]);
        ADD(b[e]);
    }
    for (int i = l; i < r; ++ i) {
        ADD(a[i]);
        ADD(b[i]);
    }
#undef ADD
    std::sort(nodes, nodes + total);
    total = std::unique(nodes, nodes + total) - nodes;
    parent[depth][nodes[0].second] = nodes[0].second;
    for (int i = 1; i < total; ++ i) {
        parent[depth][nodes[i].second] = nodes[i - 1].first == nodes[i].first ? parent[depth][nodes[i - 1].second] : nodes[i].second;
    }
    if (l + 1 == r)
    {
        if (type[l]==3)
            result[l] = find(parent[depth], a[l]) == find(parent[depth], b[l]);
    }
    else
    {
        int m = l + r >> 1;
        std::vector <int> new_edges;
        for (int &e : edges) {
            if (when[e] >= m) {
                merge(parent[depth], a[e], b[e]);
            } else {
                new_edges.push_back(e);
            }
        }
        solve(depth+1,l,m,new_edges);
        new_edges.clear();
        parent[depth][nodes[0].second] = nodes[0].second;
        for (int i = 1; i < total; ++ i) {
            parent[depth][nodes[i].second] = nodes[i - 1].first == nodes[i].first ? parent[depth][nodes[i - 1].second] : nodes[i].second;
        }
        for (int &e : edges) {
            if (when[e] >= r) {
                merge(parent[depth], a[e], b[e]);
            } else if (when[e] >= m){
                new_edges.push_back(e);
            }
        }
        for (int i = l; i < m; ++ i) {
            if (type[i] == 1) {
                if (when[i] >= r) {
                    merge(parent[depth], a[i], b[i]);
                } else if (when[i] >= m) {
                    new_edges.push_back(i);
                }
            }
        }
        solve(depth+1,m,r,new_edges);
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++ i) {
        scanf("%d%d%d", type + i, a + i, b + i);
    }
    {
        std::map <std::pair <int, int>, int> map;
        for (int i = m - 1; i >= 0; -- i) {
            std::pair <int, int> e(a[i], b[i]);
            if (type[i] == 1) {
                when[i] = map.count(e) ? map[e] : m;
            }
            if (type[i] == 2) {
                map[e] = i;
            }
        }
    }
    for (int i = 0; i < n; ++ i) {
        parent[0][i] = i;
    }
    solve(1, 0, m, std::vector <int>());
    for (int i = 0; i < m; ++ i) {
        if (type[i] == 3) {
            puts(result[i] ? "YES" : "NO");
        }
    }
    return 0;
}
