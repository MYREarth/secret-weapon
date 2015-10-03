#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

#define ALL(v) (v).begin(), (v).end()

const int N = 50000;
const int INF = (int)1e9 + 1;

int permutation[3];

struct Point {
    Point() {}
    Point(int x, int y) : x(x), y(y) {}

    void rotate(int count = 1) {
        while (count --) {
            std::swap(x, y);
            x *= -1;
        }
    }

    int type() const {
        return permutation[c];
    }

    int x, y, c;
};

bool operator < (const Point &a, const Point &b) {
    if (a.x != b.x) {
        return a.x < b.x;
    }
    return a.type() < b.type();
}

Point points[N];

int delta[N << 1];
std::pair <int, int> maximum[N << 1];

int get_id(int l, int r) {
    return l + r | l != r;
}

void rebuild(int l, int r) {
    int id = get_id(l, r);
    delta[id] = 0;
    maximum[id] = std::make_pair(0, l);
    if (l < r) {
        int m = l + r >> 1;
        rebuild(l, m);
        rebuild(m + 1, r);
    }
}

void add(int l, int r, int a, int b, int c) {
    if (b < l || r < a) {
        return ;
    }
    int id = get_id(l, r);
    if (a <= l && r <= b) {
        delta[id] += c;
        maximum[id].first += c;
    } else {
        int m = l + r >> 1;
        add(l, m, a, b, c);
        add(m + 1, r, a, b, c);
        maximum[id] = std::max(maximum[get_id(l, m)], maximum[get_id(m + 1, r)]);
        maximum[id].first += delta[id];
    }
}

int solution[3][4];

void gao(int rotate, int type, int x0, int x1, int y0, int y1) {
    int color = 0;
    while (permutation[color] != type) {
        color ++;
    }
    {
        Point p(x0, y0);
        for (int i = rotate; i < 4; ++ i) {
            p.rotate();
        }
        solution[color][0] = p.x;
        solution[color][2] = p.y;
    }
    {
        Point p(x1, y1);
        for (int i = rotate; i < 4; ++ i) {
            p.rotate();
        }
        solution[color][1] = p.x;
        solution[color][3] = p.y;
    }
    std::sort(solution[color], solution[color] + 2);
    std::sort(solution[color] + 2, solution[color] + 4);
}

int get(const std::vector <int> &values, int value) {
    if (value == -INF) {
        return -INF;
    }
    if (value == +INF) {
        return INF;
    }
    return values[value];
}

int main() {
    freopen("gold.in", "r", stdin);
    freopen("gold.out", "w", stdout);
    int n;
    while (scanf("%d", &n) == 1 && n) {
        for (int i = 0; i < n; ++ i) {
            scanf("%d%d%d", &points[i].x, &points[i].y, &points[i].c);
        }
        for (int i = 0; i < 3; ++ i) {
            permutation[i] = i;
        }
        int best = -1;
        do {
            for (int _ = 0; _ < 4; ++ _) {
                std::vector <int> xvalues, yvalues;
                for (int i = 0; i < n; ++ i) {
                    xvalues.push_back(points[i].x);
                    yvalues.push_back(points[i].y);
                }
                std::sort(ALL(xvalues));
                xvalues.erase(std::unique(ALL(xvalues)), xvalues.end());
                std::sort(ALL(yvalues));
                yvalues.erase(std::unique(ALL(yvalues)), yvalues.end());
                std::sort(points, points + n);
                int suffix_sum = 0;
                for (int i = 0; i < n; ++ i) {
                    suffix_sum += points[i].type() == 2;
                }
                int backup = suffix_sum;
                int m = yvalues.size() - 1;
                rebuild(0, m);
                int root = get_id(0, m);
                for (int i = 0; i < n; ++ i) {
                    const Point &p = points[i];
                    if (maximum[root].first + suffix_sum > best) {
                        best = maximum[root].first + suffix_sum;
                        int y = yvalues[maximum[root].second];
                        gao(_, 0, -INF, p.x, -INF, y);
                        gao(_, 1, -INF, p.x, y, +INF);
                        gao(_, 2, p.x, +INF, -INF, +INF);
                    }
                    suffix_sum -= p.type() == 2;
                    int y = std::lower_bound(ALL(yvalues), p.y) - yvalues.begin();
                    if (p.type() == 0) {
                        add(0, m, y, m, 1);
                    }
                    if (p.type() == 1) {
                        add(0, m, 0, y, 1);
                    }
                }
                if (_ < 2) {
                    m = xvalues.size() - 1;
                    rebuild(0, m);
                    root = get_id(0, m);
                    suffix_sum = backup;
                    for (int i = 0; i < n; ) {
                        int j = i;
                        while (j < n && points[i].x == points[j].x) {
                            const Point &p = points[j];
                            if (maximum[root].first + suffix_sum > best) {
                                best = maximum[root].first + suffix_sum;
                                int x = xvalues[maximum[root].second];
                                gao(_, 0, -INF, x, -INF, INF);
                                gao(_, 1, x, p.x, -INF, +INF);
                                gao(_, 2, p.x, +INF, -INF, +INF);
                            }
                            suffix_sum -= p.type() == 2;
                            j ++;
                        }
                        for (int k = i; k < j; ++ k) {
                            const Point &p = points[k];
                            int x = std::lower_bound(ALL(xvalues), p.x) - xvalues.begin();
                            if (p.type() == 0) {
                                add(0, m, x, m, 1);
                            }
                            if (p.type() == 1) {
                                add(0, m, 0, x, 1);
                            }
                        }
                        i = j;
                    }
                }
                for (int i = 0; i < n; ++ i) {
                    points[i].rotate();
                }
            }
        } while (std::next_permutation(permutation, permutation + 3));
        printf("%d\n", best);
        for (int i = 0; i < 3; ++ i) {
            printf("%d %d %d %d\n", solution[i][0], solution[i][2], solution[i][1], solution[i][3]);
        }
    }
    return 0;
}
