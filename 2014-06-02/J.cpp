#include <cstdio>
#include <cstring>

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

int n, q, types[Q], ends[Q][2];
Point points[N];

int first_edge[N], to[M << 1], next_edge[M << 1];

void add_edge(int u, int v) {
    static int count = 0;
    to[count] = v;
    next_edge[count] = first_edge[u];
    first_edge[u] = count ++;
}

std::map <Point, int> nodes[N];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) {
        scanf("%d%d", &points[i].x, &points[i].y);
    }
    scanf("%d", &q);
    memset(first_edge, -1, sizeof(first_edge));
    for (int i = 0; i < q; ++ i) {
        int a, b;
        scanf("%d", types + i, &a, &b);
        if (types[i] == 1) {
            add_edge(ends[i][0], ends[i][1]);
            add_edge(ends[i][1], ends[i][0]);
        }
    }
    return 0;
}
