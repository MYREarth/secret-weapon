#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 100000;
const long long INF = 1000000000000000001LL;

struct Exam {
    //Exam() {}
    //Exam(int id, int p, long long d) : id(id), p(p), d(d) {}

    int id, p, pos;
    long long d;
};

bool operator < (const Exam &a, const Exam &b) {
    return a.d < b.d;
}

struct Expedition {
    //Expedition() {}
    //Expedition(long long s, long long t) : s(s), t(t) {}

    long long duration() const {
        return t - s + 1;
    }

    long long s, t;
};

bool operator < (const Expedition &a, const Expedition &b) {
    return a.t < b.t;
}

int n, m, order[N];
Exam exams[N];
Expedition expeditions[N];

bool compare(const Exam &a, const Exam &b) {
    if (a.p != b.p) {
        return a.p < b.p;
    }
    return a.d > b.d;
}

long long delta[N << 1], minimum[N << 1];

int get_id(int l, int r) {
    return l + r | l != r;
}

void add(int l, int r, int a, int b, long long v) {
    if (b < l || r < a) {
        return;
    }
    int id = get_id(l, r);
    if (a <= l && r <= b) {
        delta[id] += v;
        minimum[id] += v;
    } else {
        int m = l + r >> 1;
        add(l, m, a, b, v);
        add(m + 1, r, a, b, v);
        minimum[id] = std::min(minimum[get_id(l, m)], minimum[get_id(m + 1, r)]) + delta[id];
    }
}

int main() {
    freopen("intelligent.in", "r", stdin);
    freopen("intelligent.out", "w", stdout);
    while (scanf("%d", &n) == 1 && n) {
        for (int i = 0; i < n; ++ i) {
            exams[i].id = i;
            scanf("%lld%d", &exams[i].d, &exams[i].p);
            exams[i].p ++;
        }
        std::sort(exams, exams + n);
        for (int i = 0; i < n; ++ i) {
            exams[i].pos = i;
        }
        scanf("%d", &m);
        for (int i = 0; i < m; ++ i) {
            scanf("%lld%lld", &expeditions[i].s, &expeditions[i].t);
        }
        std::sort(expeditions, expeditions + m);
        if (true) {
            long long delta = 0;
            for (int i = 0, j = 0; i < n; ++ i) {
                while (j < m && expeditions[j].t <= exams[i].d) {
                    delta += expeditions[j ++].duration();
                }
                exams[i].d -= delta;
            }
        }
        std::sort(exams, exams + n, compare);
        int root = get_id(0, n - 1);
        memset(minimum, 0, sizeof(long long) * (n << 1));
        memset(delta,   0, sizeof(long long) * (n << 1));
        for (int i = 0; i < n; ++ i) {
            const Exam &e = exams[i];
            add(0, n - 1, e.pos, e.pos, e.d + INF);
        }
        std::vector <int> result;
        for (int i = 0; i < n; ++ i) {
            const Exam &e = exams[i];
            add(0, n - 1, e.pos, n - 1, -e.p);
            add(0, n - 1, e.pos, e.pos, -INF);
            if (minimum[root] < 0) {
                add(0, n - 1, e.pos, n - 1, e.p);
                add(0, n - 1, e.pos, e.pos, INF);
            } else {
                result.push_back(e.id);
            }
        }
        printf("%d\n", (int)result.size());
        std::sort(result.begin(), result.end());
        for (int i = 0; i < (int)result.size(); ++ i) {
            printf("%d%c", result[i] + 1, " \n"[i == (int)result.size() - 1]);
        }
    }
    return 0;
}
