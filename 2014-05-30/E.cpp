#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 105;

long long n, s, a[N];

long long lb[N], ub[N];

long long l, u;

#define left LEFT

long long left;

long long now[N];

struct Frac {
    long long a, b;

    Frac(long long a = 0) : a(a), b(1) {}

    Frac(long long a, long long b) : a(a), b(b) {
        long long g = __gcd(llabs(a), llabs(b));
        this->a /= g, this->b /= g;
    }
};

Frac operator + (const Frac &a, const Frac &b) {
    return Frac(a.a * b.b + a.b * b.a, a.b * b.b);
}

Frac operator - (const Frac &a, const Frac &b) {
    return Frac(a.a * b.b - a.b * b.a, a.b * b.b);
}

Frac operator / (const Frac &a, const Frac &b) {
    return Frac(a.a * b.b, a.b * b.a);
}

bool operator < (const Frac &a, const Frac &b) {
    return(long double)a.a/a.b<(long double)b.a/b.b;
}

bool operator > (const Frac &a, const Frac &b) {
    return(b<a);
}

Frac b[N];

void phase0() {
    for (int i = 0; i < n; ++i) {
        now[i] = l, left -= l;
    }
}

const long long INF = 1ll << 60;

void phase1() {
    while (left > 0) {
        long long num = 0, best = -INF, sbest = -INF;
        for (int i = 0; i < n; ++i) {
            if (now[i] >= lb[i] || now[i] == u) {
                continue;
            }
            if (lb[i] - now[i] > best) {
                sbest = best;
                best = lb[i] - now[i];
                num = 1;
            } else if (lb[i] - now[i] == best) {
                ++num;
            } else if (lb[i] - now[i] > sbest) {
                sbest = lb[i] - now[i];
            }
        }
        if (best == -INF) {
            return;
        }
        if (left <= num) {
            while (left) {
                int best = -1;
                for (int i = 0; i < n; ++i) {
                    if (now[i] >= lb[i] || now[i] == u) {
                        continue;
                    }
                    if (best == -1 || b[i] - now[i] > b[best] - now[best]) {
                        best = i;
                    }
                }
                if (best == -1) {
                    break;
                }
                ++now[best];
                left--;
            }
            return;
        } else {
            long long delta = min(left / num, best - sbest);
            for (int i = 0; i < n; ++i) {
                if (now[i] >= lb[i] || now[i] == u) {
                    continue;
                }
                if (lb[i] - now[i] == best) {
                    delta = min(delta, min(u, lb[i]) - now[i]);
                }
            }
            for (int i = 0; i < n; ++i) {
                if (now[i] >= lb[i] || now[i] == u) {
                    continue;
                }
                if (lb[i] - now[i] == best) {
                    now[i] += delta;
                }
            }
            left -= delta * num;
        }
    }
}

void phase2() {
    while (left > 0) {
        int best = -1;
        for (int i = 0; i < n; ++i) {
            if (now[i] >= ub[i] || now[i] == u) {
                continue;
            }
            if (best == -1 || b[i] - now[i] > b[best] - now[best]) {
                best = i;
            }
        }
        if (best == -1) {
            return;
        }
        ++now[best];
        --left;
    }
}

void phase3() {
    while (left > 0) {
        long long num = 0, best = INF, sbest = INF;
        for (int i = 0; i < n; ++i) {
            if (now[i] == u) {
                continue;
            }
            if (now[i] - ub[i] < best) {
                sbest = best;
                best = now[i] - ub[i];
                num = 1;
            } else if (now[i] - ub[i] == best) {
                ++num;
            } else if (now[i] - ub[i] < sbest) {
                sbest = now[i] - ub[i];
            }
        }
        if (best == INF) {
            return;
        }
        if (left <= num) {
            while (left) {
                int best = -1;
                for (int i = 0; i < n; ++i) {
                    if (now[i] == u) {
                        continue;
                    }
                    if (best == -1 || now[i] - b[i] < now[best] - b[best]) {
                        best = i;
                    }
                }
                if (best == -1) {
                    break;
                }
                ++now[best];
                left--;
            }
            return;
        } else {
            long long delta = min(left / num, sbest - best);
            for (int i = 0; i < n; ++i) {
                if (now[i] == u) {
                    continue;
                }
                if (now[i] - ub[i] == best) {
                    delta = min(delta, u - now[i]);
                }
            }
            for (int i = 0; i < n; ++i) {
                if (now[i] == u) {
                    continue;
                }
                if (now[i] - ub[i] == best) {
                    now[i] += delta;
                }
            }
            left -= delta * num;
        }
    }
}

int main() {
    freopen("exam.in", "r", stdin);
    freopen("exam.out", "w", stdout);
    while (scanf("%lld%lld", &n, &s) == 2 && n) {
        Frac sum(s), div(0);
        for (int i = 0; i < n; ++i) {
            scanf("%lld", a + i);
            div = div + Frac(1, a[i]);
        }
        Frac c = sum / div;
        for (int i = 0; i < n; ++i) {
            b[i] = Frac(c.a, c.b * a[i]);
            ub[i] = (b[i].a + b[i].b - 1) / b[i].b;
            lb[i] = b[i].a / b[i].b;
        }
        scanf("%lld%lld", &l, &u);
        left = s;
        phase0();
        phase1();
        phase2();
        phase3();
        //printf("%lld %lld\n", n, s);
        //for (int i = 0; i < n; ++ i) {
        //    printf("%lld%c", a[i], " \n"[i == n - 1]);
        //}
        //printf("%lld %lld\n", l, u);
        for (int i = 0; i < n; ++i) {
            printf("%lld%c", now[i], i == n - 1 ? '\n' : ' ');
        }
    }
    //puts("0 0");
    return 0;
}
