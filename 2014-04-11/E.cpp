#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <iostream>

#define ALL(v) (v).begin(), (v).end()

const int N = 2000;
const int M = N * (N - 1) / 2;

int n, m, d, a[M], b[M], parent[N];
long long c[M];

bool by_cost(int i, int j) {
    if (c[i] != c[j]) {
        return c[i] < c[j];
    }
    if ((!a[i] || !b[i]) != (!a[j] || !b[j])) {
        return (!a[i] || !b[i]) < (!a[j] || !b[j]);
    }
    return i < j;
}

int get_root(int u) {
    if (parent[u] != u) {
        parent[u] = get_root(parent[u]);
    }
    return parent[u];
}

std::vector <int> mst(std::vector <int> &order) {
    for (int i = 0; i < n; ++ i) {
        parent[i] = i;
    }
    std::vector <int> result;
    for (int &e : order) {
        if (get_root(a[e]) != get_root(b[e])) {
            result.push_back(e);
            parent[get_root(a[e])] = get_root(b[e]);
        }
    }
    return result;
}

int main() {
    freopen("highway.in", "r", stdin);
    scanf("%d%d%d", &n, &m, &d);
    std::vector <int> bedges, wedges;
    for (int i = 0; i < m; ++ i) {
        scanf("%d%d%lld", a + i, b + i, c + i);
        a[i] --;
        b[i] --;
        c[i] *= 2;
        if (a[i] && b[i]) {
            wedges.push_back(i);
        } else {
            bedges.push_back(i);
        }
    }
    {
        std::sort(ALL(wedges), by_cost);
        std::vector <int> result = mst(wedges);
        for (int &e : result) {
            bedges.push_back(e);
        }
    }
    long long low = 0;
    long long high = 2000000001;
    while (low < high) {
        long long middle = low + high >> 1;
        for (int &e : bedges) {
            if (!a[e] || !b[e]) {
                c[e] += middle;
            }
        }
        std::sort(ALL(bedges), by_cost);
        std::vector <int> result = mst(bedges);
        int count = 0;
        for (int &e : result) {
            if (!a[e] || !b[e]) {
                count ++;
            }
        }
        if (count <= d) {
            high = middle;
        } else {
            low = middle + 1;
        }
        for (int &e : bedges) {
            if (!a[e] || !b[e]) {
                c[e] -= middle;
            }
        }
    }
    for (int &e : bedges) {
        if (!a[e] || !b[e]) {
            c[e] += high;
        }
    }
    std::sort(ALL(bedges), by_cost);
    std::vector <int> result = mst(bedges);
    for (int &e : bedges) {
        if (!a[e] || !b[e]) {
            c[e] -= high;
        }
    }
    long long answer = 0;
    for (int &e : result) {
        answer += c[e];
    }
    std::cout << answer / 2 << std::endl;
    return 0;
}
