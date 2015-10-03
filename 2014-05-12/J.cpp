#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int n, m, k;

const int N = 32;
bool hole[N][N];

struct Vector {
    double us, uc, rs, rc,
           ds, dc, ls, lc,
           s;

    Vector(double us = 0, double uc = 0, double rs = 0, double rc = 0, double ds = 0, double dc = 0, double ls = 0, double lc = 0, double s = 0) :
        us(us), uc(uc), rs(rs), rc(rc), ds(ds), dc(dc), ls(ls), lc(lc), s(s) {};
};

bool vis[N][N][N][N];
Vector mem[N][N][N][N];

Vector solve(int u, int l, int d, int r) {
    if (vis[u][l][d][r]) {
        return mem[u][l][d][r];
    }
    vis[u][l][d][r] = true;
    Vector ret;
    vector<pair<int, int> > h;
    for (int i = u + 1; i < d; ++i) {
        for (int j = l + 1; j < r; ++j) {
            if (hole[i][j]) {
                h.push_back(make_pair(i, j));
            }
        }
    }
    int cnt = h.size();
    if (cnt == 0) {
        return mem[u][l][d][r] = ret;
    }
    for (int i = 0; i < cnt; ++i) {
        int x = h[i].first, y = h[i].second;
cout << "CONSIDER" << x << ' ' << y << endl;
        Vector ul = solve(u, l, x, y),
               ur = solve(u, y, x, r),
               dl = solve(x, l, d, y),
               dr = solve(x, y, d, r),
               cen = Vector(y, 1, x, 1, y, 1, x, 1, (r - l + d - u));
        ret.us += dr.lc * y + dr.ds + cen.us + ur.lc * y + ur.us;
        ret.uc += dr.lc     + dr.dc + cen.uc + ur.lc     + ur.uc;
        ret.rs += dl.uc * x + dl.ls + cen.rs + dr.uc * x + dr.rs;
        ret.rc += dl.uc     + dl.lc + cen.rc + dr.uc     + dr.rc;
        ret.ds += dl.ds + dl.rc * y + cen.ds + ul.us + ul.rc * y ;
        ret.dc += dl.dc + dl.rc     + cen.dc + ul.uc + ul.rc     ;
        ret.ls += ul.ls + ul.dc * x + cen.ls + ur.rs + ur.dc * x ;
        ret.lc += ul.lc + ul.dc     + cen.lc + ur.rc + ur.dc     ;
        ret.s += ul.rc * x - ul.rs + ul.rc * (y - l) + ul.ds - ul.dc * l;
        ret.s += ur.ls - ur.lc * u + ur.ds - ur.dc * x + ur.dc * (y - l);
        ret.s += dl.rc * d - dl.rs + dl.uc * y - dl.us + dl.uc * (d - x);
        ret.s += dr.ls - dr.lc * u + dr.uc * r - dr.us;
        ret.s += ul.s + ur.s + dl.s + dr.s + cen.s;
cout << u << ' ' << l << ' ' << d << ' ' << r << endl;
cout << ret.us << ' ' << ret.uc << endl;
cout << ret.rs << ' ' << ret.rc << endl;
cout << ret.ds << ' ' << ret.dc << endl;
cout << ret.ls << ' ' << ret.lc << endl;
cout << ret.s << endl;
cout << endl;
    }
    ret.us /= cnt, ret.uc /= cnt;
    ret.rs /= cnt, ret.rc /= cnt;
    ret.ds /= cnt, ret.dc /= cnt;
    ret.ls /= cnt, ret.lc /= cnt;
    ret.s /= cnt;
cout << "FINAL" << ' ' << u << ' ' << l << ' ' << d << ' ' << r << endl;
cout << ret.us << ' ' << ret.uc << endl;
cout << ret.rs << ' ' << ret.rc << endl;
cout << ret.ds << ' ' << ret.dc << endl;
cout << ret.ls << ' ' << ret.lc << endl;
cout << ret.s << endl;
cout << endl;
    return mem[u][l][d][r] = ret;
}

int main() {
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 0; i < k; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        hole[x][y] = true;
    }
    Vector ret = solve(0, 0, n, m);
    double ans = 0;
    ans += m * ret.uc - ret.us;
    ans += n * ret.rc - ret.rs;
    ans += ret.ds - 0 * ret.dc;
    ans += ret.ls - 0 * ret.lc;
    ans += ret.s;
    printf("%.12f\n", ans);
    return 0;
}
