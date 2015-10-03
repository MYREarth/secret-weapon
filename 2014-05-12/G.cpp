#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int n;

int top;

const int C = 20;

char buf[2];

int cnt_all = 0, cnt_work = 0;

char randch() {
    ++cnt_work;
    int t = (rand() & 3);
    if (t == 0) {
        return 'G';
    } else if (t == 1) {
        return 'S';
    } else if (t == 2) {
        return 'B';
    } else {
        return 'X';
    }
}

struct Graph {

    int n, num[C];
    char g[C][C];

    bool del[C];

    Graph() {
        n = 0;
        memset(num, 0, sizeof(num));
        memset(g, 0, sizeof(g));
        memset(del, 0, sizeof(del));
    }

    bool isempty() {
        return n == 0;
    }

    bool isfull() {
        for (int u = 0; u < n; ++u) {
            for (int v = u + 1; v < n; ++v) {
                if (!g[u][v]) {
                    return false;
                }
            }
        }
        return true;
    }

    void newnode() {
        int u = n;
        num[n++] = top++;
        del[u] = false;
        for (int v = 0; v < n; ++v) {
            g[v][u] = '\0';
        }
    }

    void addedge() {
        bool find = false;
        for (int u = 0; u < n && !find; ++u) {
            for (int v = u + 1; v < n && !find; ++v) {
                if (g[u][v] == '\0') {
                    printf("1 %d %d\n", num[u], num[v]);
                    fflush(stdout);
                    scanf("%s", buf);
                    //buf[0] = randch();
                    g[u][v] = buf[0];
                    find = true;
                }
            }
        }
    }

    bool findcycle() {
        for (int u = 0; u < n - 2; ++u) {
            for (int v = u + 1; v < n - 1; ++v) {
                for (int w = v + 1; w < n; ++w) {
                    if (g[u][v] == g[v][w] && g[u][v] == g[u][w]) {
                        del[u] = del[v] = del[w] = true;
                        return true;
                    }
                }
            }
        }
        return false;
    }

    bool killcycle() {
        printf("2");
        for (int i = 0; i < n; ++i) {
            if (del[i]) {
                printf(" %d", num[i]);
            }
        }
        printf("\n");
        fflush(stdout);
        scanf("%s", buf);
        /*
        ++cnt_all;
        if (cnt_all * 100 >= (::n) * 99) {
            return true;
        }
        */
        if (buf[0] == 'E') {
            return true;
        }
        int ncnt[C], cnt = 0;
        for (int i = 0; i < n; ++i) {
            if (!del[i]) {
                ncnt[cnt++] = i;
            }
        }
        for (int i = 0; i < cnt; ++i) {
            num[i] = num[ncnt[i]];
        }
        for (int i = 0; i < cnt; ++i) {
            for (int j = i + 1; j < cnt; ++j) {
                g[i][j] = g[ncnt[i]][ncnt[j]];
            }
        }
        for (int i = 0; i < cnt; ++i) {
            del[i] = false;
        }
        n = cnt;
        return false;
    }

    void print() {
        printf("%d\n", n);
        for (int i = 0; i < n; ++i) {
            printf("%d ", num[i]);
        }
        printf("\n");
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                printf("%c", g[i][j] == '\0' ? '?' : g[i][j]);
            }
            printf("\n");
        }
    }
};

int main() {
    scanf("%d", &n);
    top = 1;
    Graph work;
    while(true) {
        //work.print();
        if (work.isempty()) {
            work.newnode();
            work.newnode();
            work.addedge();
            continue;
        }
        if (work.findcycle()) {
            if (work.killcycle()) {
                break;
            }
            continue;
        }
        if (work.isfull()) {
            work.newnode();
        }
        work.addedge();
    }
    return 0;
}
