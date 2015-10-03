#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 75;
int n;

bool vis[N], mem[N][N];

vector<int> in[N], out[N], ans;

int ord[N];

int limit;

bool go(int i) {
    if (ans.size() > limit) {
        return false;
    }
    if (i == n) {
        return true;
    }
    int u = ord[i];
    if (vis[u]) {
        return go(i + 1);
    } else {
        for (int j = 0; j < (int)in[u].size(); ++j) {
            int w = in[u][j];
            for (int k = 0; k < (int)out[w].size(); ++k) {
                int v = out[w][k];
                mem[i][v] = vis[v];
                vis[v] = true;
            }
            ans.push_back(w);
            if (go(i + 1)) {
                return true;
            }
            ans.pop_back();
            for (int k = 0; k < (int)out[w].size(); ++k) {
                int v = out[w][k];
                vis[v] = mem[i][v];
            }
        }
    }
    return false;
}

char buf[N + 1];

bool by_dgr(int i, int j) {
    return in[i].size() < in[j].size();
}

int main() {
    while (scanf("%d", &n) == 1) {
        for (int i = 0; i < n; ++i) {
            in[i].clear();
            out[i].clear();
        }
        for (int i = 0; i < n; ++i) {
            scanf("%s", buf);
            for (int j = 0; j < n; ++j) {
                if (i == j || buf[j] == '1') {
                    out[i].push_back(j);
                    in[j].push_back(i);
                }
            }
            ord[i] = i;
        }
        sort(ord, ord + n, by_dgr);
        memset(vis, 0, sizeof(vis));
        ans.clear();
        for (limit = 1; !go(0); limit++) {
        }
        static int id = 0;
        printf("Case %d: ", ++id);
        printf("%d", (int)ans.size());
        for (int i = 0; i < (int)ans.size(); ++i) {
            printf(" %d", ans[i] + 1);
        }
        printf("\n");
    }
    return 0;
}
