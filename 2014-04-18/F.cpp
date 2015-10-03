#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int a[4], b[4];

inline int cnt(int x) {
    int ret = 0;
    for (int i = 0; i < 4; ++i) {
        ret += (a[i] >= x);
    }
    return ret;
}

int main() {
    for (int i = 0; i < 4; ++i) {
        scanf("%d", a + i);
    }
    int start = 1;
    int best = -1000000000, cost = 0;
    for (int i = start; i <= 52; ++i) {
        int costi = cnt(i);
        cost += costi;
        for (int j = i + 1; j <= 52; ++j) {
            int costj = (j == i + 1) ? costi : cnt(j) + 1;
            cost += costj;
            for (int k = j + 1; k <= 52; ++k) {
                int costk = (k == j + 1) ? costj : cnt(k) + 2;
                cost += costk;
                for (int l = k + 1; l <= 52; ++l) {
                    int costl = (l == k + 1) ? costk : cnt(l) + 3;
                    cost += costl;
                    if (best < cost) {
                        best = cost;
                        b[0] = i, b[1] = j, b[2] = k, b[3] = l;
                    }
                    cost -= costl;
                }
                cost -= costk;
            }
            cost -= costj;
        }
        cost -= costi;
    }
    for (int i = 0; i < 4; ++i) {
        printf("%d%c", b[i], i == 3 ? '\n' : ' ');
    }
    return 0;
}
