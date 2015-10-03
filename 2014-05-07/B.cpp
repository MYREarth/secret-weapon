#include<map>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 100005;

#define next NEXT

map<int, int> mem;
int cnt, all, s[N], next[N], top[N], bottom[N], size[N];

int main() {
    while (true) {
        char op[2];
        scanf("%s", op);
        if (op[0] == 'A') {
            int p, num;
            scanf("%d%d", &p, &num);
            int u;
            if (mem.count(p)) {
                u = mem[p];
            } else {
                u = mem[p] = cnt++;
            }
            s[all] = num;
            if (size[u] == 0) {
                next[all] = -1;
                top[u] = bottom[u] = all;
            } else {
                next[all] = top[u];
                top[u] = all;
            }
            ++size[u];
            ++all;
        } else if (op[0] == 'M') {
            int p, q;
            scanf("%d%d", &q, &p);
            int u, v;
            if (mem.count(p)) {
                u = mem[p];
            } else {
                u = mem[p] = cnt++;
            }
            if (mem.count(q)) {
                v = mem[q];
            } else {
                v = mem[q] = cnt++;
            }
            if (size[v] == 0) {
                continue;
            }
            if (size[u] == 0) {
                size[u] = size[v];
                top[u] = top[v];
                bottom[u] = bottom[v];
                size[v] = 0, top[v] = bottom[v] = -1;
                continue;
            }
            next[bottom[v]] = top[u];
            top[u] = top[v];
            size[u] += size[v];
            size[v] = 0, top[v] = bottom[v] = -1;
        } else {
            break;
        }
    }
    for (auto it = mem.begin(); it != mem.end(); ++it) {
        int u = it->first, i = it->second;
        if (size[i] > 0) {
            printf("%d:", u);
            for (int j = top[i]; ~j; j = next[j]) {
                printf(" %d", s[j]);
            }
            printf("\n");
        }
    }
    return 0;
}
