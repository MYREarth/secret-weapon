#include <cctype>
#include <cstdio>
#include <cstring>
#include <map>
#include <algorithm>

const int N = 500;
const int M = N * (N - 1) / 2;

int n, m, max, q, a[M], b[M], c[M], id[M], values[M], graph[N][N], count[1 << 17];
bool state[M];
std::map <int, int> map;

void add(int k, int v) {
    for (; k < max; k += ~k & k + 1) {
        count[k] += v;
    }
}

const int DELTA[2] = {-1, 1};

int next_int() {
    char c = getchar();
    while (!isdigit(c)) {
        c = getchar();
    }
    int result = 0;
    while (isdigit(c)) {
        result = result * 10 + c - '0';
        c = getchar();
    }
    return result;
}

int cnt_flip,m1,m2,hehe[N],haha[N];
bool flip[N];

int main() {
    freopen("roads.in", "r", stdin);
    freopen("roads.out", "w", stdout);
    n = next_int();
    m = next_int();
    q = next_int();
    memset(graph, -1, sizeof(graph));
    for (int i = 0; i < m; ++ i) {
        a[i] = next_int() - 1;
        b[i] = next_int() - 1;
        c[i] = next_int();
    }
    max = 1;
    while (max < m) {
        max <<= 1;
    }
    memcpy(values, c, sizeof(c));
    std::sort(values, values + m);
    memset(count, 0, sizeof(count));
    for (int i = 0; i < m; ++ i) {
        graph[a[i]][b[i]] = graph[b[i]][a[i]] = id[i] = std::lower_bound(values, values + m, c[i]) - values;
        map[id[i]] = i;
        add(id[i], 1);
    }
    memset(state, true, sizeof(state));
    cnt_flip = 0;
    memset(flip, 0, sizeof(flip));
    while (q --) {
        static int t, x;
        t = next_int();
        x = next_int();
        if (t == 1) {
            x --;
            if ((flip[x] ^= 1)) {
                ++cnt_flip;
            } else {
                --cnt_flip;
            }
            /*
               for (int i = 0; i < n; ++ i) {
               if (~graph[x][i]) {
               int &j = graph[x][i];
               add(j, DELTA[state[j] ^= 1]);
               }
               }
               */
        } else {
            if (cnt_flip) {
                m1=m2=0;
                for (int i=0;i<n;i++)
                    if (flip[i])
                    {
                        hehe[m1++]=i;
                        flip[i]=false;
                    }
                    else
                        haha[m2++]=i;
                for (int i=0;i<m1;i++)
                    for (int j=0;j<m2;j++)
                    {
                        int &k = graph[hehe[i]][haha[j]];
                        if (~k)
                            add(k, DELTA[state[k] ^= 1]);
                    }
                cnt_flip = 0;
            }
            if (x > count[max - 1]) {
                puts("-1");
            } else {
                int result = 0;
                for (int now = max; now; now >>= 1) {
                    int &c = count[result | now - 1];
                    if (c < x) {
                        x -= c;
                        result |= now;
                    }
                }
                printf("%d\n", map[result] + 1);
            }
        }
    }
    return 0;
}

