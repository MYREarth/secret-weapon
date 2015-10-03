#include<map>
#include<queue>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

map<pair<int, int>, int> ans;

const int N = 100005;
int n, a[N];

long long sum, suma;

int min0, min1;
priority_queue<pair<int, int> > size;

void deal() {
    int i = size.top().second;
    for (int j = 0; j < n; ++j) {
        if (j == i) {
            continue;
        }
        if (a[j] > 0) {
            suma += a[j];
            ans[make_pair(min(i, j), max(i, j))] += a[j];
        }
    }
}

bool realize() {
    while (size.size()) {
        int i = size.top().second;
        if (a[i] != size.top().first) {
            size.pop();
            if (a[i]) {
                size.push(make_pair(a[i], i));
            }
        } else {
            break;
        }
    }
    return size.size() > 0;
}

bool getmins() {
    while (min0 < n && a[min0] == 0) {
        ++min0;
    }
    min1 = max(min1, min0 + 1);
    while (min1 < n && a[min1] == 0) {
        ++min1;
    }
    return min1 < n;
}

int getmax(int avoid1, int avoid2) {
    realize();
    int i = size.top().second, ret = a[i];
    if (i == avoid1 || i == avoid2) {
        size.pop();
        realize();
        int j = size.top().second; ret = a[j];
        if (j == avoid1 || j == avoid2) {
            size.pop();
            realize();
            if (size.size() > 0) {
                ret = size.top().first;
            } else {
                ret = 0;
            }
            size.push(make_pair(a[j], j));
        }
        size.push(make_pair(a[i], i));
    }
    return ret;
}

void drink(int aa, int b, int cnt) {
    sum -= 2 * cnt;
    suma += cnt;
    ans[make_pair(min(aa, b), max(aa, b))] += cnt;
    a[aa] -= cnt, a[b] -= cnt;
}

void solve() {
    while (true) {
        if (!realize()) {
            return;
        }
        if (size.top().first * 2 >= sum) {
            deal();
            return;
        }
        if (!getmins()) {
            return;
        }
        int take = min((long long)min(a[min0], a[min1]), (sum + 1) / 2 - getmax(min0, min1));
        drink(min0, min1, take);
    }
}

int main() {
    freopen("magic.in", "r", stdin);
    freopen("magic.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", a + i);
        sum += a[i];
        size.push(make_pair(a[i], i));
    }
    min0 = 0, min1 = 0;
    solve();
    cout << ans.size() << endl;
    for (map<pair<int, int>, int> :: iterator it = ans.begin(); it != ans.end(); ++it) {
        printf("%d %d %d\n", it->first.first + 1, it->first.second + 1, it->second);
    }
    return 0;
}
