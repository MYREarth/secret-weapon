#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int M = 1000000000;

int n;

int main() {
    scanf("%d", &n);
    freopen("D3.in", "w", stdout);
    printf("%d\n", n);
    for (int i = 0; i < n; ++i) {
        printf("%d %d\n", rand() % M + 1, rand() % M + 1);
    }
    return 0;
}
