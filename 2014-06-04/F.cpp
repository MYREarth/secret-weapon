#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int INF = 1000000000 + 1;

int n;

const int N = 200005;

int top, bottom;

pair<int, int> s[N];

void push_front(pair<int, int> a) {
    s[++top] = a;
}

void push_back(pair<int, int> a) {
    s[--bottom] = make_pair(a.second, a.first);
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        vector<pair<int, int> > a(n);
        for (int i = 0; i < n; ++i) {
            scanf("%d%d", &a[i].first, &a[i].second);
            if (a[i].first > a[i].second) {
                swap(a[i].first, a[i].second);
            }
        }
        sort(a.begin(), a.end());
        top = 0, bottom = n + 1;
        s[top] = make_pair(-1, INF), s[bottom] = make_pair(INF, -1);
        for (int i = 0; i < n; ++i) {
            int j = i;
            while (j < n && a[j].first == a[i].first) {
                ++j;
            }
            int mins = s[top].second, k = i;
            while (k < j && a[k].second <= mins) {
                ++k;
            }
            for (int l = k - 1; l >= i; --l) {
                push_front(a[l]);
            }
            for (int l = j - 1; l >= k; --l) {
                push_back(a[l]);
            }
            i = j - 1;
        }
        bool good = true;
        for (int i = 1; i + 1 <= n; ++i) {
            good = good && (s[i].first <= s[i + 1].first && s[i].second >= s[i + 1].second);
        }
        if (!good) {
            puts("no");
        } else {
            puts("yes");
            for (int i = 1; i <= n; ++i) {
                printf("%d %d\n", s[i].first, s[i].second);
            }
        }
    }
    return 0;
}
