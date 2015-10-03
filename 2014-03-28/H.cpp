#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>

typedef std::vector <int> Permutation;

const int TRANSFORMATIONS[3][6] = {{2, 3, 1, 0, 4, 5}, {0, 1, 4, 5, 3, 2}, {5, 4, 2, 3, 0, 1}};

Permutation composite(const Permutation &p, const Permutation &q) {
    Permutation r(6);
    for (int i = 0; i < 6; ++ i) {
        r[i] = p[q[i]];
    }
    return r;
}

std::vector <Permutation> permutations;

int get_pid(const Permutation &p) {
    for (int i = 0; i < (int)permutations.size(); ++ i) {
        if (permutations[i] == p) {
            return i;
        }
    }
    return -1;
}

int group[24][24];

struct Count {
    int count[6][6];

    Count() {
        memset(count, 0, sizeof(count));
    }

    Count(const Count &a, const Count &b) {
        for (int i = 0; i < 6; ++ i) {
            for (int j = 0; j < 6; ++ j) {
                count[i][j] = a[i][j] + b[i][j];
            }
        }
    }

    int* operator[](int i) {
        return count[i];
    }

    const int* operator[](int i) const {
        return count[i];
    }
};

struct Node;

Node *null;

typedef std::pair <Node*, Node*> Pair;

const int N = 100000;

int colors[N][6];

struct Node {
    int   id, delta, action, size;
    bool  reversed;
    Count count;
    Node  *left, *right;

    Node() : id(-1), delta(0), action(0), size(0), reversed(false), left(null), right(null) {}

    Node* push_down() {
        if (reversed) {
            left->reversed ^= 1;
            right->reversed ^= 1;
            std::swap(left, right);
            reversed = false;
        }
        if (delta) {
            left->perform(delta);
            right->perform(delta);
            delta = 0;
        }
        return this;
    }

    Node* update() {
        size  = left->size + 1 + right->size;
        count = Count(left->count, right->count);
        for (int i = 0; i < 6; ++ i) {
            count[i][colors[id][permutations[action][i]]] ++;
        }
        return this;
    }

    Node* perform(int p) {
        action = group[action][p];
        delta  = group[delta][p];
        Count newCount;
        for (int i = 0; i < 6; ++ i) {
            for (int j = 0; j < 6; ++ j) {
                newCount[i][j] = count[permutations[p][i]][j];
            }
        }
        count = newCount;
        return this;
    }

    void dump() {
        if (this != null) {
            push_down();
            left->dump();
            for (int i = 0; i < 6; ++ i) {
                printf("%d", colors[id][permutations[action][i]] + 1);
            }
            puts("");
            right->dump();
        }
    }

    Pair split(int);
};

int random(int a, int b) {
    return rand() % (a + b) < a;
}

Node* merge(Node *a, Node *b) {
    if (a == null) {
        return b;
    }
    if (b == null) {
        return a;
    }
    if (random(a->size, b->size)) {
        a->push_down();
        a->right = merge(a->right, b);
        return a->update();
    } else {
        b->push_down();
        b->left = merge(a, b->left);
        return b->update();
    }
}

Pair Node::split(int n) {
    if (this == null) {
        return Pair(null, null);
    }
    push_down();
    if (n <= left->size) {
        Pair p = left->split(n);
        left = null;
        return Pair(p.first, merge(p.second, update()));
    } else {
        Pair p = right->split(n - (1 + left->size));
        right = null;
        return Pair(merge(update(), p.first), p.second);
    }
}

int main() {
    freopen("toys.in", "r", stdin);
    freopen("toys.out", "w", stdout);
    {
        Permutation id(6);
        for (int i = 0; i < 6; ++ i) {
            id[i] = i;
        }
        permutations.push_back(id);
    }
    for (int head = 0; head < (int)permutations.size(); ++ head) {
        Permutation p = permutations[head];
        for (int i = 0; i < 3; ++ i) {
            Permutation q(6);
            for (int j = 0; j < 6; ++ j) {
                q[j] = TRANSFORMATIONS[i][j];
            }
            Permutation r = composite(p, q);
            if (get_pid(r) == -1) {
                permutations.push_back(r);
            }
        }
    }
    for (int i = 0; i < 24; ++ i) {
        for (int j = 0; j < 24; ++ j) {
            group[i][j] = get_pid(composite(permutations[i], permutations[j]));
            assert(group[i][j] != -1);
        }
    }
    null = new Node();
    null->left = null->right = null;
    int n;
    scanf("%d", &n);
    Node *root = null;
    for (int i = 0; i < n; ++ i) {
        char buffer[7];
        scanf("%s", buffer);
        for (int j = 0; j < 6; ++ j) {
            colors[i][j] = buffer[j] - '1';
        }
        Node *u = new Node();
        u->id = i;
        u->update();
        root = merge(root, u);
    }
    int q;
    scanf("%d", &q);
    while (q --) {
        char buffer[2];
        scanf("%s", buffer);
        if (*buffer == '?') {
            for (int i = 0; i < 6; ++ i) {
                printf("%d%c", root->count[0][i], " \n"[i == 5]);
            }
        } else {
            int l, r;
            scanf("%d%d", &l, &r);
            Pair q = root->split(r);
            Pair p = q.first->split(l - 1);
            Node *u = p.second;
            int t = -1;
            if (*buffer == 'F') {
                t = 1;
            } else if (*buffer == 'B') {
                t = group[1][group[1][1]];
            } else if (*buffer == 'U') {
                t = 2;
            } else if (*buffer == 'D') {
                t = group[2][group[2][2]];
            } else if (*buffer == 'L') {
                t = 3;
            } else if (*buffer == 'R') {
                t = group[3][group[3][3]];
            }
            assert(t != -1);
            if (*buffer != 'L' && *buffer != 'R') {
                if (l < r) {
                    u->reversed ^= 1;
                    t = group[t][t];
                }
            }
            u->perform(t);
            root = merge(p.first, merge(u, q.second));
        }
    }
    root->dump();
    return 0;
}
