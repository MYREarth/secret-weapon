#include<map>
#include<queue>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int k, n;

int stcnt;

void minimize(vector<int> &con) {
    int mem[5], cnt = 0;
    memset(mem, -1, sizeof(mem));
    for (int i = 0; i < (int)con.size(); ++i) {
        if (mem[con[i]] == -1) {
            mem[con[i]] = cnt++;
        }
        con[i] = mem[con[i]];
    }
}

map<pair<vector<int>, vector<int> >, int > compress;

const int M = 320, MOD = 1000000007;

struct Matrix {
    int num[M][M];

    Matrix(int tag = 0) {
        memset(num, 0, sizeof(num));
        if (tag) {
            for (int i = 0; i < M; ++i) {
                num[i][i] = 1;
            }
        }
    }

    int* operator [] (int i) {
        return num[i];
    }

    const int* operator [] (int i) const {
        return num[i];
    }
};

Matrix operator * (const Matrix &a, const Matrix &b) {
    Matrix ret;
    for (int i = 0; i < stcnt; ++i) {
        for (int j = 0; j < stcnt; ++j) {
            long long tmp = 0;
            for (int k = 0; k < stcnt; ++k) {
                (tmp += (long long)a[i][k] * b[k][j] % MOD);
            }
            ret[i][j] = tmp % MOD;
        }
    }
    return ret;
}

vector<int> operator * (const vector<int> &a, const Matrix &b) {
    int m = a.size();
    vector<int> ret(m);
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < m; ++j) {
            (ret[j] += (long long)a[i] * b[i][j] % MOD) %= MOD;
        }
    }
    return ret;
}

int operator * (const vector<int> &a, const vector<int> &b) {
    int ret = 0, m = a.size();
    for (int i = 0; i < m; ++i) {
        (ret += (long long)a[i] * b[i] % MOD) %= MOD;
    }
    return ret;
}

bool isfinal (vector<int> a) {
    for (int i = 0; i < (int)a.size(); ++i) {
        if (a[i] != a[0]) {
            return false;
        }
    }
    return true;
}

bool isvalid(const vector<int> &con, const vector<int> &dgr) {
    for (int j = 1; j < (int)con.size(); ++j) {
        if (con[j] == con[0]) {
            return true;
        }
    }
    return false;
}

vector<int> v, w;
queue<pair<vector<int>, vector<int> > > q;

int getID(const pair<vector<int>, vector<int> > &a) {
    if (!compress.count(a)) {
        compress[a] = stcnt++;
        v.push_back(0);
        w.push_back(isfinal(a.first));
        q.push(a);
    }
    return compress[a];
}

int main() {
    scanf("%d%d", &k, &n);
    if (k >= n) {
        int ans = 1;
        for (int i = 1; i <= n; ++i) {
            ans *= i;
        }
        printf("%d\n", ans);
        return 0;
    }
    int m = k * (k - 1) / 2;
    stcnt = 0;
    for (int st = 0; st < (1 << m); ++st) {
        vector<int> con(k), dgr(k);
        for (int u = 0; u < k; ++u) {
            con[u] = u;
        }
        int cnt = 0;
        bool use = true;
        for (int u = 0; u < k; ++u) {
            for (int v = u + 1; v < k; ++v) {
                if (st >> cnt & 1) {
                    ++dgr[u], ++dgr[v];
                    int old = max(con[u], con[v]), news = min(con[u], con[v]);
                    if (old == news) {
                        use = false;
                    }
                    for (int j = 0; j < k; ++j) {
                        if (con[j] == old) {
                            con[j] = news;
                        }
                    }
                }
                ++cnt;
            }
        }
        for (int u = 0; u < k; ++u) {
            if (dgr[u] > 2) {
                use = false;
            }
        }
        if (!use) {
            continue;
        }
        minimize(con);
        if (compress.count(make_pair(con, dgr))) {
            ++v[compress[make_pair(con, dgr)]];
        } else {
            compress[make_pair(con, dgr)] = stcnt++;
            q.push(make_pair(con, dgr));
            v.push_back(1);
            w.push_back(isfinal(con));
        }
    }
    Matrix a(1), f;
    while (q.size()) {
        map<pair<vector<int>, vector<int> >, int>::iterator it = compress.find(q.front());
        q.pop();
        vector<int> con = it->first.first, dgr = it->first.second;
        vector<int> ncon, ndgr;

        ncon = con, ncon.push_back(k);
        ndgr = dgr, ndgr.push_back(0);
        if (isvalid(ncon, ndgr)) {
            ncon.erase(ncon.begin());
            ndgr.erase(ndgr.begin());
            minimize(ncon);
            ++f[it->second][getID(make_pair(ncon, ndgr))];
        }

        for (int i = 0; i < (int)con.size(); ++i) {
            if (dgr[i] == 2) {
                continue;
            }
            ncon = con, ncon.push_back(con[i]);
            ndgr = dgr, ndgr.push_back(1), ++ndgr[i];
            if (isvalid(ncon, ndgr)) {
                ncon.erase(ncon.begin());
                ndgr.erase(ndgr.begin());
                minimize(ncon);
                ++f[it->second][getID(make_pair(ncon, ndgr))];
            }
        }

        for (int i = 0; i < (int)con.size(); ++i) {
            for (int j = i + 1; j < (int)con.size(); ++j) {
                if (dgr[i] == 2 || dgr[j] == 2 || con[i] == con[j]) {
                    continue;
                }
                ncon = con, ncon.push_back(con[i]);
                int old = con[j], news = con[i];
                for (int k = 0; k < (int)ncon.size(); ++k) {
                    if (ncon[k] == old) {
                        ncon[k] = news;
                    }
                }
                ndgr = dgr, ndgr.push_back(2), ++ndgr[i], ++ndgr[j];
                if (isvalid(ncon, ndgr)) {
                    ncon.erase(ncon.begin());
                    ndgr.erase(ndgr.begin());
                    minimize(ncon);
                    ++f[it->second][getID(make_pair(ncon, ndgr))];
                }
            }
        }
    }
/*
for (int i = 0; i < stcnt; ++i) {
    cout << "st" << ' ' << v[i] << endl;
}
for (int i = 0; i < stcnt; ++i) {
    cout << "fi" << ' ' << w[i] << endl;
}
for (int i = 0; i < stcnt; ++i) {
    for (int j = 0; j < stcnt; ++j) {
        cout << f[i][j] << ' ' ;
    }
    cout << endl;
}
for (map<pair<vector<int>, vector<int> >, int> :: iterator it = compress.begin(); it != compress.end(); ++it) {
    for (int i = 0; i < k; ++i) {
        cout << (it->first.first[i]) << ' ' ;
    }
    cout << endl;
    for (int i = 0; i < k; ++i) {
        cout << (it->first.second[i]) << ' ' ;
    }
    cout << endl;
    cout << it->second << endl;
}
*/
    n -= k;
    while (n) {
        if (n & 1) {
            a = a * f;
        }
        f = f * f;
        n >>= 1;
    }
    printf("%d\n", v * a * w * 2 % MOD);
    return 0;
}
