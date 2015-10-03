#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <utility>

struct Node;
Node *null;

typedef std::pair <Node*, Node*> Pair;

int random(int a, int b) {
    return rand() % (a + b) < a;
}

Node* merge(Node*, Node*);

struct Node {
    char value;
    bool reversed;
    int  size;
    Node *left, *right;

    Node(char value, bool reversed, int size, Node* left, Node* right)
        : value(value), reversed(reversed), size(size), left(left), right(right) {}

    Node* reverse() {
        if (this == null) {
            return this;
        } else {
            return new Node(value, reversed ^ 1, size, left, right);
        }
    }

    Node* push_down() {
        if (!reversed) {
            return this;
        } else {
            return new Node(value, false, size, right->reverse(), left->reverse());
        }
    }

    Pair split(int n) {
        if (this == null) {
            return Pair(null, null);
        }
        Node* u = push_down();
        if (n <= u->left->size) {
            Pair ret = u->left->split(n);
            return Pair(ret.first, merge(ret.second, new Node(u->value, false, 1 + u->right->size, null, u->right)));
        } else {
            Pair ret = u->right->split(n - 1 - u->left->size);
            return Pair(merge(new Node(u->value, false, 1 + u->left->size, u->left, null), ret.first), ret.second);
        }
        assert(false);
    }

    void dump() {
        if (this != null) {
            Node* u = push_down();
            u->left->dump();
            putchar(u->value);
            u->right->dump();
        }
    }
};

Node* merge(Node *a, Node *b) {
    if (a == null) {
        return b;
    }
    if (b == null) {
        return a;
    }
    if (random(a->size, b->size)) {
        a = a->push_down();
        return new Node(a->value, false, a->size + b->size, a->left, merge(a->right, b));
    } else {
        b = b->push_down();
        return new Node(b->value, false, a->size + b->size, merge(a, b->left), b->right);
    }
}

const int N = 200000;

char buffer[N + 1];

void split2(Node* root, int n, Node*& x, Node*& y) {
    Pair pair = root->split(n);
    x = pair.first;
    y = pair.second;
}

void split3(Node* root, int l, int r, Node*& x, Node*& y, Node*& z) {
    split2(root, r, y, z);
    split2(y, l - 1, x, y);
}

int main() {
    freopen("palindroming.in", "r", stdin);
    freopen("palindroming.out", "w", stdout);
    null = new Node(0, false, 0, NULL, NULL);
    null->left = null->right = null;
    Node* root = null;
    int n, m;
    scanf("%d%d%s", &n, &m, buffer);
    for (int i = 0; i < n; ++ i) {
        Node* node = new Node(buffer[i], false, 1, null, null);
        root = merge(root, node);
    }
    while (m --) {
        int l, r;
        scanf("%d%d", &l, &r);
        Node *u, *v, *w;
        split3(root, l, r, u, v, w);
        int length = r - l + 1;
        if (length & 1) {
            Node *x, *y, *z;
            int p = (length >> 1) + 1;
            split3(v, p, p, x, y, z);
            v = merge(x, merge(y, x->reverse()));
        } else {
            Node *x, *y;
            split2(v, length >> 1, x, y);
            v = merge(x, x->reverse());
        }
        root = merge(u, merge(v, w));
    }
    root->dump();
    puts("");
    return 0;
}
