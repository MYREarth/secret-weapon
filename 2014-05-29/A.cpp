#include <cstdio>
#include <cstring>
#include <map>
#include <set>
#include <algorithm>

const int N = 500;

int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

struct Point {
    Point() : x(0), y(0), z(0) {}
    Point(int x, int y, int z) : x(x), y(y), z(z) {
    }

    Point& operator -= (const Point &o) {
        x -= o.x;
        y -= o.y;
        z -= o.z;
        return *this;
    }

    Point normalize() {
        int g = gcd(std::abs(x), gcd(std::abs(y), std::abs(z)));
        return Point(x / g, y / g, z / g);
    }

    Point negate() {
        return Point(-x, -y, -z);
    }

    int x, y, z;
};

Point operator - (Point a, const Point &b) {
    return a -= b;
}

long long dot(const Point &a, const Point &b) {
    return (long long)a.x * b.x + (long long)a.y * b.y + (long long)a.z * b.z;
}

bool operator < (const Point &a, const Point &b) {
    if (a.x != b.x) {
        return a.x < b.x;
    }
    if (a.y != b.y) {
        return a.y < b.y;
    }
    return a.z < b.z;
}


int n, m, result[N + 1];
Point a[N], b[N];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) {
        scanf("%d%d%d", &a[i].x, &a[i].y, &a[i].z);
    }
    scanf("%d", &m);
    for (int i = 0; i < m; ++ i) {
        scanf("%d%d%d", &b[i].x, &b[i].y, &b[i].z);
    }
    std::map <Point, int> count;
    for (int i = 0; i < n; ++ i) {
        std::set <Point> opposite;
        std::map <Point, std::vector <long long>> events;
        for (int j = 0; j < n + m; ++ j) {
            if (i == j) {
                continue;
            }
            const Point &p = j < n ? a[j] : b[j - n];
            Point d = (p - a[i]).normalize();
            if (j < n) {
                opposite.insert(d.negate());
            }
            long long dd = dot(d, p - a[i]);
            if (dd > 0) {
                events[d].push_back(dd * 2 + (j >= n));
            }
        }
        for (auto &iterator : events) {
            if (!opposite.count(iterator.first)) {
                std::vector <long long> &events = iterator.second;
                std::sort(events.begin(), events.end());
                int delta = 1;
                for (long long event : events) {
                    if (event & 1) {
                        if (delta) {
                            delta --;
                            count[iterator.first] ++;
                        }
                    } else {
                        delta ++;
                    }
                }
            }
        }
    }
    for (auto &iterator : count) {
        result[iterator.second] ++;
    }
    for (int k = 1; k <= N; ++ k) {
        if (result[k]) {
            printf("%d %d\n", k, result[k]);
        }
    }
    return 0;
}
