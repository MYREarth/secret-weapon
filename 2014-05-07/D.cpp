#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>

typedef long long Long;

const int N = 6400;

struct Point {
    Point() : x(0), y(0) {}
    Point(int x, int y) : x(x), y(y) {}

    int x, y;
};

long long det(const Point &a, const Point &b) {
    return (long long)a.x * b.y - (long long)a.y * b.x;
}

int n, m;
Long binom[N + 1][5];

int minX, maxX, minY, maxY, total, count[N + 1];
Point points[N + 1];

bool check(int x, int y) {
    return minX <= x && x < maxX && minY <= y && y < maxY;
}

void generate_ray(int dx, int dy) {
    count[total] = 0;
    points[total] = Point(dx, dy);
    for (int x = dx, y = dy; check(x, y); x += dx, y += dy) {
        count[total] ++;
    }
    if (count[total]) {
        total ++;
    }
}

void generate(int x0, int y0, int x1, int y1) {
    int x = x0 + x1;
    int y = y0 + y1;
    if (check(x, y)) {
        generate(x0, y0, x, y);
        generate_ray(x, y);
        generate(x, y, x1, y1);
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i <= n * m; ++ i) {
        binom[i][0] = 1;
        for (int j = 1; j <= 4; ++ j) {
            binom[i][j] = binom[i - 1][j - 1] + binom[i - 1][j];
        }
    }
    Long result = binom[n * m][4];
    for (int dx = 0; dx < n; ++ dx) {
        for (int dy = 0; dy < m; ++ dy) {
            if (dx || dy) {
                int d = std::__gcd(dx, dy);
                int scale = (1 + (dx && dy)) * (n - dx) * (m - dy);
                result -= (d - 1LL) * (n * m - 3) * scale;
                result += 3LL * binom[d - 1][2] * scale;
            }
        }
    }
    for (int x0 = 0; x0 < n; ++ x0) {
        for (int y0 = 0; y0 < m; ++ y0) {
            minX = -x0;
            minY = -y0;
            maxX = n - x0;
            maxY = m - y0;
            total = 0;
            generate(-1, 0, 0, -1);
            generate_ray(0, -1);
            generate(0, -1, 1, 0);
            generate_ray(1, 0);
            generate(1, 0, 0, 1);
            generate_ray(0, 1);
            generate(0, 1, -1, 0);
            generate_ray(-1, 0);
            result -= binom[n * m - 1][3];
            for (int i = 0, j = 0, plane = 0, line = 0; i < total; ++ i) {
                line = 0;
                while (j + 1 < total) {
                    int jj = (i + j + 1) % total;
                    int d = det(points[i], points[jj]);
                    if (d < 0) {
                        break;
                    }
                    plane += count[jj];
                    line = !d * count[jj];
                    j ++;
                }
                result += binom[count[i] + plane][3] - binom[plane][3];
                result -= count[i] * binom[line][2];
                if (j) {
                    plane -= count[(i + 1) % total];
                    j --;
                }
            }
        }
    }
    std::cout << result << std::endl;
    //std::cout << binom[n * m][4] - result << std::endl;
    return 0;
}
