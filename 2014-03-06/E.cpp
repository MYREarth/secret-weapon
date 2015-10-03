#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 305;
int n;

int cnt[N];

int main() {
    //freopen("permutation.in", "r", stdin);
    //freopen("permutation.out", "w", stdout);
    scanf("%d", &n);
    vector<vector<int> > s;
    for (int i = 0; i < n; ++i) {
        vector<int> tmp(n - 1);
        for (int j = 0; j < n - 1; ++j) {
            scanf("%d", &tmp[j]);
        }
        s.push_back(tmp);
    }
    vector<int> ans;
    sort(s.begin(), s.end());
    for (int i = 0; i < n && ans.size() == 0; ++i) {
        vector<int> tmp = s[i];
        int type = 0, maxm = 0;
        memset(cnt, 0, sizeof(cnt));
        for (int j = 0; j < n; ++j) {
            if (i == j) {
               continue;
            }
            for (int k = 0; k < n - 1; ++k) {
                if (s[j][k] == n - 1) {
                    if (cnt[k] == 0) {
                        ++type;
                    }
                    ++cnt[k];
                    maxm = max(maxm, k);
                    break;
                }
            }
        }
        if (type > 2) {
            continue;
        } else {
            if (maxm == n - 2 && type == 1) {
                ++maxm;
            }
            vector<int> ttmp;
            for (int i = 0; i < n; ++i) {
                if (i == maxm) {
                    ttmp.push_back(n);
                } else if (i < maxm) {
                    ttmp.push_back(tmp[i]);
                } else if (i > maxm) {
                    ttmp.push_back(tmp[i - 1]);
                }
            }
            tmp = ttmp;
        }
        vector<vector<int> > ss;
        for (int j = 0; j < n; ++j) {
            int u = tmp[j];
            vector<int> ttmp(n - 1);
            for (int k = 0; k < n; ++k) {
                if (k < j) {
                    ttmp[k] = tmp[k] > u ? tmp[k] - 1 : tmp[k];
                } else if (k > j) {
                    ttmp[k - 1] = tmp[k] > u ? tmp[k] - 1 : tmp[k];
                }
            }
            ss.push_back(ttmp);
        }
        sort(ss.begin(), ss.end());
        if (s == ss) {
            ans = tmp;
        }
    }
    for (int i = 0; i < (int)ans.size(); ++i) {
        printf("%d%c", ans[i], i == n - 1 ? '\n' : ' ');
    }
    return 0;
}
