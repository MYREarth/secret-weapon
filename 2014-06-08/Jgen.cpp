#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int M = 1000000000;

int main() {
    freopen("J2.in", "w", stdout);
    int n, m;
    scanf("%d%d", &n, &m);
    printf("%d %d\n", n, m);
    for (int i = 0; i < m; ++i) {
        int u = rand() % n + 1, v = rand() % n + 1, w = rand() % M + 1;
        printf("%d %d %d\n", u, v, w);
    }
    return 0;
}
