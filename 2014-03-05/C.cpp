#include<queue>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 105, M = N * N;
int n, m, k;

vector<int> ans;
int top, head[N], next[M], to[M], l[M];

int in[N];

void addedge(int u, int v, int i) {
    to[top] = v, next[top] = head[u], l[top] = i, head[u] = top++;
}

bool alive[N];

vector<int> v;

bool by_in(int i, int j) {
    return in[i] < in[j];
}

bool solve(int cost) {
    if (v.size() == n) {
        return true;
    }
    vector<int> tmp;
    for (int i = 0; i < n; ++i) {
        if (alive[i]) {
            tmp.push_back(i);
        }
    }
    sort(tmp.begin(), tmp.end(), by_in);
    bool ret = false;
    for (int i = 0; i < (int)tmp.size() && ~ret && cost + in[tmp[i]] <= k; ++i) {
        vector<int> q;
        q.push_back(tmp[i]);
        for (int j = 0; j < (int)q.size(); ++j) {
            int u = q[j];
            alive[u] = false;
            v.push_back(u);
            for (int k = head[u]; ~k; k = next[k]) {
                int v = to[k];
                if (alive[v]) {
                    if ((--in[v]) == 0) {
                        q.push_back(v);
                    }
                }
            }
        }
        ret = ret | solve(cost + in[tmp[i]]);
        if (ret) {
            break;
        }
        for (int j = (int)q.size() - 1; j >= 0; --j) {
            v.pop_back();
            int u = q[j];
            alive[u] = true;
            for (int k = head[u]; ~k; k = next[k]) {
                int v = to[k];
                if (alive[v]) {
                    ++in[v];
                }
            }
        }
    }
    return ret;
}

int ord[N];

int main() {
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    k = n * (n - 1) / 2 - m;
    for (int i = 0; i < m; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        addedge(--u, --v, i);
        ++in[v];
    }
    for (int i = 0; i < n; ++i) {
        alive[i] = true;
    }
    if (solve(0)) {
        for (int i = 0; i < n; ++i) {
            ord[v[i]] = i;
        }
        for (int i = 0; i < n; ++i) {
            for (int j = head[i]; ~j; j = next[j]) {
                int u = i, v = to[j];
                if (ord[u] > ord[v]) {
                    ans.push_back(l[j]);
                }
            }
        }
        printf("%d\n", (int)ans.size());
        sort(ans.begin(), ans.end());
        for (int i = 0; i < (int)ans.size(); ++i) {
            printf("%d\n", ans[i] + 1);
        }
    } else {
        printf("-1\n");
    }
    return 0;
}
