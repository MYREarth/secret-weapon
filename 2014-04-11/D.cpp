#include <cstdio>
#include <cstring>
#include <set>
#include <queue>
#include <utility>
#include <functional>
#include <algorithm>

typedef std::set <std::pair <int, int> > Set;

const int N = 100000;

int n, m, next[N], degree[N];
Set* sets[N];

Set* merge(Set *a, Set *b) {
    if (a->size() > b->size()) {
        std::swap(a, b);
    }
    for (auto &v : *a) {
        b->insert(v);
    }
    delete a;
    return b;
}

Set* add(Set *set, int delta, int name) {
    if (set->empty()) {
        set->insert(std::make_pair(0, name));
    }
    auto rbegin = *set->rbegin();
    set->erase(set->find(rbegin));
    set->insert(std::make_pair(rbegin.first + delta, rbegin.second));
    return set;
}

bool visited[N];

int main() {
    freopen("free.in", "r", stdin);
    scanf("%d%d", &n, &m);
    memset(degree, 0, sizeof(degree));
    for (int i = 0; i < n; ++ i) {
        scanf("%d", next + i);
        next[i] --;
        degree[next[i]] ++;
        sets[i] = new Set();
    }
    std::queue <int> queue;
    for (int i = 0; i < n; ++ i) {
        if (!degree[i]) {
            queue.push(i);
        }
    }
    while (!queue.empty()) {
        int u = queue.front();
        queue.pop();
        sets[next[u]] = merge(sets[next[u]], add(sets[u], 1, u));
        if (!--degree[next[u]]) {
            queue.push(next[u]);
        }
    }
    Set* candidates = new Set();
    for (int i = 0; i < n; ++ i) {
        if (degree[i]) {
            int length = 0;
            Set *set = new Set();
            int p = i;
            do {
                length ++;
                degree[p] = 0;
                set = merge(set, sets[p]);
                p = next[p];
            } while (p != i);
            candidates = merge(candidates, add(set, length, i));
        }
    }
    std::vector <std::pair <int, int> > cc;
    for (auto &it : *candidates) {
        cc.push_back(it);
    }
    std::sort(cc.begin(), cc.end(), std::greater <std::pair <int, int> >());
    int result = 0;
    memset(visited, 0, sizeof(visited));
    for (int i = 0; i < (int)cc.size() && i < m; ++ i) {
        result += cc[i].first;
        visited[cc[i].second] = true;
    }
    m -= cc.size();
    for (int i = 0; i < n; ++ i) {
        if (!visited[i] && m > 0) {
            visited[i] = true;
            m --;
        }
    }
    printf("%d\n", result);
    bool first = true;
    for (int i = 0; i < n; ++ i) {
        if (visited[i]) {
            if (first) {
                first = false;
            } else {
                putchar(' ');
            }
            printf("%d", i + 1);
        }
    }
    puts("");
    return 0;
}
