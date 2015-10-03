#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>

const int N = 1000000;

int n, m, q, weight[N], degree[N], order[N], neighbours[N][2], parent[N + N];

bool by_weight(int i, int j) {
    return weight[i] > weight[j];
}

int find(int u) {
    if (parent[u] != u) {
        parent[u] = find(parent[u]);
    }
    return parent[u];
}

void link(int u, int v) {
    parent[find(u)] = find(v);
}

bool solve(int u) {
    if (degree[u] == 0) {
        return false;
    }
    if (find(neighbours[u][0]) >= n) {
        link(neighbours[u][0], u);
        if (degree[u] == 2) {
            link(u, neighbours[u][1]);
        }
        return true;
    }
    if (degree[u] == 1) {
        return false;
    }
    if (find(neighbours[u][1]) >= n) {
        link(neighbours[u][1], u);
        return true;
    }
    return false;
}

int main() {
    freopen("binary.in", "r", stdin);
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 0; i < n; ++ i) {
        scanf("%d", weight + i);
    }
    memset(degree, 0, sizeof(degree));
    while (q --) {
        int a, b;
        scanf("%d%d", &a, &b);
        a --;
        b --;
        neighbours[a][degree[a] ++] = n + b;
    }
    for (int i = 0; i < n; ++ i) {
        order[i] = i;
    }
    std::sort(order, order + n, by_weight);
    long long result = 0;
    for (int i = 0; i < n + m; ++ i) {
        parent[i] = i;
    }
    for (int i = 0; i < n; ++ i) {
        int u = order[i];
        if (solve(u)) {
            result += weight[u];
        }
    }
    std::cout << result << std::endl;
    return 0;
}
