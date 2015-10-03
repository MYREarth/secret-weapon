#include<queue>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int n;

int c[17][2];
char op[17][7];

bool use[33], g[33][33];
void addedge(int u, int v) {
    g[u][v] = true;
}

int num[33], ord[33];

void bfs(int u) {
    queue<int> q;
    use[u] = true;
    q.push(u);
    while (q.size()) {
        int u = q.front();
        q.pop();
        for (int j = 0; j < 32; ++j) {
            if (g[u][j] && !use[j]) {
                use[j] = true;
                q.push(j);
            }
        }
    }
}

queue<pair<int, int> > q;
int dis[17][1 << 18];

void update(int nst, int ni, int d) {
    if (dis[ni][nst] > d) {
        dis[ni][nst] = d;
        q.push(make_pair(ni, nst));
    }
}

int main() {
    vector<int> related;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%s", op[i]);
        char ch = op[i][0];
        if (ch == 'A' || ch == 'O' || ch == 'X' || ch == 'M') {
            scanf("%d%d", &c[i][0], &c[i][1]);
            addedge(c[i][0], c[i][1]);
        } else if (ch == 'N' || ch == 'R') {
            scanf("%d", &c[i][0]);
        } else if (ch == 'S' && op[i][1] == 'E') {
            scanf("%d%d", &c[i][0], &c[i][1]);
        } else if (ch == 'J') {
            if (op[i][1] == 'Z') {
                scanf("%d%d", &c[i][0], &c[i][1]);
                related.push_back(c[i][1]);
            } else {
                scanf("%d", &c[i][0]);
            }
        }
    }
    for (int i = 0; i < (int)related.size(); ++i) {
        bfs(related[i]);
    }
    int cnt = 0;
    for (int i = 0; i < 32; ++i) {
        if (use[i]) {
            num[cnt] = i;
            ord[i] = cnt++;
        }
    }
    for (int st = 0; st < (1 << cnt); ++st) {
        q.push(make_pair(0, st));
        for (int i = 0; i <= n; ++i) {
            dis[i][st] = 1 << 30;
        }
        dis[0][st] = 0;
    }
    int ans = -1;
    while (q.size() && ans == -1) {
        int st = q.front().second, i = q.front().first;
        q.pop();
        char ch = op[i][0], ch1 = op[i][1];
        if (ch == 'A') {
            int u = c[i][0], v = c[i][1];
            if (!use[u]) {
                update(st, i + 1, dis[i][st] + 1);
            } else {
                int r = ord[u], t = ord[v];
                int tc = st >> t & 1;
                update(st & ~(!tc << r), i + 1, dis[i][st] + 1);
            }
        } else if (ch == 'O') {
            int u = c[i][0], v = c[i][1];
            if (!use[u]) {
                update(st, i + 1, dis[i][st] + 1);
            } else {
                int r = ord[u], t = ord[v];
                int tc = st >> t & 1;
                update(st | (tc << r), i + 1, dis[i][st] + 1);
            }
        } else if (ch == 'X') {
            int u = c[i][0], v = c[i][1];
            if (!use[u]) {
                update(st, i + 1, dis[i][st] + 1);
            } else {
                int r = ord[u], t = ord[v];
                int tc = st >> t & 1;
                update(st ^ (tc << r), i + 1, dis[i][st] + 1);
            }
        } else if (ch == 'N') {
            int u = c[i][0];
            if (!use[u]) {
                update(st, i + 1, dis[i][st] + 1);
            } else {
                int r = ord[u];
                update(st ^ (1 << r), i + 1, dis[i][st] + 1);
            }
        } else if (ch == 'M') {
            int u = c[i][0], v = c[i][1];
            if (!use[u]) {
                update(st, i + 1, dis[i][st] + 1);
            } else {
                int r = ord[u], t = ord[v];
                int tc = st >> t & 1;
                if (tc == 0) {
                    update(st & ~(1 << r), i + 1, dis[i][st] + 1);
                } else {
                    update(st | (1 << r), i + 1, dis[i][st] + 1);
                }
            }
        } else if (ch == 'S' && ch1 == 'E') {
            int u = c[i][0];
            if (!use[u]) {
                update(st, i + 1, dis[i][st] + 1);
            } else {
                int r = ord[u];
                if (c[i][1] == 0) {
                    update(st & ~(1 << r), i + 1, dis[i][st] + 1);
                } else {
                    update(st | (1 << r), i + 1, dis[i][st] + 1);
                }
            }
        } else if (ch == 'R') {
            int u = c[i][0];
            if (!use[u]) {
                update(st, i + 1, dis[i][st] + 1);
            } else {
                int r = ord[u];
                update(st, i + 1, dis[i][st] + 1);
                update(st ^ (1 << r), i + 1, dis[i][st] + 1);
            }
        } else if (ch == 'J' && ch1 == 'M') {
            update(st, c[i][0], dis[i][st] + 1);
        } else if (ch == 'J' && ch1 == 'Z') {
            int u = c[i][1];
            int r = ord[u];
            int tc = st >> r & 1;
            if (tc == 0) {
                update(st, c[i][0], dis[i][st] + 1);
            } else {
                update(st, i + 1, dis[i][st] + 1);
            }
        } else {
            ans = dis[i][st] + 1;
        }
    }
    if (ans == -1) {
        printf("HANGS\n");
    } else {
        printf("%d\n", ans);
    }
    return 0;
}
