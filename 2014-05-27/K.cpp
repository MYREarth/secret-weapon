#include<deque>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 4005;

int l[N << 1];

void cal(char *s, int n, int ret[]) {
    l[0] = 1;
    for (int i = 1, j = 0; i != (n << 1) - 1; ++i) {
        int p = i >> 1, q = i - p, r = ((j + 1) >> 1) + l[j] - 1;
        l[i] = r < q ? 0 : min(r - q + 1, l[(j << 1) - i]);
        while (p - l[i] != -1 && q + l[i] != n && s[p - l[i]] == s[q + l[i]]) {
            l[i]++;
        }
        if (q + l[i] - 1 > r) {
            j = i;
        }
    }
    for (int i = 0; i < n; ++i) {
        ret[i] = l[i << 1];
    }
}

void solve(int h[], int n, int ret[]) {
    deque<pair<int, int> > stack;
    for (int i = 0; i < n; ++i) {
        pair<int, int> pr = make_pair(h[i], i);
        while (stack.size() && pr.first <= stack.back().first) {
            pr.second = stack.back().second;
            stack.pop_back();
        }
        stack.push_back(pr);
        while (stack[0].first < i - stack[0].second + 1) {
            ++stack[0].second;
            if (stack.size() > 1 && stack[0].second == stack[1].second) {
                stack.pop_front();
            }
        }
        ret[i] = i - stack[0].second + 1;
    }
}

int n;

int hori[N][N], vert[N][N], ans[N][N];

char map[N][N], tmp[N];

int h[N], kot[N];

int main() {
    freopen("kaleidoscope.in","r",stdin);
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for (int i = 0; i < n; ++i) {
            scanf("%s", map[i]);
            cal(map[i], n, hori[i]);
        }
        for (int j = 0; j < n; ++j) {
            for (int i = 0; i < n; ++i) {
                tmp[i] = map[i][j];
            }
            cal(tmp, n, vert[j]);
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                ans[i][j] = n;
            }
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                h[j] = vert[j][i];
            }
            solve(h, n, kot);
            for (int j = 0; j < n; ++j) {
                ans[i][j] = min(ans[i][j], kot[j]);
            }
            reverse(h, h + n);
            solve(h, n, kot);
            for (int j = 0; j < n; ++j) {
                ans[i][j] = min(ans[i][j], kot[n - j - 1]);
            }
        }
        for (int j = 0; j < n; ++j) {
            for (int i = 0; i < n; ++i) {
                h[i] = hori[i][j];
            }
            solve(h, n, kot);
            for (int i = 0; i < n; ++i) {
                ans[i][j] = min(ans[i][j], kot[i]);
            }
        }
        long long anst = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                anst += ans[i][j];
            }
        }
        printf("%lld\n", anst);
    }
    return 0;
}
