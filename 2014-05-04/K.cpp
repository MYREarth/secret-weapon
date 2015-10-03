#include <cstdio>
#include <cstring>
#include <climits>
#include <utility>
#include <queue>
#include <set>
#include <algorithm>

const int N = 100000;

int n, m, s, a, b;
int first_edge[N], to[N << 1], next_edge[N << 1], first_edge2[N], to2[N << 1], next_edge2[N << 1];

void add_edge(int u, int v) {
    static int count = 0;
    to[count] = v;
    next_edge[count] = first_edge[u];
    first_edge[u] = count ++;
}

//std::set <long long> edges_set;
//
//long long get_hash(int a, int b) {
//    if (a > b) {
//        std::swap(a, b);
//    }
//    return (long long)a * n + b;
//}

//inline bool has_edge(int a, int b) {
//    return edges_set.count(get_hash(a, b));
//}

int distance[N], stamp[N], now;

std::priority_queue <std::pair <int, int>> queue;

void update(int u, int v, int w) {
    if (distance[u] + w < distance[v]) {
        distance[v] = distance[u] + w;
        queue.push(std::make_pair(-distance[v], v));
    }
}

int main() {
    scanf("%d%d%d%d%d", &n, &m, &s, &a, &b);
    s --;
    memset(first_edge, -1, sizeof(first_edge));
    for (int i = 0; i < m; ++ i) {
        int a, b;
        scanf("%d%d", &a, &b);
        a --;
        b --;
        add_edge(a, b);
        add_edge(b, a);
    }
    for (int i = 0; i < n; ++ i) {
        first_edge2[i] = first_edge[i];
    }
    for (int i = 0; i < m << 1; ++ i) {
        to2[i] = to[i];
        next_edge2[i] = next_edge[i];
    }
    now = 0;
    memset(stamp, -1, sizeof(stamp));
    std::fill(distance, distance + n, INT_MAX);
    distance[s] = 0;
    queue.push(std::make_pair(-0, s));
    while (!queue.empty()) {
        auto pair = queue.top();
        queue.pop();
        int u = pair.second;
        if (-pair.first == distance[u]) {
            now ++;
            for (int it = first_edge2[u]; ~it; it = next_edge2[it]) {
                stamp[to[it]] = now;
            }
            for (int it = first_edge2[u]; ~it; it = next_edge2[it]) {
                int v = to[it];
                update(u, v, a);
                int head = -1;
                for (int it2 = first_edge[v]; ~it2; ) {
                    int vv = to[it2];
                    int backup = next_edge[it2];
                    if (stamp[vv] == now) {
                        next_edge[it2] = head;
                        head = it2;
                    } else {
                        update(u, vv, b);
                    }
                    it2 = backup;
                }
                first_edge[v] = head;
            }
        }
    }
    for (int i = 0; i < n; ++ i) {
        printf("%d\n", distance[i]);
    }
    return 0;
}
