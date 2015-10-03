#include <algorithm>
#include <cstdio>
#include <cstring>
#include <utility>

struct Node;

Node *null;

int random(int a, int b) {
    return rand() % (a + b) < a;
}

typedef std::pair <Node*, Node*> Pair;

struct Node {
    Node* renew(Node *l, Node *r) {
        Node* n = new Node();
        n->value = value;
        n->left = l;
        n->right = r;
        return n->update();
    }

    Node* update() {
        size = left->size + 1 + right->size;
        return this;
    }

    Pair split(int n) {
    }

    int  value, size;
    Node *left, *right;
};

int main() {
    null = new Node();
    null->size = 0;
    null->left = null->right = null;
    return 0;
}
