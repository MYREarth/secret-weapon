#include<cmath>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int n, F, S;

vector<pair<int, int> > all, use;

pair<long double, long double> cal(int i, int j) {
    if ((long long)S * use[j].second <= F) {
        return make_pair((long double)S / use[j].first, F - (long long)S * use[j].second);
    } else {
        long double x = ((long double)use[j].second * S - F)/ (use[j].second - use[i].second);
        return make_pair(x / use[i].first + (S - x) / use[j].first, 0);
    }
}

bool better(const pair<long double, long double> a, const pair<long double, long double> b) {
    if (fabs(a.first - b.first) > 1e-7) {
        return a.first < b.first;
    } else {
        return a.second > b.second;
    }
}

int main() {
    scanf("%d%d%d", &n, &F, &S);
    for (int i = 0; i < n; ++i) {
        int f, v;
        scanf("%d%d", &f, &v);
        if (v == 0) {
            continue;
        }
        all.push_back(make_pair(v, f));
    }
    if (all.size() == 0) {
        printf("Mission impossible\n");
        return 0;
    }
    sort(all.begin(), all.end());
    for (int i = 0; i < (int)all.size(); ++i) {
        if (i && all[i].first == all[i - 1].first) {
            continue;
        }
        while (use.size() > 0 && use.back().second >= all[i].second) {
            use.pop_back();
        }
        use.push_back(all[i]);
    }
    pair<long double, long double> ans = make_pair(1e100, -1e100);
    int j = 0;
    for (int i = 0; i < (int)use.size(); ++i) {
        if ((long long)S * use[i].second > F) {
            break;
        }
        while (j + 1 < (int)use.size() && better(cal(i, j + 1), cal(i, j))) {
            ++j;
        }
        if (better(cal(i, j), ans)) {
            ans = cal(i, j);
        }
    }
    if (ans.first > 1e99) {
        printf("Mission impossible\n");
    } else {
        printf("%.12f %.12f\n", (double)ans.first, (double)ans.second);
    }
    return 0;
}
