#include<map>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int n;

const int N = 100005;
int s[N], a[N];

map<int, vector<int> > mem;

int check(int s, int l, int r) {
    if (!mem.count(s)) {
        return 0;
    }
    int ret = upper_bound(mem[s].begin(), mem[s].end(), r) - lower_bound(mem[s].begin(), mem[s].end(), l);
//cout << s << ' ' << l << ' ' << r << ' ' << ret << endl;
    return ret;
}

int main() {
    freopen("hack.in", "r", stdin);
    freopen("hack.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", a + i);
        s[i + 1] = s[i] ^ a[i];
    }
    for (int i = 0; i <= n; ++i) {
        mem[s[i]].push_back(i);
    }
    vector<pair<int, int> > stack;
    long long ans = 0;
    for (int i = 0; i < n; ++i) {
        stack.push_back(make_pair(i, a[i]));
        for (int j = 0; j < (int)stack.size(); ++j) {
            stack[j].second &= a[i];
        }
        vector<pair<int, int> > nstack;
        for (int j = 0; j < (int)stack.size(); ++j) {
            if (j == (int)stack.size() - 1 || stack[j].second != stack[j + 1].second) {
                nstack.push_back(stack[j]);
            }
        }
        stack = nstack;
/*
for (int j = 0; j < (int)stack.size(); ++j) {
    cout << stack[j].first << ' ' << stack[j].second << endl;
}
cout << endl;
*/
        for (int j = 0; j < (int)stack.size(); ++j) {
            int tmp = s[i + 1] ^ stack[j].second, p1 = j == 0 ? 0 : stack[j - 1].first + 1, p2 = stack[j].first;
            ans += check(tmp, p1, p2);
        }
    }
    cout << ans << endl;
    return 0;
}
