#include <cstdio>
#include <cstring>
#include <utility>
#include <vector>

const int N   = 100000;
const int MOD = (int)1e9 + 7;

int n, m, k, row[N], column[N], color[N];

std::vector <std::pair <int, int> > graph[N + N];
int visit[N + N];

void add_edge(int a, int b, int c) 
{
    graph[a].push_back(std::make_pair(b, c));
    graph[b].push_back(std::make_pair(a, c));
}

long long count;

#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i)

void dfs(int u)
{
    foreach (iterator, graph[u]) {
        int v = iterator->first;
        int c = iterator->second;
        if (visit[v] == -1) {
            visit[v] = visit[u] ^ c;
            dfs(v);
        } else if ((visit[u] ^ visit[v]) != c) {
            count = 0;
            return;
        }
    }
}

int get_c(int x, int y, int c) {
    if (x == 0 && y == 0) {
        return c;
    }
    if (x > 0 && y > 0) {
        return c;
    }
    return 0;
}

int get_bit(int x, int y)
{
    return (x & 1) && (y & 1);
}

int main()
{
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 0; i < k; ++ i) {
        scanf("%d%d%d", row + i, column + i, color + i);
        row[i] --;
        column[i] --;
    }
    int result = 0;
    for (int c = 0; c < 2; ++ c) {
        for (int i = 0; i < n + m; ++ i) {
            graph[i].clear();
        }
        count = 1;
        for (int i = 0; i < k; ++ i) {
            if (row[i] == 0 && column[i] == 0) {
                if (color[i] != c) {
                    count = 0;
                }
            } else if (row[i] == 0) {
                add_edge(0, n + column[i], color[i]);
            } else if (column[i] == 0) {
                add_edge(0, row[i], color[i]);
            } else {
                add_edge(row[i], n + column[i], color[i] ^ get_c(row[i], column[i], c) ^ get_bit(row[i], column[i]));
            }
        }
        memset(visit, -1, sizeof(visit));
        visit[0] = 0;
        dfs(0);
        for (int i = 1; i < n + m; ++ i) {
            if (visit[i] == -1 && i != n) {
                (count <<= 1) %= MOD;
                visit[i] = 0;
                dfs(i);
            }
        }
        (result += count) %= MOD;
    }
    printf("%d\n", result);
    return 0;
}
