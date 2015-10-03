#include<map>
#include<set>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

#define next NEXT

const int N = 1000005;
int n, a[N], next[N];

int anst[N];
vector<pair<int, int> > que[N];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", a + i);
    }
    map<int, int> mem;
    for (int i = n - 1; i >= 0; --i) {
        int tmp = a[i];
        if (!mem.count(tmp)) {
            next[i] = n;
        } else {
            next[i] = mem[tmp];
        }
        mem[tmp] = i;
    }
    int q;
    scanf("%d", &q);
    for (int i = 0; i < q; ++i) {
        int l, r;
        scanf("%d%d", &l, &r);
        --l, --r;
        que[l].push_back(make_pair(r, i));
    }
    map<int, int> ans;
    set<int> vis;
    int cur = a[0] == 0;
    ans[0] = cur;
    for (int i = 0; i < n; ++i) {
        vis.insert(a[i]);
        if (a[i] == cur) {
            while (vis.count(cur)) {
                ++cur;
            }
            ans[i] = cur;
        }
    }
    for (int i = 0; i < n; ++i) {
/*
printf("%d ", i);
for (map<int, int>::iterator it = ans.begin(); it != ans.end(); ++it) {
    printf("[%d : %d] ", it->first, it->second);
}
printf("\n");
*/
        for (int j = 0; j < (int)que[i].size(); ++j) {
            int p = que[i][j].first, id = que[i][j].second;
            map<int, int>::iterator it = ans.upper_bound(p);
            --it;
            anst[id] = it->second;
        }
        int pos = next[i];
        int minpos = pos;
        bool first = true;
        while (true) {
            map<int, int>::iterator it = ans.lower_bound(pos), nit = it;
            if (it == ans.begin()) {
                break;
            }
            --it;
            if (it->second < a[i]) {
                break;
            }
            if ((nit == ans.end() || nit->first > pos) && first) {
                ans[pos] = it->second;
            }
            minpos = it->first;
            ans.erase(it);
            first = false;
        }
        if (minpos < pos) {
            ans[minpos] = a[i];
        }
    }
    for (int i = 0; i < q; ++i) {
        printf("%d\n", anst[i]);
    }
    return 0;
}
