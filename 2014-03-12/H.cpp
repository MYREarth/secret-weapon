#include<set>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int n, k;

inline int sign(long long a) {
    return a > 0 ? 1 : -1;
}

const int N = 1000005;

#define next NEXT

int next[N], prec[N];

long long cal[N], num[N];

int main() {
    freopen("holidays.in", "r", stdin);
    freopen("holidays.out", "w", stdout);
    //freopen("H2.in", "r", stdin);
    scanf("%d%d", &n, &k);
    vector<long long> num;
    for (int i = 0; i < n; ++i) {
        int a;
        scanf("%d", &a);
        if (a == 0) {
            continue;
        }
        if (num.size() == 0 || sign(a) != sign(num.back())) {
            num.push_back(a);
        } else {
            num.back() += a;
        }
    }
    if (num.size() && num.back() < 0) {
        num.pop_back();
    }
    if (num.size() && num[0] < 0) {
        num = vector<long long>(num.begin() + 1, num.end());
    }
    long long s = 0;
    int cnt = 0;
    n = num.size();
    set<pair<long long, int> > mem;
    for (int i = 0; i < n; ++i) {
        next[i] = i + 1;
        prec[i] = i - 1;
    }
    for (int i = 0; i < n; ++i) {
        if (num[i] > 0) {
            s += num[i];
            ++cnt;
            cal[i] = -num[i];
            mem.insert(make_pair(-num[i], i));
        } else {
            cal[i] = num[i];
            mem.insert(make_pair(num[i], i));
        }
    }
    if (cnt <= k) {
        cout << s << endl;
        return 0;
    }
    for (int _ = 0; _ < cnt - k; ++_) {
        long long ss = mem.rbegin()->first;
        int i = mem.rbegin()->second;
//cout << ss << ' ' << i << endl;
        s += ss;
        long long tmp = -cal[i], tpos = i;
        mem.erase(make_pair(cal[i], i));
        if (prec[i] != -1) {
            tmp += cal[prec[i]], tpos = prec[i];
            mem.erase(make_pair(cal[prec[i]], prec[i]));
        }
        if (next[i] != n) {
            tmp += cal[next[i]];
            mem.erase(make_pair(cal[next[i]], next[i]));
            int u = next[i];
            if (prec[u] != -1) {
                next[prec[u]] = next[u];
            }
            if (next[u] != n) {
                prec[next[u]] = prec[u];
            }
        }
        if (tpos != i) {
            if (prec[i] != -1) {
                next[prec[i]] = next[i];
            }
            if (next[i] != n) {
                prec[next[i]] = prec[i];
            }
        }
        if (tpos != 0 && next[tpos] != n) {
            cal[tpos] = tmp;
            mem.insert(make_pair(tmp, tpos));
//cout << "NEW" << ' ' << tmp << ' ' << tpos << endl;
        }
    }
    cout << s << endl;
    return 0;
}
