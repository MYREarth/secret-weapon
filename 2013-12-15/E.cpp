#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 120;
int top, head[N], next[N * N], to[N * N];

void addedge(int u, int v) {
    to[top] = v, next[top] = head[u], head[u] = top++;
}

int n;

void print() {
    printf("%d\n", n);
    for (int u = 0; u < n; ++u) {
        vector<int> ans;
        for (int j = head[u]; ~j; j = next[j]) {
            int v = to[j];
            ans.push_back(v);
        }
        sort(ans.begin(),ans.end());
        printf("%d", (int)ans.size());
        for (int j = 0; j < (int)ans.size(); ++j) {
            printf(" %d", ans[j] + 1);
        }
        printf("\n");
    }
}

int met[N];

void dp(int u) {
    for (int j = head[u]; ~j; j = next[j]) {
        int vv = to[j];
        met[vv] += met[u];
    }    
}

int main() {
    freopen("kpaths.in", "r", stdin);
    freopen("kpaths.out", "w", stdout);
    int k, l = 0;
    scanf("%d", &k);
    while ((1 << l) <= k) {
        ++l;
    }
    n = l * 2;
    --l;
    top = 0;
    memset(head, -1, sizeof(head));
    for (int i = 0; i < l; ++i) {
        int u1 = 2 + i * 2, v1 = u1 + 1,
            u2 = 4 + i * 2, v2 = u2 + 1;
        if (i == l - 1) {
            addedge(u1, 1);
            addedge(v1, 1);
        } else {
            addedge(u1, v2);
            addedge(u1, u2);
            addedge(v1, v2);
            addedge(v1, u2);
        }
    }
    for (int i = 0; i <= l; ++i) {
        if (k >> i & 1) {
            if (i == 0) {
                addedge(0, 1);
            } else {
                addedge(0, (l - i + 1) * 2);
                addedge(0, (l - i + 1) * 2 + 1);
            }
        }
    }
    print();
    /*
    memset(met, 0, sizeof(met));
    met[0] = 1;
    dp(0);
    for (int i = 2; i <= l * 2 + 1; ++i) {
        dp(i);
    if (met[1] != k) {
        cout << "WA" << endl;
    }
    */
    return 0;
}
