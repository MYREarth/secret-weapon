#include <cassert>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

const int N = 10000;

int n, m, colors, head[N], to[N << 2], next[N << 2], weight[N << 2];

void add_edge(int a, int b, int c) {
    static int edge_count = 0;
    to[edge_count] = b;
    next[edge_count] = head[a];
    weight[edge_count] = c;
    head[a] = edge_count ++;
}

int parent[N];

int find_root(int u) {
    if (~parent[u]) {
        return parent[u] = find_root(parent[u]);
    }
    return u;
}

int depth[N], lowest[N];
bool used[N << 1];
std::vector <int> stack;

int group_count;
std::vector <int> groups[N];

void dfs(int p, int u, int d) {
    lowest[u] = depth[u] = d;
    for (int it = head[u]; ~it; it = next[it]) {
        if (used[it >> 1]) {
            continue;
        }
        used[it >> 1] = true;
        int v = to[it];
        stack.push_back(it);
        if (depth[v] == -1) {
            dfs(u, v, d + 1);
            if (lowest[v] > depth[u]) {
                // tree edge
                groups[group_count ++].push_back(it);
                assert(stack.back() == it);
                stack.pop_back();
            } else if (lowest[v] == depth[u]) {
                // cycle
                int last;
                while (!stack.empty()) {
                    last = stack.back();
                    stack.pop_back();
                    groups[group_count].push_back(last);
                    if (last == it) {
                        break;
                    }
                }
                group_count ++;
            }
            lowest[u] = std::min(lowest[u], lowest[v]);
        } else {
            lowest[u] = std::min(lowest[u], depth[v]);
        }
    }
}

bool by_weight(int i, int j) {
    return weight[i] < weight[j];
}

const int K = 1000;

int minimum[N + 1][K + 1];

void update(int &x, int a) {
    if (x == -1 || x > a) {
        x = a;
    }
}

int color[N];

void colorit(int u, int c) {
    color[u] = c;
    for (int it = head[u]; ~it; it = next[it]) {
        if (!used[it >> 1]) {
            continue;
        }
        int v = to[it];
        if (color[v] == -1) {
            colorit(v, c);
        }
    }
}

int main() {
    freopen("cacti.in", "r", stdin);
    freopen("cacti.out", "w", stdout);
    scanf("%d%d%d", &n, &m, &colors);
    memset(head, -1, sizeof(head));
    memset(parent, -1, sizeof(parent));
    int component = n;
    for (int i = 0; i < m; ++ i) {
        static int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        a --, b --;
        add_edge(a, b, c);
        add_edge(b, a, c);
        if (find_root(a) != find_root(b)) {
            component --;
            parent[find_root(a)] = find_root(b);
        }
    }
    int need = colors - component;
    memset(used, true, sizeof(used));
    if (need > 0) {
        group_count = 0;
        memset(used, 0, sizeof(used));
        memset(depth, -1, sizeof(depth));
        for (int i = 0; i < n; ++ i) {
            if (depth[i] == -1) {
                dfs(-1, i, 0);
            }
        }
        assert(stack.empty());
        for (int i = 0; i < group_count; ++ i) {
            std::sort(groups[i].begin(), groups[i].end(), by_weight);
        }
        memset(minimum, -1, sizeof(minimum));
        minimum[0][0] = 0;
        for (int i = 0; i < group_count; ++ i) {
            std::vector <int> &group = groups[i];
            int size = group.size();
            for (int j = 0; j <= need; ++ j) {
                if (~minimum[i][j]) {
                    update(minimum[i + 1][j], minimum[i][j]);
                    if (size == 1) {
                        if (j + 1 <= need) {
                            update(minimum[i + 1][j + 1], minimum[i][j] + weight[group[0]]);
                        }
                    } else {
                        int sum = weight[group[0]];
                        for (int k = 1; k < size && j + k <= need; ++ k) {
                            sum += weight[group[k]];
                            update(minimum[i + 1][j + k], minimum[i][j] + sum);
                        }
                    }
                }
            }
        }
        memset(used, true, sizeof(used));
        for (int i = group_count - 1, j = need; i >= 0; -- i) {
            std::vector <int> &group = groups[i];
            int size = group.size();
            if (minimum[i][j] != minimum[i + 1][j]) {
                if (size == 1) {
                    used[group[0] >> 1] = false;
                    j --;
                } else {
                    int sum = weight[group[0]];
                    used[group[0] >> 1] = false;
                    bool found = false;
                    for (int k = 1; k < size && k <= j; ++ k) {
                        used[group[k] >> 1] = false;
                        sum += weight[group[k]];
                        if (minimum[i][j - k] + sum == minimum[i + 1][j]) {
                            j -= k;
                            found = true;
                            break;
                        }
                    }
                    assert(found);
                }
            }
        }
    }
    printf("%d\n", minimum[group_count][need]);
    memset(color, -1, sizeof(color));
    int color_count = 0;
    for (int i = 0; i < n; ++ i) {
        if (color[i] == -1) {
            colorit(i, color_count ++);
        }
    }
    for (int i = 0; i < n; ++ i) {
        printf("%d%c", std::min(color[i] + 1, colors), " \n"[i == n - 1]);
    }
    return 0;
}
