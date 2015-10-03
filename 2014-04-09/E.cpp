#include <cstdio>
#include <cstring>
#include <iostream>

struct Point {
    int x, y;

    Point() : x(0), y(0) {}
    Point(int x, int y) : x(x), y(y) {}

    Point &operator -=(const Point &o) {
        x -= o.x;
        y -= o.y;
        return *this;
    }
};

long long det(const Point &a, const Point &b) {
    return (long long)a.x * b.y - (long long)a.y * b.x;
}

Point operator -(Point a, const Point &b) {
    return a -= b;
}

const int N = 20000;

int n;
Point points[N];

long long find(int i, int j) {
    int low = j;
    int high = n;
    Point p = points[(i + j) % n] - points[i];
    while (low < high) {
        int middle = low + high >> 1;
        if (det(p, points[(i + middle + 1) % n] - points[(i + middle) % n]) < 0) {
            high = middle;
        } else {
            low = middle + 1;
        }
    }
    return det(p, points[(i + low) % n] - points[i]);
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    while (scanf("%d", &n) == 1 && n) {
        for (int i = 0; i < n; ++ i) {
            scanf("%d%d", &points[i].x, &points[i].y);
        }
        long long result = 0;
        for (int i = 0, j = 1; i < n; ++ i) {
            long long value = find(i, j);
            while (j + 2 < n) {
                long long new_value = find(i, j + 1);
                if (new_value >= value) {
                    j ++;
                    value = new_value;
                } else {
                    break;
                }
            }
            result = std::max(result, value);
            if (j > 1) {
                j --;
            }
        }
        std::cout << result << std::endl;
    }
    return 0;
}
