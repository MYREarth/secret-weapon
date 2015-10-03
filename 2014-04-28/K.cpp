#include <cstdio>
#include <cstring>
#include <vector>

const int N = 80000;

int n, weight[N], depth[N];
std::vector <int> children[N];

struct Node;

Node* null;

struct Node {
    Node(int sum, Node *left, Node *right) : sum(sum), left(left), right(right) {
    }

    int query(int l, int r, int s) {
        if (l + 1 == r) {
            return l;
        }
        int m = l + r >> 1;
        if (left->sum >= s) {
            return left->query(l, m, s);
        }
        return right->query(m, r, s - left->sum);
    }

    int  sum;
    Node *left, *right;
};

Node* build(int l, int r, int k, int v) {
    if (k < l || r <= k) {
        return null;
    }
    if (l + 1 == r) {
        return new Node(v, null, null);
    }
    int m = l + r >> 1;
    return new Node(v, build(l, m, k, v), build(m, r, k, v));
}

Node* merge(Node *p, Node *q) {
    if (p == null) {
        return q;
    }
    if (q == null) {
        return p;
    }
    return new Node(p->sum + q->sum, merge(p->left, q->left), merge(p->right, q->right));
}

Node* trees[N];

void prepare(int p, int u) {
    depth[u] = ~p ? depth[p] + 1 : 0;
    trees[u] = build(0, n, depth[u], weight[u]);
    for (int i = 0; i < (int)children[u].size(); ++ i) {
        int v = children[u][i];
        prepare(u, v);
        trees[u] = merge(trees[u], trees[v]);
    }
}

int main() {
    null = new Node(0, NULL, NULL);
    null->left = null->right = null;
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) {
        scanf("%d", weight + i);
    }
    for (int i = 1; i < n; ++ i) {
        int parent;
        scanf("%d", &parent);
        children[-- parent].push_back(i);
    }
    prepare(-1, 0);
    int q;
    scanf("%d", &q);
    while (q --) {
        int u, s;
        scanf("%d%d", &u, &s);
        u --;
        Node* root = trees[u];
        if (root->sum < s) {
            puts("-1");
        } else {
            printf("%d\n", root->query(0, n, s) - depth[u]);
        }
        fflush(stdout);
    }
    return 0;
}
