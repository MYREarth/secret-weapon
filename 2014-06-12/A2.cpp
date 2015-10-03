#include<cassert>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int n;
const int N = 1000005, INF = 1000000000;
char a[N], b[N];

/*
vector<pair<int, int> > minimize(char *s) {
    vector<pair<int, int> > ret;
    int i = 0, j = n - 1 - 1;
    while (true) {
        while (i + 1 < n && !(s[i] == 'b' && s[i + 1] == 'a')) {
            ++i;
        }
        while (j >= 0 && !(s[j] == 'a' && s[j + 1] == 'b')) {
            --j;
        }
        if (i + 1 < j) {
            ret.push_back(make_pair(j + 1, i + 1));
            swap(s[j], s[j + 1]);
            swap(s[i], s[i + 1]);
            if (i > 0) {
                --i;
            }
            if (j < n - 2) {
                ++j;
            }
        } else {
            break;
        }
    }
    return ret;
}
*/

vector<int> make(char *s) {
    vector<int> ret;
    int last = -1;
    for (int j = 0; j < n; ++j) {
        if (s[j] == 'a') {
            ret.push_back(j - last - 1);
            last = j;
        }
    }
    ret.push_back(n - last - 1);
    return ret;
}

vector<int> process(vector<int> v) {
    int i = 0, j = (int)v.size() - 1;
    while (true) {
        while (i + 1 < j && v[i] == 0) {
            ++i;
        }
        while (i + 1 < j && v[j] == 0) {
            --j;
        }
        if (i + 1 >= j) {
            break;
        }
        int m = min(v[i], v[j]);
        v[i] -= m, v[j] -= m;
        v[i + 1] += m, v[j - 1] += m;
    }
    return v;
}

inline int turn(const int &a, const int &b) {
    if (a >= b) {
        return a - b;
    } else {
        return INF;
    }
}

const int BAR = 1000000;

bool check(vector<pair<int, int> > c) {
    if (c.size() > BAR) {
        return false;
    }
    for (int i = 0; i < (int)c.size(); ++i) {
        int u = c[i].first, v = c[i].second;
        if (!(1 <= u && u < n && 1 <= v && v < n)) {
            return false;
        }
        --u, --v;
        if (!(a[u] == 'a' && a[u + 1] == 'b' && a[v] == 'b' && a[v + 1] == 'a')) {
            return false;
        }
        swap(a[u], a[u + 1]);
        swap(a[v], a[v + 1]);
    }
    for (int i = 0; i < n; ++i) {
        if (a[i] != b[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    scanf("%d", &n);
    scanf("%s%s", a, b);
    vector<int> va = process(make(a)), vb = process(make(b));
    if (va != vb) {
        printf("NIE\n");
        return 0;
    }
    printf("TAK\n");
    if (n <= 4000) {
        va = make(a), vb = make(b);
        int i = 0, j = (int)va.size() - 1;
        vector<pair<int, int> > ca, cb;
        while (true) {
            while (i + 1 < j && va[i] == vb[i]) {
                ++i;
            }
            while (i + 1 < j && va[j] == vb[j]) {
                --j;
            }
            if (i + 1 >= j) {
                break;
            }
            int makea = min(turn(va[i], vb[i]), turn(va[j], vb[j])), makeb = min(turn(vb[i], va[i]), turn(vb[j], va[j]));
            if (makea > va[i] || makea > va[j]) {
                makea = INF;
            }
            if (makeb > vb[i] || makeb > vb[j]) {
                makeb = INF;
            }
            assert(min(makea, makeb) != INF);
            if (makea <= makeb) {
                int posa = 0, posb = n;
                for (int k = 0; k < i; ++k) {
                    posa += va[k] + 1;
                }
                posa += va[i];
                for (int k = (int)va.size() - 1; k > j; --k) {
                    posb -= va[k] + 1;
                }
                posb -= va[j];
                for (int k = 0; k < makea; ++k) {
                    ca.push_back(make_pair(posb, posa));
                    --posa, ++posb;
                    --va[i], ++va[i + 1],
                    --va[j], ++va[j - 1];
                }
            } else {
                int posa = 0, posb = n;
                for (int k = 0; k < i; ++k) {
                    posa += vb[k] + 1;
                }
                posa += vb[i];
                for (int k = (int)vb.size() - 1; k > j; --k) {
                    posb -= vb[k] + 1;
                }
                posb -= vb[j];
                for (int k = 0; k < makeb; ++k) {
                    cb.push_back(make_pair(posb, posa));
                    --posa, ++posb;
                    --vb[i], ++vb[i + 1],
                    --vb[j], ++vb[j - 1];
                }
            }
        }
        reverse(cb.begin(), cb.end());
        vector<pair<int, int> > c = ca;
        for (int i = 0; i < (int)cb.size(); ++i) {
            c.push_back(make_pair(cb[i].second, cb[i].first));
        }
        assert(check(c));
        printf("%d\n", (int)c.size());
        for (int i = 0; i < (int)c.size(); ++i) {
            printf("%d %d\n", c[i].first, c[i].second);
        }
    }
    return 0;
}
