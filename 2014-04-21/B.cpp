#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>
#include <string>
#include <vector>

#define SIZE(v) ((int)(v).size())

const int N = 100001;

int n, m;
char buffer[N + 1];
std::string words[3][N];

struct Trie {
    int pointer, extra, weight[N], parent[N], position[N], size[N], children[N][26], total;

    void initialize(std::string *words, int n) {
        int count = 1;
        pointer = 0;
        memset(weight, 0, sizeof(weight));
        memset(children, -1, sizeof(children));
        for (int i = 0; i < n; ++ i) {
            int length = SIZE(words[i]);
            int p = 0;
            for (int j = 0; j < length; ++ j) {
                int c = words[i][j] - 'a';
                if (!~children[p][c]) {
                    children[p][c] = count ++;
                }
                p = children[p][c];
            }
            weight[p] ++;
        }
        total = count;

        parent[0] = -1;
        std::vector <int> stack;
        stack.push_back(0);
        count = 0;
        std::vector <int> order;
        while (!stack.empty()) {
            int u = stack.back();
            order.push_back(u);
            stack.pop_back();
            position[u] = count ++;
            for (int i = 0; i < 26; ++ i) {
                int v = children[u][i];
                if (~v) {
                    parent[v] = u;
                    stack.push_back(v);
                }
            }
        }
        std::reverse(order.begin(), order.end());
        for (int v : order) {
            size[v] += 1;
            if (~parent[v]) {
                size[parent[v]] += size[v];
            }
        }
    }

    //void prepare(int u, int &&count) {
    //    size[u] = 1;
    //    position[u] = count ++;
    //    for (int i = 0; i < 26; ++ i) {
    //        int v = children[u][i];
    //        if (~v) {
    //            parent[v] = u;
    //            prepare(v, std::move(count));
    //            size[u] += size[v];
    //        }
    //    }
    //}

    int get(const std::string &pattern) {
        int p = 0;
        for (int i = 0; i < SIZE(pattern); ++ i) {
            p = children[p][pattern[i] - 'a'];
        }
        return p;
    }

    void go(int c) {
        if (c == -1) {
            if (extra) {
                extra --;
            } else {
                pointer = parent[pointer];
            }
        } else if (!extra && ~children[pointer][c]) {
            pointer = children[pointer][c];
        } else {
            extra ++;
        }
    }

    int get_pointer() {
        return extra ? -1 : pointer;
    }
} tries[3];

int q, points[N][3], queries[N][3];

namespace Treap {
    const int NN = N * 18;

    int node_count, key[NN], weight[NN], count[NN], size[NN], children[NN][2];

    void initialize() {
        node_count = 0;
        size[0] = 0;
        weight[0] = INT_MAX;
    }

    void update(int &x) {
        size[x] = size[children[x][0]] + count[x] + size[children[x][1]];
    }

    void rotate(int &x, int t) {
        int y = children[x][t];
        children[x][t] = children[y][1 ^ t];
        children[y][1 ^ t] = x;
        update(x);
        update(y);
        x = y;
    }

    void insert(int &x, int k) {
        if (x) {
            if (key[x] == k) {
                count[x] ++;
            } else {
                int t = key[x] < k;
                insert(children[x][t], k);
                if (weight[children[x][t]] < weight[x]) {
                    rotate(x, t);
                }
            }
        } else {
            x = ++ node_count;
            key[x] = k;
            count[x] = 1;
            weight[x] = rand();
            children[x][0] = children[x][1] = 0;
        }
        update(x);
    }

    int query(int &x, int k) {
        if (x) {
            if (key[x] < k) {
                return query(children[x][1], k);
            }
            return query(children[x][0], k) + count[x] + size[children[x][1]];
        } else {
            return 0;
        }
    }
}

int roots[N << 1];

int get_id(int l, int r) {
    return l + r | l != r;
}

void insert(int l, int r, int x, int y) {
    if (l <= x && x <= r) {
        int id = get_id(l, r);
        Treap::insert(roots[id], y);
        if (l < r) {
            int m = l + r >> 1;
            insert(l, m, x, y);
            insert(m + 1, r, x, y);
        }
    }
}

int query(int l, int r, int x1, int x2, int y1, int y2) {
    if (x2 < l || r < x1) {
        return 0;
    }
    if (x1 <= l && r <= x2) {
        int id = get_id(l, r);
        return Treap::query(roots[id], y1) - Treap::query(roots[id], y2);
    }
    int m = l + r >> 1;
    return query(l, m, x1, x2, y1, y2) + query(m + 1, r, x1, x2, y1, y2);
}

struct Event {
    int type, id, x;

    Event(int type, int id, int x) : type(type), id(id), x(x) {}
};

bool operator < (const Event &a, const Event &b) {
    if (a.x != b.x) {
        return a.x < b.x;
    }
    return !a.type < !b.type;
}

int result[N];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < m; ++ j) {
            scanf("%s", buffer);
            words[j][i] = buffer;
        }
    }
    for (int i = 0; i < 3; ++ i) {
        tries[i].initialize(words[i], n);
    }
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < 3; ++ j) {
            points[i][j] = tries[j].get(words[j][i]);
        }
    }
    scanf("%d", &q);
    for (int i = 0; i < q; ++ i) {
        int id;
        scanf("%d%s", &id, buffer);
        id --;
        if (*buffer == '+') {
            scanf("%s", buffer);
            tries[id].go(*buffer - 'a');
        } else {
            tries[id].go(-1);
        }
        for (int j = 0; j < 3; ++ j) {
            queries[i][j] = tries[j].get_pointer();
        }
    }
    Treap::initialize();
    memset(roots, 0, sizeof(roots));
    std::vector <Event> events;
    for (int i = 0; i < n; ++ i) {
        events.push_back(Event(0, i, tries[0].position[points[i][0]]));
    }
    for (int i = 0; i < q; ++ i) {
        if (~queries[i][0] && ~queries[i][1] && ~queries[i][2]) {
            events.push_back(Event(1, i, tries[0].position[queries[i][0]]));
            events.push_back(Event(-1, i, tries[0].position[queries[i][0]] + tries[0].size[queries[i][0]]));
        }
    }
//for (int i = 0; i < n; ++ i) {
//    printf("%d %d %d\n", points[i][0], points[i][1], points[i][2]);
//}
//puts("---");
//for (int i = 0; i < q; ++ i) {
//    printf("%d %d %d\n", queries[i][0], queries[i][1], queries[i][2]);
//}
//puts("---");
    std::sort(events.begin(), events.end());
    memset(result, 0, sizeof(result));
    for (int i = (int)events.size() - 1; i >= 0; -- i) {
        Event e = events[i];
        if (e.type == 0) {
            insert(0, tries[1].total - 1, tries[1].position[points[e.id][1]], tries[2].position[points[e.id][2]]);
        } else {
            int x1 = tries[1].position[queries[e.id][1]];
            int x2 = x1 + tries[1].size[queries[e.id][1]];
            int y1 = tries[2].position[queries[e.id][2]];
            int y2 = y1 + tries[2].size[queries[e.id][2]];
            result[e.id] += e.type * query(0, tries[1].total - 1, x1, x2 - 1, y1, y2);
        }
    }
    for (int i = 0; i < q; ++ i) {
        printf("%d\n", result[i]);
    }
    return 0;
}
