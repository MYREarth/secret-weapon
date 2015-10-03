#include<vector>
#include<cstdio>
#include<cstring>
#include<string>
#include<iostream>
#include<algorithm>
using namespace std;

vector<string> cut(string s) {
    vector<string> ret;
    string ept;
    ret.push_back(ept);
    for (int i = 0; i < (int)s.size(); ++i) {
        if (s[i] == '*') {
            ret.push_back(ept);
        } else {
            ret.back() += s[i];
        }
    }
    return ret;
}

const int L = 200000 + 5;
int next[L];

int main() {
    freopen("patterns.in", "r", stdin);
    freopen("patterns.out", "w", stdout);
    string sa, sb;
    cin >> sa >> sb;
    vector<string> v1 = cut(sa), v2 = cut(sb);
    int sum1 = 0, sum2 = 0;
    for (int i = 0; i < (int)v1.size(); ++i) {
        sum1 += v1[i].size();
    }
    for (int j = 0; j < (int)v2.size(); ++j) {
        sum2 += v2[j].size();
    }
    if (sum1 == 0 && sum2 == 0) {
        printf("a\n");
        return 0;
    }
    if (v1.size() == 1 && v2.size() == 1) {
        if (v1[0] != v2[0]) {
            puts("Impossible");
        } else {
            printf("%s\n", v1[0].c_str());
        }
    } else if (v1.size() == 1 || v2.size() == 1) {
        if (v1.size() == 1) {
            swap(v1, v2);
            swap(sa, sb);
        }
        int l1 = v1[0].size(), l2 = v1.back().size();
        int i = 0;
        bool flag = true;
        if (l1 + l2 > v2[0].size() || v2[0].substr(0, l1) != v1[0] || v2.back().substr(v2.back().size() - l2, l2) != v1.back()) {
            flag = false;
        } else {
            v2[0] = v2[0].substr(l1, v2[0].size() - l1 - l2);
        }
        for (int j = 1; j + 1 < (int)v1.size() && flag; ++j) {
            if (v1[j].size() == 0) {
                continue;
            }
            int l = v1[j].size(); 
            next[0] = -1;
            for (int k = 1; k <= l; ++k) {
                next[k] = next[k - 1];
                while (next[k] != -1 && v1[j][next[k]] != v1[j][k - 1]) {
                    next[k] = next[next[k]];
                }
                ++next[k];
            }
            int p = 0; 
            while (i < v2[0].size() && p != l) {
                while (p != -1 && v2[0][i] != v1[j][p]) {
                    p = next[p];
                }
                ++p, ++i;
            }
            if (p != l) {
                flag = false;
            }
        }
        if (flag) {
            printf("%s\n", sb.c_str());
        } else {
            puts("Impossible");
        }
    } else {
        int len1 = min(v1[0].size(), v2[0].size()), len2 = min(v1.back().size(), v2.back().size()); 
        if (v1[0].substr(0, len1) == v2[0].substr(0, len1) && v1.back().substr(v1.back().size() - len2, len2) == v2.back().substr(v2.back().size() - len2, len2)) {
            string ans;
            if (v1[0].size() > v2[0].size()) {
                ans += v1[0];
            } else {
                ans += v2[0];
            }
            for (int i = 1; i + 1 < v1.size(); ++i) {
                ans += v1[i];
            }
            for (int i = 1; i + 1 < v2.size(); ++i) {
                ans += v2[i];
            }
            if (v1.back().size() > v2.back().size()) {
                ans += v1.back();
            } else {
                ans += v2.back();
            }
            printf("%s\n", ans.c_str());
        } else {
            puts("Impossible");
        }
    }
    return 0;
}
