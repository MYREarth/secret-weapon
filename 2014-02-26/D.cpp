#include <cstdio>
#include <cstring>
#include <utility>
#include <algorithm>

const int N = 100000;

struct Info {
    int count[10];

    Info() {
        memset(count, 0, sizeof(count));
    }

    Info& operator+=(const Info& other) {
        for (int i = 0; i < 10; ++ i) {
            count[i] += other.count[i];
        }
        return *this;
    }

    void add(int d) {
        std::rotate(count, count + ((10 - d) % 10 + 10) % 10, count + 10);
    }
};

Info operator +(Info a, const Info &b) {
    return a += b;
}

struct Node;

Node* null;

bool random(int a, int b)
{
    return rand() % (a + b) < a;
}

typedef std::pair <Node*, Node*> Pair;

Node* merge(Node*, Node*);

struct Node {
    Node *left, *right;
    bool reveresed;
    int size, delta;
    Info self, subtree;

    Node() : left(null), right(null), reveresed(false), size(1), delta(0) {
    }

    void push_down() {
        if (delta) {
            left->add(delta);
            right->add(delta);
            delta = 0;
        }
        if (reveresed) {
            reveresed = false;
            left->reveresed ^= 1;
            right->reveresed ^= 1;
            std::swap(left, right);
        }
    }

    Node* update() {
        subtree = left->subtree + self + right->subtree;
        size = left->size + 1 + right->size;
        return this;
    }

    void add(int d) {
        (delta += d) %= 10;
        self.add(d);
        subtree.add(d);
    }

    Pair split(int n) {
        if (this == null) {
            return std::make_pair(null, null);
        }
        push_down();
        if (n <= left->size) {
            Pair ret = left->split(n);
            left = null;
            return std::make_pair(ret.first, merge(ret.second, update()));
        } else {
            Pair ret = right->split(n - 1 - left->size);
            right = null;
            return std::make_pair(merge(update(), ret.first), ret.second);
        }
    }
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
char buffer[N + 1];

const int MOD = (int)1e9 + 7;

int fact[N + 1], invFact[N + 1];

int inverse(int a) {
    return a == 1 ? 1 : (long long)(MOD - MOD / a) * inverse(MOD % a) % MOD;
}

int main()
{
    freopen("permutations.in", "r", stdin);
    freopen("permutations.out", "w", stdout);
    fact[0] = 1;
    for (int i = 1; i <= N; ++ i) {
        fact[i] = (long long)fact[i - 1] * i % MOD;
    }
    for (int i = 0; i <= N; ++ i) {
        invFact[i] = inverse(fact[i]);
    }
    null = new Node();
    null->left = null->right = null;
    null->size = 0;
    scanf("%d%s", &n, buffer);
    Node* root = null;
    for (int i = 0; i < n; ++ i) {
        Node* node = new Node();
        node->self.count[buffer[i] - 'a'] ++;
        root = merge(root, node->update());
    }
    int q;
    scanf("%d", &q);
    while (q --) {
        static int op, l, r;
        scanf("%d%d%d", &op, &l, &r);
        Pair ret1 = root->split(r);
        Pair ret2 = ret1.first->split(l - 1);
        Node* tree = ret2.second;
        if (op == -1) {
            tree->reveresed ^= 1;
        } else if (op == 0) {
            static int d;
            scanf("%d", &d);
            tree->add(d);
        } else {
            long long result = fact[r - l + 1];
            for (int i = 0; i < 10; ++ i) {
                result = result * invFact[tree->subtree.count[i]] % MOD;
            }
            printf("%d\n", (int)result);
        }
        root = merge(ret2.first, merge(tree, ret1.second));
    }
    return 0;
}
