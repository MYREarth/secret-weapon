#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <map>
#include <utility>

const int N = 200000;
const int M = 1000000;

struct Point {
    Point() : x(0), y(0) {}
    Point(int x, int y) : x(x), y(y) {}

    int quadrant() const {
        assert(x || y);
        if (y) {
            return y > 0;
        }
        return x > 0;
    }

    Point &operator -= (const Point &other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    int x, y;
};

long long det(const Point &a, const Point &b) {
    return (long long)a.x * b.y - (long long)a.y * b.x;
}

bool operator < (const Point &a, const Point &b) {
    if (a.quadrant() != b.quadrant()) {
        return a.quadrant() < b.quadrant();
    }
    return det(a, b) > 0;
}

Point operator - (Point a, const Point &b) {
    return a -= b;
}

struct Node;
Node *null;

int random(int a, int b) {
    return rand() % (a + b) < a;
}

struct Node {
    int size;
    long long sum, self_area;
    Node *parent, *left, *right;

    Node(long long area) : size(1), sum(area), self_area(area), parent(null), left(null), right(null) {
    }

    std::pair <Node*, Node*> split(int n) {
        if (this == null) {
            return std::make_pair(null, null);
        }
        if (n <= left->size) {
            auto result = left->split(n);
            Node *tree = result.second;
            tree->parent = this;
            left = tree;
            return std::make_pair(result.first, update());
        } else {
            auto result = right->split(n - left->size - 1);
            Node *tree = result.first;
            tree->parent = this;
            right = tree;
            return std::make_pair(update(), result.second);
        }
    }

    Node* get_root() {
        Node *p = this;
        while (p->parent != null) {
            p = p->parent;
        }
        return p;
    }

    Node* update() {
        size = left->size + 1         + right->size;
        sum  = left->sum  + self_area + right->sum;
        return this;
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
        Node* tree = merge(p->right, q);
        tree->parent = p;
        p->right = tree;
        return p->update();
    } else {
        Node* tree = merge(p, q->left);
        tree->parent = q;
        q->left = tree;
        return q->update();
    }
}

int   n;
Point points[N];

Node* edges[M << 1], next_edge[M << 1], previous_edge[M << 1];
std::map <Point, int> nodes[N];
std::map <std::pair <int, int>, int> edges_map;

int get_previous_edge(int u, int v) {
    if (nodes[u].empty()) {
        return -1;
    }
    auto iterator = nodes[u].upper_bound(points[v] - points[u]);
    if (iterator == nodes[u].end()) {
        return nodes[u].begin()->second;
    }
    return iterator->second;
}

int get_next_edge(int u, int v) {
    if (nodes[v].empty()) {
        return -1;
    }
    auto iterator = nodes[v].lower_bound(points[u] - points[v]);
    if (iterator == nodes[u].begin()) {
        return nodes[u].rbegin()->second;
    }
    iterator --;
    return iterator->second;
}

void add_edge(int u, int v) {
    Node *e = edges[edge_count] = new Node(det(points[u], points[v]));
    int id = get_previous_edge(u, v);


    nodes[u][points[v] - points[u]] = edge_count;
    edges_map[std::make_pair(u, v)] = edge_count ++;
}

int main() {
    null = new Node();
    null->size = null->sum = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) {
        scanf("%d%d", &points[i].x, &points[i].y);
    }
    int q;
    scanf("%d", &q);
    int edge_count = 0;
    while (q --) {
        int t, a, b;
        scanf("%d%d%d", &t, &a, &b);
        if (t == 1) {
            add_edge(a, b);
            add_edge(b, a);
        } else {
            Node* e = edges[edges_map[std::make_pair(a, b)]]->get_root();
            long long result = e->sum;
            printf("%lld\n", result < 0 ? -1 : result);
        }
    }
    return 0;
}
