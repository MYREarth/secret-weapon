#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 405;
int n, h[N][N], hh[N * N];

int top, head[N * N], to[N * N * 12], next[N * N * 12];

void addedge(int u, int v) {
    to[top] = v, next[top] = head[u], head[u] = top++;
}

int node_cnt, num[N][N], dis[N * N];

double cpl_sum[6][N * N], path_cnt[6][N * N];

void bfs(int start, double sum[], double cnt[]) {
    for (int i = 0; i < node_cnt; ++i) {
        dis[i] = N * N;
    }
    queue<int> q;
    q.push(start);
    dis[start] = 0;
    sum[start] = 0;
    cnt[start] = 1;
    while (q.size()) {
        int u = q.front();
        q.pop();
        for (int j = head[u]; ~j; j = next[j]) {
            int v = to[j];
            if (dis[v] > dis[u] + 1) {
                q.push(v);
                dis[v] = dis[u] + 1;
                sum[v] = cnt[u] * abs(hh[u] - hh[v]) + sum[u];
                cnt[v] = cnt[u];
            } else if (dis[v] == dis[u] + 1) {
                sum[v] += cnt[u] * abs(hh[u] - hh[v]) + sum[u];
                cnt[v] += cnt[u];
            }
        }
    }
}

int main() {
    freopen("meeting.in", "r", stdin);
    freopen("meeting.out", "w", stdout);
    top = 0;
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 0; i < n - 1; ++i) {
        int m = n + i;
        for (int j = 0; j < m; ++j) {
            scanf("%d", &h[i][j]);
            hh[node_cnt] = h[i][j];
            num[i][j] = node_cnt++; 
        }
    }
    for (int i = 0; i < n; ++i) {
        int m = 2 * n - 1 - i;
        for (int j = 0; j < m; ++j) {
            scanf("%d", &h[n + i - 1][j]);
            hh[node_cnt] = h[n + i - 1][j];
            num[n + i - 1][j] = node_cnt++;
        }
    }
    for (int i = 0; i < n - 1; ++i) {
        int m = n + i;
        for (int j = 0; j < m; ++j) {
            if (j != m - 1) {
                addedge(num[i][j], num[i][j + 1]);
                addedge(num[i][j + 1], num[i][j]);
            }
            addedge(num[i][j], num[i + 1][j]);
            addedge(num[i + 1][j], num[i][j]);
            addedge(num[i][j], num[i + 1][j + 1]);
            addedge(num[i + 1][j + 1], num[i][j]);
        }
    } 
    for (int i = 0; i < n; ++i) {
        int m = 2 * n - 1 - i;
        for (int j = 0; j < m; ++j) {
            if (i != n - 1 && j) {
                addedge(num[n + i - 1][j], num[n + i][j - 1]);
                addedge(num[n + i][j - 1], num[n + i - 1][j]);
            }
            if (i != n - 1 && j != m - 1) {
                addedge(num[n + i - 1][j], num[n + i][j]);
                addedge(num[n + i][j], num[n + i - 1][j]);
            }
            if (j != m - 1) {
                addedge(num[n + i - 1][j], num[n + i - 1][j + 1]);
                addedge(num[n + i - 1][j + 1], num[n + i - 1][j]);
            }
        }
    }
    bfs(num[0][0], cpl_sum[0], path_cnt[0]);
    bfs(num[0][n - 1], cpl_sum[1], path_cnt[1]);
    bfs(num[n - 1][0], cpl_sum[2], path_cnt[2]);
    bfs(num[n - 1][n * 2 - 2], cpl_sum[3], path_cnt[3]);
    bfs(num[n * 2 - 2][0], cpl_sum[4], path_cnt[4]);
    bfs(num[n * 2 - 2][n - 1], cpl_sum[5], path_cnt[5]);
    int ansx = -1, ansy = -1; 
    double avg = 1e100;
    for (int i = 0; i < n - 1; ++i) {
        int m = n + i;
        for (int j = 0; j < m; ++j) {
            double tmp = 0;
            for (int k = 0; k < 6; ++k) {
                tmp += cpl_sum[k][num[i][j]] / path_cnt[k][num[i][j]];
            }
            if (tmp < avg) {
                ansx = i;
                ansy = j;
                avg = tmp;
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        int m = 2 * n - 1 - i;
        for (int j = 0; j < m; ++j) {
            int u = num[n + i - 1][j]; 
            double tmp = 0;
            for (int k = 0; k < 6; ++k) {
                tmp += cpl_sum[k][u] / path_cnt[k][u];
            }
            if (tmp < avg) {
                ansx = n + i - 1;
                ansy = j;
                avg = tmp;
            }
        }
    }
    printf("%d %d\n", ansx + 1, ansy + 1);
    return 0;
}
