#include<map>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int n;

char buf[505], buf2[505];
map<string, string> mem;
map<string, int> cnt;

int main() {
    scanf("%d", &n);
    gets(buf);
    for (int i = 0; i < n; ++i) {
        gets(buf);
        gets(buf2);
        mem[buf] = buf2;
    }
    int m;
    scanf("%d", &m);
    gets(buf);
    for (int i = 0; i < m; ++i) {
        gets(buf);
        if (mem.count((string)buf)) {
            ++cnt[buf];
        }
    }
    if (cnt.size() == 0) {
        puts("tie");
        return 0;
    }
    vector<pair<int, string> > v;
    for (map<string, int>::iterator it = cnt.begin(); it != cnt.end(); ++it) {
        v.push_back(make_pair(it->second, it->first));
    }
    sort(v.begin(), v.end());
    reverse(v.begin(), v.end());
    if (v.size() == 1 || v[0].first > v[1].first) {
        printf("%s\n", mem[v[0].second].c_str());
    } else {
        printf("tie\n");
    }
    return 0;
}
