#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int cnt;

void go(int n) {
    if (n == 0) {
        ++cnt;
        return;
    }
    for (int i = 1; i <= n; ++i) {
        go(n - i);
    }
}
int main() {
    int n;
    scanf("%d", &n);
    go(n);
    printf("%d\n", cnt);
    return 0;
}
