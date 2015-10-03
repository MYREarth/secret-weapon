#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int ans, bar;
string anss;

const int DEP = 50;
vector<pair<int, int> > stack[50];

int sum[DEP];

string l[DEP];

void go(int dep);

void trace(int pos, int dep) {
    string &f = l[dep];
    if (pos == f.size()) {
        string &c = l[dep + 1];
        c = "";
        for (int i = 0; i < (int)stack[dep].size(); ++i) {
            for (int j = 0; j < stack[dep][i].first; ++j) {
                c += stack[dep][i].second + '0';
            }
        }
        if (c != "0") {
            go(dep + 1);
        }
    }
    if (f[pos] == '0') {
        return;
    }
    int num = f[pos] - '0';
    for (int len = 1; len <= 1 && pos + len < f.size() && sum[dep] + num < bar; ++len) {
        int ch = f[pos + len] - '0';
        if (stack[dep].size() == 0 || stack[dep].back().second != ch) {
            stack[dep].push_back(make_pair(num, ch));
            sum[dep] += num;
            trace(pos + len + 1, dep);
            sum[dep] -= num;
            stack[dep].pop_back();
        }
        num = num * 10 + f[pos + len] - '0';
    }
}

void go(int dep) {
    string &s = l[dep];
    if (s.size() > bar) {
        return;
    }
    if (s.size() < ans) {
        anss = s;
        ans = s.size();
        bar = ans * 12;
    }
    trace(0, dep);
}

char s[10005];

int main() {
    freopen("describe.in", "r", stdin);
    freopen("describe.out", "w", stdout);
    scanf("%s", s);
    l[0] = s;
    int l = strlen(s);
    ans = l;
    anss = s;
    bar = l * 12;
    go(0);
    printf("%s\n", anss.c_str());
    return 0;
}
