#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int dis[2005][11];
queue<pair<int, int> > q;

void update(int p, int v, int d) {
    if (p > 2000 || p <= 0 || v > 10) {
        return;
    }
    if (dis[p][v] > d + 1) {
        dis[p][v] = d + 1;
        if (v != 0) {
            q.push(make_pair(p, v));
        }
    }
}

int main() {
    memset(dis, 63, sizeof(dis));
    dis[1000][1] = 0;
    q.push(make_pair(1000, 1));
    while (q.size()) {
        int p = q.front().first, v = q.front().second;
        q.pop();
        if ((p + (1 << v - 1)) < 2000) {
            update(p + (1 << v - 1), v + 1, dis[p][v]);
        }
        if ((p - (1 << v - 1)) > 0) {
            update(p - (1 << v - 1), v + 1, dis[p][v]);
        }
        if (v > 0) {
            update(p, v - 1, dis[p][v]);
        }
    }
    for (int i = 1001; i < 1101; ++i) {
        printf("%d\n", dis[i][0]);
    }
    return 0;
}
