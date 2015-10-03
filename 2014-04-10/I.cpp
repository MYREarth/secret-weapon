#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int n;

const int N = 10005;
vector<pair<int, int> > edge[N];

const int M = 205;
vector<int> ans[M];

int g[M][M];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n * (n - 1) / 2; ++i) {
        int u, v, k;
        scanf("%d%d%d", &u, &v, &k);
        --u, --v;
        for (int i = 0; i < k; ++i) {
            int a;
            scanf("%d", &a);
            edge[a].push_back(make_pair(u, v));
        }
    }
    for (int i = 1; i < N; ++i) {
        vector<int> vis;
        for (int j = 0; j < (int)edge[i].size(); ++j) {
            vis.push_back(edge[i][j].first);
            vis.push_back(edge[i][j].second);
            g[edge[i][j].first][edge[i][j].second] = i;
            g[edge[i][j].second][edge[i][j].first] = i;
        }
        if (vis.size()) {
            sort(vis.begin(), vis.end());
            vis.erase(unique(vis.begin(), vis.end()), vis.end());
            for (int j = 0; j < (int)vis.size(); ++j) {
                for (int k = j + 1; k < (int)vis.size(); ++k) {
                    if (g[vis[j]][vis[k]] != i) {
                        puts("No");
                        return 0;
                    }
                }
            }
            for (int j = 0; j < (int)vis.size(); ++j) {
                ans[vis[j]].push_back(i);
            }
        }
    }
    puts("Yes");
    for (int i = 0; i < n; ++i) {
        printf("%d", (int)ans[i].size());
        for (int j = 0; j < (int)ans[i].size(); ++j) {
            printf(" %d", ans[i][j]);
        }
        printf("\n");
    }
    return 0;
}
