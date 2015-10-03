#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>

struct Point {
    double x, y, z;

    Point() {}
    Point(double x, double y, double z) : x(x), y(y), z(z) {}

    Point &operator +=(const Point &o) {
        x += o.x, y += o.y, z += o.z;
        return *this;
    }

    Point &operator -=(const Point &o) {
        x -= o.x, y -= o.y, z -= o.z;
        return *this;
    }

    Point &operator *=(double k) {
        x *= k, y *= k, z *= k;
        return *this;
    }

    Point &operator /=(double k) {
        x /= k, y /= k, z /= k;
        return *this;
    }

    double norm() const {
        return sqrt(x * x + y * y + z * z);
    }

    Point normalize() const;

    Point project(const Point &a, const Point &b) const;
};

std::istream &operator >>(std::istream &in, Point &p) {
    return in >> p.x >> p.y >> p.z;
}

Point operator +(Point a, const Point &b) {
    return a += b;
}

Point operator -(Point a, const Point &b) {
    return a -= b;
}

Point operator *(Point a, double k) {
    return a *= k;
}

Point operator *(double k, Point a) {
    return a *= k;
}

Point operator /(Point a, double k) {
    return a /= k;
}

Point det(const Point &a, const Point &b) {
    return Point(a.y * b.z - a.z * b.y,
                 a.z * b.x - a.x * b.z,
                 a.x * b.y - a.y * b.x);
}

double dot(const Point &a, const Point &b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Point Point::project(const Point &a, const Point &b) const {
    const Point &p = *this;
    return a + (b - a) * dot(p - a, b - a) / dot(b - a, b - a);
}

Point Point::normalize() const {
    return *this / this->norm();
}

int main() {
    freopen("planet.in", "r", stdin);
    freopen("planet.out", "w", stdout);
    Point o, a, b;
    double r;
    std::cin >> o >> r >> a >> b;
    a -= o;
    b += a;
    o -= o;
    Point oo = o.project(a, b);
    double x = r * r / oo.norm();
    double y = sqrt(r * r - x * x);
    Point x_axis = oo.normalize();
    Point y_axis = det(b - a, oo).normalize();
    Point n = (x * x_axis + y * y_axis).normalize();
    printf("%.8f %.8f %.8f\n", n.x, n.y, n.z);
    return 0;
}
