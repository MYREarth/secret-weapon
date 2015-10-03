#include <algorithm>
#include <climits>
#include <cstdio>
#include <cstring>

const int N = 100001;

int n, first_edge[N], to[N << 1], next_edge[N << 1], rank[N << 1], cost[N << 1];
long long result[N];

void add_edge(int u, int v, int b, int c) {
    static int count = 0;
    to[count] = v;
    rank[count] = b;
    cost[count] = c;
    next_edge[count] = first_edge[u];
    first_edge[u] = count ++;
}

const int M = N * 31;

int node_count, key[M], weight[M], count[M], size[M], children[M][2];

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

void insert(int &x, int k, int v) {
    if (x) {
        if (key[x] == k) {
            count[x] += v;
        } else {
            int t = key[x] < k;
            insert(children[x][t], k, v);
            if (weight[children[x][t]] < weight[x]) {
                rotate(x, t);
            }
        }
    } else {
        x = ++ node_count;
        key[x] = k;
        weight[x] = rand();
        count[x] = v;
        children[x][0] = children[x][1] = 0;
    }
    update(x);
}

int query(int &x, int k) {
    if (x) {
        if (key[x] >= k) {
            return query(children[x][0], k);
        }
        return size[children[x][0]] + count[x] + query(children[x][1], k);
    }
    return 0;
}

struct Node {
    Node(int root, Node *left, Node *right) : root(root), left(left), right(right) {}

    int  root;
    Node *left, *right;
};

Node *root, *null;

void insert(Node* &x, int l, int r, int value, int rank, int delta) {
    if (l <= value && value < r) {
        if (x == null) {
            x = new Node(0, null, null);
        }
        insert(x->root, rank, delta);
        if (l + 1 < r) {
            int m = l + r >> 1;
            insert(x->left, l, m, value, rank, delta);
            insert(x->right, m, r, value, rank, delta);
        }
    }
}

int find(Node* &x, int l, int r, int rank, int k) {
    if (l + 1 == r) {
        return l;
    }
    int result = query(x->left->root, rank);
    int m = l + r >> 1;
    if (result >= k) {
        return find(x->left, l, m, rank, k);
    }
    return find(x->right, m, r, rank, k - result);
}

const int X = 2000000000;

void go(int p, int u) {
    for (int it = first_edge[u]; ~it; it = next_edge[it]) {
        int v = to[it];
        if (v == p) {
            continue;
        }
        int desire = query(root->root, rank[it]);
        int new_cost = [&]() {
            if (desire == 0) {
                return cost[it];
            }
            desire = desire + 1 >> 1;
            return find(root, 0, X, rank[it], desire) + 1;
        }();
        result[v] = result[u] + new_cost;
        insert(root, 0, X, new_cost, rank[it], +1);
        go(u, v);
        insert(root, 0, X, new_cost, rank[it], -1);
    }
}

int main() {
    weight[0] = INT_MAX;
    size[0] = 0;
    node_count = 0;
    scanf("%d", &n);
    memset(first_edge, -1, sizeof(first_edge));
    for (int i = 0; i < n; ++ i) {
        int s, t, b, c;
        scanf("%d%d%d%d", &s, &t, &b, &c);
        add_edge(s, t, b, c);
        add_edge(t, s, b, c);
    }
    null = new Node(0, NULL, NULL);
    null->left = null->right = null;
    root = null;
    result[0] = 0;
    go(-1, 0);
    for (int i = 1; i <= n; ++ i) {
        printf("%lld%c", result[i], " \n"[i == n]);
    }
    return 0;
}
