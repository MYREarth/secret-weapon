#include <cassert>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

const int N = 100000;

int n, first_edge[N], to[N << 1], next_edge[N << 1], weight[N << 1];

void add_edge(int u, int v, int w) {
    static int count = 0;
    to[count] = v;
    weight[count] = w;
    next_edge[count] = first_edge[u];
    first_edge[u] = count ++;
}

struct Node;

Node *null;

struct Node {
    Node(int count, Node *left, Node *right) : count(count), left(left), right(right) {}

    Node* insert(int l, int r, int k) {
        if (k < l || r <= k) {
            return this;
        }
        if (l + 1 == r) {
            return new Node(count + 1, null, null);
        }
        int m = l + r >> 1;
        return new Node(count + 1, left->insert(l, m, k), right->insert(m, r, k));
    }

    int  count;
    Node *left, *right;
};

const int D = 20;

int depth[N], jump[N][D], rank[N];
Node* trees[N];
std::vector <int> values;

void prepare(int p, int u) {
    static int count = 0;
    depth[u] = ~p ? depth[p] + 1 : 0;
    rank[u] = count ++;
    jump[u][0] = p;
    for (int i = 0; ~jump[u][i]; ++ i) {
        jump[u][i + 1] = jump[jump[u][i]][i];
    }
    for (int iterator = first_edge[u]; ~iterator; iterator = next_edge[iterator]) {
        int v = to[iterator];
        if (v != p) {
            int id = std::lower_bound(values.begin(), values.end(), weight[iterator]) - values.begin();
            trees[v] = trees[u]->insert(0, (int)values.size(), id);
            prepare(u, v);
        }
    }
}

int get_lca(int a, int b) {
    if (depth[a] > depth[b]) {
        std::swap(a, b);
    }
    for (int i = 0; i < D; ++ i) {
        if (depth[b] - depth[a] >> i & 1) {
            b = jump[b][i];
        }
    }
    if (a == b) {
        return a;
    }
    for (int i = D - 1; i >= 0; -- i) {
        if (jump[a][i] != jump[b][i]) {
            a = jump[a][i];
            b = jump[b][i];
        }
    }
    return jump[a][0];
}

bool by_rank(int u, int v) {
    return rank[u] < rank[v];
}

int main() {
    null = new Node(0, NULL, NULL);
    null->left = null->right = null;
    scanf("%d", &n);
    memset(first_edge, -1, sizeof(first_edge));
    for (int i = 0; i < n - 1; ++ i) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        a --;
        b --;
        add_edge(a, b, c);
        add_edge(b, a, c);
        values.push_back(c);
    }
    std::sort(values.begin(), values.end());
    values.erase(std::unique(values.begin(), values.end()), values.end());
    memset(jump, -1, sizeof(jump));
    trees[0] = null;
    prepare(-1, 0);
    int q;
    scanf("%d", &q);
    while (q --) {
        std::vector <int> vertices;
        while (true) {
            vertices.push_back(0);
            scanf("%d", &vertices.back());
            vertices.back() --;
            if (vertices.back() == -1) {
                break;
            }
        }
        vertices.pop_back();
        std::sort(vertices.begin(), vertices.end(), by_rank);
        int m = vertices.size();
        std::vector <std::pair <Node*, int>> parts;
        int all = 0;
        for (int i = 0; i < m; ++ i) {
            int a = vertices[i];
            int b = vertices[(i + 1) % m];
            parts.push_back(std::make_pair(trees[a], 1));
            parts.push_back(std::make_pair(trees[b], 1));
            parts.push_back(std::make_pair(trees[get_lca(a, b)], -2));
            all += depth[a] + depth[b] - 2 * depth[get_lca(a, b)];
        }
        assert(all % 2 == 0);
        all /= 2;
        int l = 0;
        int r = (int)values.size();
        int need;
        scanf("%d", &need); // 1-based
        if (need <= all) {
            while (r - l > 1) {
                int m = l + r >> 1;
                int count = 0;
                for (auto &iterator : parts) {
                    count += iterator.first->left->count * iterator.second;
                }
                assert(count % 2 == 0);
                count /= 2;
                if (count >= need) {
                    for (auto &iterator : parts) {
                        iterator.first = iterator.first->left;
                    }
                    r = m;
                } else {
                    need -= count;
                    for (auto &iterator : parts) {
                        iterator.first = iterator.first->right;
                    }
                    l = m;
                }
            }
            printf("%d\n", values[l]);
        } else {
            puts("-1");
        }
    }
    return 0;
}
