#include<vector>
#include<cstdio>
#include<string>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

inline bool isprefix(const string &a, const string &b) {
    return a.size() <= b.size() && b.substr(0, a.size()) == a;
}

inline vector<int> merge(const vector<int> &a, const vector<int> &b) {
    vector<int> ret;
    int i = 0, j = 0;
    while (i < a.size() && j < b.size()) {
        if (a[i] == b[j]) {
            ret.push_back(a[i]);
            ++i, ++j;
        } else if (a[i] < b[j]) {
            ret.push_back(a[i]);
            ++i;
        } else {
            ret.push_back(b[j]);
            ++j;
        }
    }
    if (i < a.size()) {
        for (int k = i; k < (int)a.size(); ++k) {
            ret.push_back(a[k]);
        }
    }
    if (j < b.size()) {
        for (int k = j; k < (int)b.size(); ++k) {
            ret.push_back(b[k]);
        }
    }
    return ret;
}

struct Prefix {
    string s;
    vector<int> pre;

    Prefix() {}

    Prefix(const string &t) : s(t) {
        pre.push_back(s.size());
    }

    string ans() {
        return s.substr(0, pre[0]);
    }

    void update(const Prefix &b) {
        if (pre.size() == 0) {
            s = b.s, pre = b.pre;
            return;
        }
        if (isprefix(s, b.s)) {
            s = b.s, pre = merge(pre, b.pre);
        } else if (isprefix(b.s, s)) {
            pre = merge(pre, b.pre);
        } else {
            int i = 0;
            while (s[i] == b.s[i]) {
                ++i;
            }
            if (s[i] > b.s[i]) {
                while (pre.size() && pre.back() > i) {
                    pre.pop_back();
                }
                s = b.s, pre = merge(pre, b.pre);
            } else {
                vector<int> npre = b.pre;
                while (npre.size() && npre.back() > i) {
                    npre.pop_back();
                }
                pre = merge(pre, npre);
            }
        }
    }
};

Prefix append(Prefix a, char ch) {
    vector<int> newpre;
    for (int i = 0; i < (int)a.pre.size(); ++i) {
        int u = a.pre[i];
        if (u == a.s.size()) {
            newpre.push_back(u + 1);
            a.s += ch;
        } else {
            if (a.s[u] == ch) {
                newpre.push_back(u + 1);
            } else if (a.s[u] < ch) {
            } else if (a.s[u] > ch) {
                newpre.push_back(u + 1);
                a.s = a.s.substr(0, u) + ch;
                break;
            }
        }
    }
    a.pre = newpre;
    return a;
}

Prefix appbeg(Prefix a, char ch) {
    a.s = ch + a.s;
    for (int i = 0; i < (int)a.pre.size(); ++i) {
        ++a.pre[i];
    }
    return a;
}

const int L = 101;
int n;
Prefix dp[L][L];

int main() {
    string s;
    cin >> s;
    n = s.size();
    for (int i = 1; i <= n; ++i) {
        dp[i][i - 1] = dp[i][i] = Prefix("");
        dp[i][i].update(Prefix(s.substr(i - 1, 1)));
    }
    for (int l = 0; l < n; ++l) {
        for (int i = 1; i + l - 1 <= n; ++i) {
            int j = i + l - 1;
            if (dp[i][j].pre.size() == 0) {
                continue;
            }
            if (i > 1) {
                dp[i - 1][j].update(appbeg(dp[i][j], s[i - 2]));
            }
            if (j < n) {
                dp[i][j + 1].update(append(dp[i][j], s[j]));
            }
            if (i > 1 && j < n && s[i - 2] == s[j]) {
                dp[i - 1][j + 1].update(dp[i][j]);
            }
        }
    }
    cout << dp[1][n].ans() << endl;
    return 0;
}

