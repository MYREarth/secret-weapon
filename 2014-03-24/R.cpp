#include<queue>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 26 * 26 + 1, M = 100005;
int n;
int top, head[N], to[M], next[M], len[M];

void addedge(int u, int v, int l) {
    to[top] = v, next[top] = head[u], len[top] = l, head[u] = top++;
}

bool inque[N];
double dis[N];
int cnt[N];

const int NN = 26 * 26;

bool check(double bar) {
    queue<int> q;
    for (int i = 0; i < NN; ++i) {
        inque[i] = true;
        dis[i] = 0;
        cnt[i] = 1;
        q.push(i);
    }
    while (q.size()) {
        int u = q.front();
        q.pop();
        inque[u] = false;
        for (int j = head[u]; ~j; j = next[j]) {
            int v = to[j];
            double d = dis[u] + len[j] - bar;
            if (d > dis[v]) {
                dis[v] = d;
                ++cnt[v];
                if (cnt[v] * cnt[v] > NN * 2) {
                    return true;
                }
                if (!inque[v]) {
                    q.push(v);
                    inque[v] = true;
                }
            }
        }
    }
    return false;
}

char buf[1005];

int main() {
    while (scanf("%d", &n) == 1 && n) {
        top = 0;
        memset(head, -1, sizeof(head));
        for (int i = 0; i < n; ++i) {
            scanf("%s", buf);
            int l = strlen(buf);
            int in = (buf[0] - 'a') * 26 + buf[1] - 'a',
                out = (buf[l - 2] - 'a') * 26 + buf[l - 1] - 'a';
            addedge(in, out, l);
        }
        double l = 0, r = 1000;
        while (r - l > 1e-3) {
            double mid = (l + r) / 2;
            if (check(mid)) {
                l = mid;
            } else {
                r = mid;
            }
        }
        printf("%.2f\n", (l + r) / 2);
    }
    return 0;
}
