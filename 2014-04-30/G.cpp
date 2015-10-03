#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <utility>
#include <vector>

#define ALL(v) (v).begin(), (v).end()

const int N = 100000;

int n, x[N], y[N];

struct Node;

Node* null;

typedef std::pair <Node*, Node*> Pair;

int random(int a, int b) {
    return rand() % (a + b) < a;
}

struct Node {
    int id, size;
    bool reversed;
    Node *parent, *left, *right;

    Node* push_down() {
        if (reversed) {
            reversed = false;
            left->reversed ^= 1;
            right->reversed ^= 1;
            std::swap(left, right);
        }
        return this;
    }

    Node* update() {
        size = left->size + 1 + right->size;
        return this;
    }

    Pair split(int n) {
        if (this == null) {
            return Pair(null, null);
        }
        push_down();
        if (left->size >= n) {
            Pair result = left->split(n);
            left = result.second;
            result.second->parent = this;
            return Pair(result.first, update());
        } else {
            Pair result = right->split(n - left->size - 1);
            right = result.first;
            result.first->parent = this;
            return Pair(update(), result.second);
        }
    }

    int rank() {
        std::vector <Node*> nodes;
        for (Node *p = this; p != null; p = p->parent) {
            nodes.push_back(p);
        }
        std::reverse(ALL(nodes));
        for (Node *&p : nodes) {
            p->push_down();
        }
        int result = left->size;
        for (int i = 0; i + 1 < (int)nodes.size(); ++ i) {
            if (nodes[i + 1] == nodes[i]->right) {
                result += 1 + nodes[i]->left->size;
            }
        }
        return result;
    }

    void dump(bool flag = false) {
        if (this != null) {
            if (flag ^ reversed) {
                right->dump(flag ^ reversed);
                printf("%d, ", id + 1);
                left->dump(flag ^ reversed);
            } else {
                left->dump(flag ^ reversed);
                printf("%d, ", id + 1);
                right->dump(flag ^ reversed);
            }
        }
    }
};

Node* merge(Node *p, Node *q) {
    if (p == null) {
        return q;
    }
    if (q == null) {
        return p;
    }
    if (random(p->size, q->size)) {
        p->push_down();
        p->right = merge(p->right, q);
        p->right->parent = p;
        return p->update();
    } else {
        q->push_down();
        q->left = merge(p, q->left);
        q->left->parent = q;
        return q->update();
    }
}

Node* nodes[N];

int sqr(int x) {
    return x * x;
}

int main() {
    null = new Node();
    null->size = 0;
    null->parent = null->left = null->right = null;
    int q;
    scanf("%d%d", &n, &q);
    for (int i = 0; i < n; ++ i) {
        scanf("%d%d", x + i, y + i);
    }
    Node *root = null;
    for (int i = 0; i < n; ++ i) {
        nodes[i] = new Node();
        nodes[i]->id = i;
        nodes[i]->size = 1;
        nodes[i]->parent = nodes[i]->left = nodes[i]->right = null;
        root = merge(root, nodes[i]);
        root->parent = null;
    }
    while (q --) {
        int a, b;
        scanf("%d%d", &a, &b);
        a --;
        b --;
        a = nodes[a]->rank();
        b = nodes[b]->rank();
        Pair result = root->split(a);
        root = merge(result.second, result.first);
        root->parent = null;
        result = root->split(a <= b ? b - a + 1 : b + n - a + 1);
        result.first->reversed ^= 1;
        root = merge(result.first, result.second);
        root->parent = null;
    }
    std::vector <int> order;
    while (root->size) {
        Pair result = root->split(1);
        order.push_back(result.first->id);
        root = result.second;
    }
    double result = 0.;
    for (int i = 0; i < n; ++ i) {
        int p = order[i];
        int q = order[(i + 1) % n];
        result += sqrt(sqr(x[p] - x[q]) + sqr(y[p] - y[q]));
    }
    printf("%.2f\n", result);
    return 0;
}
