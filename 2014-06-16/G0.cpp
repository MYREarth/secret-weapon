#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int mem[15][15][15][15];

int solve(int a, int b, int c, int d) {
    if (mem[a][b][c][d] != -1) {
        return mem[a][b][c][d];
    }
    int ret = 0;
    if (a == 0 && b == 0 && c == 0 && d == 0) {
        ret = 2;
    } else {
        bool could[3];
        memset(could, 0, sizeof(could));
        for (int i = 0; i < a; ++i) {
            could[(solve(i, b, c, d) + 1) % 3] = true;
        }
        for (int i = 0; i < b; ++i) {
            could[(solve(a, i, c, d) + 1) % 3] = true;
        }
        for (int i = 0; i < c; ++i) {
            could[(solve(a, b, i, d) + 1) % 3] = true;
        }
        for (int i = 0; i < d; ++i) {
            could[(solve(a, b, c, i) + 1) % 3] = true;
        }
        if (could[0]) {
            ret = 0;
        } else if (could[1]) {
            ret = 1;
        } else {
            ret = 2;
        }
    }
    return mem[a][b][c][d] = ret;
}

int main() {
    memset(mem, -1, sizeof(mem));
    for (int i = 0; i <= 10; ++i) {
        for (int j = 0; j <= i; ++j) {
            for (int k = 0; k <= j; ++k) {
                for (int l = 0; l <= k; ++l) {
                    if (solve(i, j, k, l) == 2) {
                        cout << i << ' ' << j << ' ' << k << ' ' << l << endl;
                    }
                }
            }
        }
    }
    return 0;
}
