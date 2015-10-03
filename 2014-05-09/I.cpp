#include <algorithm>
#include <cstdio>
#include <cstring>
#include <climits>
#include <cassert>
#include <vector>

#define ALL(v) (v).begin(), (v).end()

const int N = 100000;

int n, q, m, a, b, c, d, e, f, x[N], y[N];

void transform(int &x, int &y) {
    int a = x + y;
    int b = x - y;
    x = a;
    y = b;
}

std::vector <int> xvalues, yvalues;

struct Node;

Node *null;

struct Node {
    Node(int minimum, Node *left, Node *right) : minimum(minimum), left(left), right(right) { }

    Node* insert(int l, int r, int k, int v) {
        if (k < yvalues[l] || yvalues[r] < k) {
            return this;
        }
        int m = l + r >> 1;
        if (l == r) {
            return new Node(std::min(minimum, v), null, null);
        } else {
            return new Node(std::min(minimum, v), left->insert(l, m, k, v), right->insert(m + 1, r, k, v));
        }
    }

    int query(int l, int r, int a, int b) {
        if (b < yvalues[l] || yvalues[r] < a) {
            return INT_MAX;
        }
        if (a <= yvalues[l] && yvalues[r] <= b) {
            return minimum;
        }
        int m = l + r >> 1;
        return std::min(left->query(l, m, a, b), right->query(m + 1, r, a, b));
    }

    int minimum;
    Node *left, *right;
};

Node *lu[N + 1], *ld[N + 1], *ru[N + 1], *rd[N + 1];

void update(int &x, int a, int b) {
    if (b < INT_MAX) {
        x = std::min(x, a + b);
    }
}

int main() {
    null = new Node(INT_MAX, NULL, NULL);
    null->left = null->right = null;
    scanf("%d%d%d%d%d%d%d%d%d", &n, &q, &m, &a, &b, &c, &d, &e, &f);
    std::vector <std::pair <int, int>> points;
    for (int i = 0; i < n; ++ i) {
        scanf("%d%d", x + i, y + i);
        transform(x[i], y[i]);
        yvalues.push_back(y[i]);
        points.push_back(std::make_pair(x[i], y[i]));
    }
    std::sort(ALL(yvalues));
    yvalues.erase(std::unique(ALL(yvalues)), yvalues.end());
    std::sort(ALL(points));
    int ym = yvalues.size() - 1;
    ld[0] = lu[0] = null;
    for (int i = 0; i < n; ++ i) {
        int x = points[i].first;
        int y = points[i].second;
        ld[i + 1] = ld[i]->insert(0, ym, y, -x - y);
        lu[i + 1] = lu[i]->insert(0, ym, y, -x + y);
    }
    rd[n] = ru[n] = null;
    for (int i = n - 1; i >= 0; -- i) {
        int x = points[i].first;
        int y = points[i].second;
        rd[i] = rd[i + 1]->insert(0, ym, y, x - y);
        ru[i] = ru[i + 1]->insert(0, ym, y, x + y);
    }
    int x, y;
    scanf("%d%d", &x, &y);
    long long result = 0;
    while (q --) {
        int xx = x + y;
        int yy = x - y;
        int now = INT_MAX;
        update(now,  xx + yy, ld[std::upper_bound(ALL(points), std::make_pair(xx, INT_MAX)) - points.begin()]->query(0, ym, INT_MIN, yy));
        update(now,  xx - yy, lu[std::upper_bound(ALL(points), std::make_pair(xx, INT_MAX)) - points.begin()]->query(0, ym, yy, INT_MAX));
        update(now, -xx + yy, rd[std::lower_bound(ALL(points), std::make_pair(xx, INT_MIN)) - points.begin()]->query(0, ym, INT_MIN, yy));
        update(now, -xx - yy, ru[std::lower_bound(ALL(points), std::make_pair(xx, INT_MIN)) - points.begin()]->query(0, ym, yy, INT_MAX));
        assert(now >= 0 && now % 2 == 0);
        now /= 2;
        result += now;
        x = std::abs((long long)a * x + (long long)b * now + c) % (2 * m + 1) - m;
        y = std::abs((long long)d * y + (long long)e * now + f) % (2 * m + 1) - m;
    }
    printf("%lld\n", result);
    return 0;
}
