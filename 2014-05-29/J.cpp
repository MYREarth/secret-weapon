#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

void solve(vector<pair<int, int> > num, int offset) {
    bool order = true;
    for (int i = 0; i + 1 < (int)num.size(); ++i) {
        if (num[i] > num[i + 1]) {
            order = false;
        }
    }
    if (order) {
        return;
    }
    int n = num.size();
    vector<pair<int, int> > ord = num;
    nth_element(ord.begin(), ord.begin() + n / 2, ord.end());
    pair<int, int> mid = ord[n / 2];
    int pos;
    vector<int> mark;
    vector<pair<int, int> > &ori = num;
    for (int i = 0; i < n; ++i) {
        if (ori[i] < mid) {
            mark.push_back(0);
        } else if (ori[i] == mid) {
            pos = i;
            mark.push_back(-1);
        } else {
            mark.push_back(1);
        }
    }
    for (int i = 0; i < pos; ++i) {
        if (mark[i] == 1) {
            int j = i;
            while (mark[j] == 1 && j < pos) {
                ++j;
            }
            if (j == pos) {
                break;
            } else {
                while (mark[j] == 0 && j < pos) {
                    ++j;
                }
                --j;
                printf("%d %d\n", i + offset + 1, j + offset + 1);
                reverse(mark.begin() + i, mark.begin() + j + 1);
                reverse(ori.begin() + i, ori.begin() + j + 1);
            }
        }
    }
    for (int i = pos + 1; i < n; ++i) {
        if (mark[i] == 0) {
            int j = i;
            while (mark[j] == 0 && j < n) {
                ++j;
            }
            if (j == n) {
                break;
            } else {
                while (mark[j] == 1 && j < n) {
                    ++j;
                }
                --j;
                printf("%d %d\n", i + offset + 1, j + offset + 1);
                reverse(mark.begin() + i, mark.begin() + j + 1);
                reverse(ori.begin() + i, ori.begin() + j + 1);
            }
        }
    }
    int lb = pos, rb = pos;
    while (lb >= 0 && mark[lb] != 0) {
        --lb;
    }
    ++lb;
    while (rb < n && mark[rb] != 1) {
        ++rb;
    }
    --rb;
    if (rb > lb) {
        printf("%d %d\n", lb + offset + 1, rb + offset + 1);
        reverse(mark.begin() + lb, mark.begin() + rb + 1);
        reverse(ori.begin() + lb, ori.begin() + rb + 1);
    }
    vector<pair<int, int> > left, right;
    int newpos;
    for (int i = 0; i < n; ++i) {
        if (ori[i] == mid) {
            newpos = i;
        }
    }
    for (int i = 0; i < n; ++i) {
        if (ori[i] < mid) {
            left.push_back(make_pair(ori[i].first, i));
        } else if (ori[i] > mid) {
            right.push_back(make_pair(ori[i].first, i));
        }
    }
    if (left.size()) {
        solve(left, offset);
    }
    if (right.size()) {
        solve(right, offset + newpos + 1);
    }
}

int main() {
    int n;
    scanf("%d", &n);
    vector<pair<int, int> > ori;
    for (int i = 0; i < n; ++i) {
        int u;
        scanf("%d", &u);
        ori.push_back(make_pair(u, i));
    }
    solve(ori, 0);
    return 0;
}
