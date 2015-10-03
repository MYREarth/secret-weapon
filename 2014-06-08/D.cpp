#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <utility>
#include <algorithm>

struct Node;

Node *null;

int random(int a, int b) {
    return rand() % (a + b) < a;
}

struct Node {
    Node(int value, Node *left, Node *right) : size(1), reversed(false), value((long long)value * value), sum((long long)value * value), left(left), right(right) {
    }

    Node* update() {
        size = left->size + 1     + right->size;
        sum  = left->sum  + value + right->sum;
        return this;
    }

    Node* push_down() {
        if (reversed) {
            left->reversed ^= 1;
            right->reversed ^= 1;
            std::swap(left, right);
            reversed = false;
        }
        return this;
    }

    std::pair <Node*, Node*> split(int n) {
        if (this == null) {
            return std::make_pair(null, null);
        }
        push_down();
        if (n <= left->size) {
            auto result = left->split(n);
            left = result.second;
            return std::make_pair(result.first, update());
        } else {
            auto result = right->split(n - 1 - left->size);
            right = result.first;
            return std::make_pair(update(), result.second);
        }
    }

    int       size;
    bool      reversed;
    long long value, sum;
    Node      *left, *right;
};

Node* merge(Node* p, Node* q) {
    if (p == null) {
        return q;
    }
    if (q == null) {
        return p;
    }
    if (random(p->size, q->size)) {
        p->push_down();
        p->right = merge(p->right, q);
        return p->update();
    } else {
        q->push_down();
        q->left = merge(p, q->left);
        return q->update();
    }
}

int n;

int main() {
    freopen("dft.in", "r", stdin);
    freopen("dft.out", "w", stdout);
    null = new Node(0, NULL, NULL);
    null->size = 0;
    null->left = null->right = null;
    scanf("%d", &n);
    Node* root = null;
    for (int i = 0; i < n; ++ i) {
        int a;
        scanf("%d", &a);
        root = merge(root, new Node(a, null, null));
    }
    int q;
    scanf("%d", &q);
    while (q --) {
        int l, r;
        scanf("%d%d", &l, &r);
        auto mr = root->split(r);
        auto lm = mr.first->split(l - 1);
        printf("%lld\n", lm.second->sum);
        auto lmm = lm.second->split(1);
        lmm.second->reversed ^= 1;
        root = merge(lm.first, merge(lmm.first, merge(lmm.second, mr.second)));
    }
    return 0;
}

