#include<map>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

struct Pair {
    int val, pos;

    Pair() {
        val = pos = 0;
    }

    Pair(int val, int pos) : val(val), pos(pos) {}
};

bool operator < (const Pair &a, const Pair &b) {
    return a.val < b.val || a.val == b.val && a.pos > b.pos;
}

const int N = 3 * 100000;
int n, a[N];
vector<Pair> ord;
map<int, int> tr;

void push(int i) {
    tr[ord[i].pos] = ord[i].val;
}

void pop(int i) {
    tr.erase(tr.find(ord[i].pos));
}

bool check(int i) {
    if (tr.size() == 0) {
        return true;
    }
    map<int, int>::iterator right = tr.upper_bound(ord[i].pos);
    if (right == tr.end() || right->second >= ord[i].val) {
        return right == tr.begin() || (--right)->second <= ord[i].val;
    }
    return false;
}

int main() {
    freopen("gem.in", "r", stdin);
    freopen("gem.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", a + i);
        ord.push_back(Pair(a[i], i));
    }
    sort(ord.begin(), ord.end());
    int ans = n;
    int r = 0; 
    for (int l = 0; l < n; ++l) {
        while (r < n && check(r)) {
            push(r++);
        }
        ans = min(ans, n - r + l);
        if (l < r) {
            pop(l);
        }
    }
    printf("%d\n", ans);
    return 0;
}
