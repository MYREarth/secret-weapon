#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

void print(int l, int r) {
    printf("check %d %d\n", l, r);
    fflush(stdout);
}

char buf[5];

bool yes() {
    scanf("%s", buf);
    return buf[0] == 'Y';
}

int main() {
    int vmin, vmax, pu;
    vector<pair<int, int> > p;
    scanf("%d%d", &pu, &vmax);
    vmin = 0;
    print(0, pu / 2);
    if (yes()) {
        p.push_back(make_pair(0, pu / 2));
    } else {
        p.push_back(make_pair(pu / 2 + 1, pu));
    }
    int t = 0;
    while (true) {
        ++t;
        int l = 0, r = 1000000000;
        for (int i = 0; i < t; ++i) {
            l = max(l, p[i].first + vmin * (t - i));
            r = min(r, p[i].second + vmax * (t - i));
        }
        if (l == r) {
            printf("answer %d\n", l);
            return 0;
        }
        int m = l + r >> 1;
        print(l, m);
        if (yes()) {
            r = m;
        } else {
            l = m + 1;
        }
        p.push_back(make_pair(l, r));
        for (int i = 0; i < t; ++i) {
            int d = t - i;
            vmin = max(vmin, (p[t].first - p[i].second + d - 1) / d);
            vmax = min(vmax, (p[t].second - p[i].first) / d);
        }
        /*
        for (int i = 0; i <= t; ++i) {
            for (int j = 0; j < i; ++j) {
                p[i].first = max(p[i].first, p[j].second + vmin * (i - j));
                p[i].second = min(p[i].second, p[j].first + vmax * (i - j));
            }
        }
        for (int i = 0; i <= t; ++i) {
            for (int j = t; j > i; --j) {
                p[i].first = max(p[i].first, p[j].first - vmax * (j - i));
                p[i].second = min(p[i].second, p[j].second - vmin * (j - i));
            }
        }
        for (int i = 0; i <= t; ++i) {
            for (int j = 0; j < i; ++j) {
                p[i].first = max(p[i].first, p[j].second + vmin * (i - j));
                p[i].second = min(p[i].second, p[j].first + vmax * (i - j));
            }
        }
        */
    }
    return 0;
}
