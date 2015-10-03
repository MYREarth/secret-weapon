#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 100005;
vector<vector<int> > met[N];
vector<int> step;

int n;

void go(int m) {
//cout << m << ' ' << met[m].size() << endl;
    if (met[n].size() && step.size() > met[n][0].size()) {
        return;
    }
    if (m == 0) {
        if (met[n].size() == 0 || step.size() < met[n][0].size()) {
            met[n].clear();
            met[n].push_back(step);
        } else if (step.size() == met[n][0].size()) {
            met[n].push_back(step);
        }
        return ;
    }
    if (met[m].size() == 0) {
        for (int j = m; j >= 1; --j) {
            if (~j & 1) {
                continue;
            }
            if (m % j != j / 2) {
                continue;
            }
            int cnt = m / j;
            for (int k = 0; k < cnt; ++k) {
                step.push_back(j);
            }
            go(m % j);
            for (int k = 0; k < cnt; ++k) {
                step.pop_back();
            }
        }
        return;
    }
    if (met[n].size() == 0 || step.size() + met[m][0].size() < met[n][0].size()) {
//        cout << "S1" << endl;
        met[n].clear();
        for (int i = 0; i < (int)met[m].size(); ++i) {
            vector<int> tmp = step;
            for (int j = 0; j < (int)met[m][i].size(); ++j) {
                tmp.push_back(met[m][i][j]);
            }
            met[n].push_back(tmp);
        }
    } else if (step.size() + met[m][0].size() == met[n][0].size()) {
//        cout << "S2" << endl;
        for (int i = 0; i < (int)met[m].size(); ++i) {
            vector<int> tmp = step;
            for (int j = 0; j < (int)met[m][i].size(); ++j) {
                tmp.push_back(met[m][i][j]);
            }
            met[n].push_back(tmp);
        }
    }
}

int main() {
    scanf("%d", &n);
    if (n == 1) {
        printf("1 1\n1\n");
        return 0;
    }
    vector<int> one;
    one.push_back(1);
    met[1].push_back(one);
    go(n);
    printf("%d %d\n", (int)met[n].size(), (int)met[n][0].size());
    for (int i = 0; i < (int)met[n].size(); ++i) {
        sort(met[n][i].begin(), met[n][i].end());
    }
    sort(met[n].begin(), met[n].end());
    for (int i = 0; i < (int)met[n].size(); ++i) {
        for (int j = 0; j < (int)met[n][i].size(); ++j) {
            printf("%d%c", met[n][i][j], j == (int)met[n][i].size() - 1 ? '\n' : ' ');
        }
    }
    return 0;
}
