#include<cstdio>
#include<cassert>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int pn;

const int M = 1000;

struct Point {
    double x, y;

    Point(double x = 0, double y = 0) : x(x), y(y) {}
};

int signum(double x, double eps = 1e-8) {
    return x < -eps ? -1 : x > eps;
}

double det(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

Point operator + (Point a, Point b) {
    return Point(a.x + b.x, a.y + b.y);
}

Point operator - (Point a, Point b) {
    return Point(a.x - b.x, a.y - b.y);
}

Point operator * (Point a, double k) {
    return Point(a.x * k, a.y * k);
}

Point operator / (Point a, double k) {
    return Point(a.x / k, a.y / k);
}

Point points[M], newPoints[M], p[6];

void rebuild(const Point &a, const Point &b) {
    points[pn] = points[0];
    int m = 0;
    for (int i = 0; i < pn; ++i) {
        double s_1 = det(b - a, points[i] - a);
        double s_2 = det(b - a, points[i + 1] - a);
        if (signum(s_1) * signum(s_2) < 0) {
            newPoints[m++] = (points[i] * s_2 - points[i + 1] * s_1) / (s_2 - s_1);
        }
        if (signum(det(b - a, points[i + 1] - a)) >= 0) {
            newPoints[m++] = points[i + 1];
        }
    }
    pn = m;
    for (int i = 0; i < pn; ++i) {
        points[i] = newPoints[i];
    }
}

Point A, B, C;

void prepare() {
    pn = 3;
    points[0] = A, points[1] = B, points[2] = C;
}

const int N = 6;

int n, a[N], b[N], c[N], lq[4][N];
double angle[N];

bool cmp(int x,int y)
{
    return(angle[x]<angle[y]);
}

bool check()
{
    Point P[3];
    P[0]=Point(0,0);
    P[1]=Point(20000,0);
    P[2]=Point(0,20000);
    for (int i=0;i<3;i++)
    {
        for (int j=1;j<=n;j++)
        {
            lq[3][j]=j;
            angle[j]=atan2(p[j-1].y-P[i].y,p[j-1].x-P[i].x);
        }
        sort(lq[3]+1,lq[3]+n+1,cmp);
        for (int j=1;j<=n;j++)
            printf("%d ",lq[3][j]);
        printf("[%d %.10f %.10f]\n",i,angle[2],angle[4]);
        for (int j=1;j<=n;j++)
            if (lq[i][j]!=lq[3][j])
                return(false);
    }
    return(true);
}

int ord[N];

bool by_a(int i, int j) {
    return a[i] < a[j];
}

int main() {
    A = Point(0, 0), B = Point(20000, 0), C = Point(0, 20000);
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        int u;
        scanf("%d", &u);
        lq[0][i+1]=u;
        a[--u] = i;
    }
    for (int i = 0; i < n; ++i) {
        int u;
        scanf("%d", &u);
        lq[1][i+1]=u;
        b[--u] = i;
    }
    for (int i = 0; i < n; ++i) {
        int u;
        scanf("%d", &u);
        lq[2][i+1]=u;
        c[--u] = i;
    }
    for (int i = 0; i < n; ++i) {
        ord[i] = i;
    }
    sort(ord, ord + n, by_a);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) {
                continue;
            }
            if (a[i] < a[j] && b[i] < b[j] && c[i] < c[j]) {
                printf("NO\n");
                return 0;
            }
        }
    }
    for (int _ = 0; _ < n; ++_) {
        int i = ord[_];
        prepare();
        for (int __ = 0; __ < _; ++__) {
            int j = ord[__];
            if (a[j] < a[i]) {
                rebuild(A, p[j]);
            } else {
                rebuild(p[j], A);
            }
            if (b[j] < b[i]) {
                rebuild(B, p[j]);
            } else {
                rebuild(p[j], B);
            }
            if (c[j] < c[i]) {
                rebuild(C, p[j]);
            } else {
                rebuild(p[j], C);
            }
        }
        double area = 0;
        p[i] = Point(0, 0);
        double sum = 0;
        points[pn] = points[0];
        for (int j = 0; j < pn; ++j) {
//cout << "PP" << j << ' ' << points[j].x << ' ' << points[j].y << endl;
            area += det(points[j], points[j + 1]);
            p[i] = p[i] + points[j];
            sum += 1;
            if (_ != 0 && det(p[ord[_ - 1]], points[j]) < 0) {
                int k = rand() % 10 + 1;
                p[i] = p[i] + (points[j] * k);
                sum += k;
            }
        }
//cout << "SUM" << ' ' << sum << endl;
//cout << "P" << ' ' << i << ' ' << p[i].x << ' ' << p[i].y << endl;
//cout << pn << endl;
//        cout << i << ' ' << fabs(area) << endl;
        p[i] = p[i] / sum;
    }
    printf("YES\n");
    for (int i = 0; i < n; ++i) {
        printf("%.12f %.12f\n", p[i].x, p[i].y);
    }
    assert(check());
    return 0;
}

