#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

struct Event {
    int t;
    bool op;
    long double da, db;

    Event(int t = 0, bool op = false, long double da = 0, long double db = 0) : t(t), op(op), da(da), db(db) {}
};

bool operator < (const Event &a, const Event &b) {
    return a.t > b.t;
}

vector<Event> evt;

int process(bool op) {
    int n;
    scanf("%d", &n);
    int lx, lz, maxz;
    scanf("%d%d", &lx, &lz);
    maxz = lz;
    for (int i = 1; i < n; ++i) {
        int x, z;
        scanf("%d%d", &x, &z);
        maxz = max(maxz, z);
        if (z != lz) {
            long double dx = x - lx, dz = z - lz,
                        a = dx / dz, b = -lz * a + lx;
            evt.push_back(Event(z, op, a, b));
            evt.push_back(Event(lz, op, -a, -b));
        }
        lz = z, lx = x;
    }
    return maxz;
}

int main() {
    freopen("lonely.in", "r", stdin);
    freopen("lonely.out", "w", stdout);
    if (process(0) != process(1)) {
        printf("Invalid plan\n");
        return 0;
    }
    sort(evt.begin(), evt.end());
    long double ans = 0;
    long double fa = 0, fb = 0, ga = 0, gb = 0;
    for (int i = 0; i + 1 < evt.size(); ++i) {
        if (!evt[i].op) {
            fa += evt[i].da;
            fb += evt[i].db;
        } else {
            ga += evt[i].da;
            gb += evt[i].db;
        }
        long double lz = evt[i].t, z = evt[i + 1].t;
        long double a = fa * ga, b = fa * gb + ga * fb, c = fb * gb;
        ans += a / 3 * (lz * lz * lz - z * z * z) + b / 2 * (lz * lz - z * z) + c * (lz - z);
    }
    printf("%.12f\n", (double)ans);
    return 0;
}
