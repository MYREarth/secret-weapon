#include<cmath>
#include<vector>
#include<cstdio>
#include<complex>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 200005;

int n;

vector<int> edge[N];

void addedge(int u, int v) {
    edge[u].push_back(v);
}

const int L = 530000;

int ans, cnt[L];
bool use[N];

void update(int top) {
    for (int i = 1; i <= top && i <= n; ++i) {
        if (!use[i] && cnt[i]) {
            use[i] = true;
            ++ans;
        }
        cnt[i] = 0;
    }
}

bool block[N];

int vis[N], stamp, dep[N], size[N], maxch[N], fa[N];

int getroot(int u) {
    ++stamp;
    vector<int> q;
    q.push_back(u);
    dep[u] = 1;
    vis[u] = stamp;
    fa[u] = -1;
    maxch[u] = 0;
    for (int i = 0; i < (int)q.size(); ++i) {
        int u = q[i];
        for (int j = 0; j < (int)edge[u].size(); ++j) {
            int v = edge[u][j];
            if (block[v] || vis[v] == stamp) {
                continue;
            }
            dep[v] = dep[u] + 1;
            vis[v] = stamp;
            fa[v] = u;
            maxch[v] = 0;
            q.push_back(v);
        }
    }
    if (q.size() == 1) {
        return u;
    }
    for (int i = (int)q.size() - 1; i >= 0; --i) {
        int u = q[i];
        ++size[u];
        if (fa[u] != -1) {
            size[fa[u]] += size[u];
            maxch[fa[u]] = max(maxch[fa[u]], size[u]);
        }
    }
    int all = size[u], cen = u;
    for (int i = 0; i < (int)q.size(); ++i) {
        int u = q[i];
        maxch[u] = max(maxch[u], all - size[u]);
        if (maxch[u] < maxch[cen]) {
            cen = u;
        }
    }
    for (int i = 0; i < (int)q.size(); ++ i) {
        size[q[i]] = 0;
    }
    return cen;
}

typedef complex<double> Complex;

void sincos2(double ang, double &y, double &x) {
    x = cos(ang), y = sin(ang);
}

const double pi = acos(-1);

void FFT(Complex p[], int n, int oper) {
    for (int i = 1, j = 0; i < n - 1; ++i) {
        for (int s = n; j ^= s >>= 1, ~j & s;);
        if (i < j) {
            swap(p[i], p[j]);
        }
    }
    Complex unit_p0;
    for (int d = 0; (1 << d) < n; ++d) {
        int m = 1 << d, m2 = m * 2;
        double p0 = pi / m * oper;
        double x, y;
        sincos2(p0, y, x);
        unit_p0 = Complex(x, y);
        for (int i = 0; i < n; i += m2) {
            Complex unit = 1;
            for (int j = 0; j < m; ++j) {
                Complex &P1 = p[i + j + m], &P2 = p[i + j];
                Complex t = unit * P1;
                P1 = P2 - t;
                P2 = P2 + t;
                unit = unit * unit_p0;
            }
        }
    }
}

Complex a[L], b[L], c[L];

void cross(const vector<int> &aa, int delta) {
    int top = 0;
    for (int i = 0; i < (int)aa.size(); ++i) {
        top = max(top, aa[i]);
    }
    ++top;

    int n = 1;
    while (n < 2 * top) {
        n <<= 1;
    }
//printf("%d\n", n);
    for (int i = 0; i < n; ++i) {
        a[i] = Complex(0, 0);
//b[i] = Complex(0, 0);
    }
    for (int i = 0; i < (int)aa.size(); ++i) {
        a[aa[i]] += Complex(1, 0);
    }
    //for (int i = 0; i < (int)bb.size(); ++i) {
    //    b[bb[i]] += Complex(1, 0);
    //}
    FFT(a, n, 1);
    //FFT(b, n, 1);
    for (int i = 0; i < n; ++i) {
        c[i] = a[i] * a[i];
    }
    FFT(c, n, -1);
    for (int i = 0; i < n; ++i) {
        cnt[i] += (int)(c[i].real() / n + 0.5) * delta;
    }
}

vector<int> tmp;

void dfs(int u, int fa, int dep) {
    if (edge[u].size() == 1) {
        tmp.push_back(dep);
        return ;
    }
    for (int j = 0; j < (int)edge[u].size(); ++j) {
        int v = edge[u][j];
        if (v == fa || block[v]) {
            continue;
        }
        dfs(v, u, dep + 1);
    }
}

void solve(int u) {
    u = getroot(u);
    block[u] = true;
    vector<int> ret;
    if (edge[u].size() == 1) {
        ret.push_back(0);
    }
    for (int i = 0; i < (int)edge[u].size(); ++i) {
        int v = edge[u][i];
        if (!block[v]) {
            tmp.clear();
            dfs(v, u, 1);
            if (tmp.size() == 0) {
                continue;
            }
            for (int j = 0; j < (int)tmp.size(); ++j) {
                ret.push_back(tmp[j]);
            }
            cross(tmp, -1);
        }
    }
    if (ret.size() == 0) {
        return;
    }
    cross(ret, 1);
    sort(ret.begin(), ret.end());
    update(ret.back() * 2);
    for (int i = 0; i < (int)edge[u].size(); ++i) {
        int v = edge[u][i];
        if (!block[v]) {
            solve(v);
        }
    }
    return ;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        --u, --v;
        addedge(u, v);
        addedge(v, u);
    }
    solve(0);
    printf("%d\n", ans);
    for (int i = 1; i <= n; ++i) {
        if (use[i]) {
            printf("%d\n", i);
        }
    }
    return 0;
}
