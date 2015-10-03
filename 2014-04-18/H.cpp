#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int main() {

    int n;
    scanf("%d", &n);
    if (n == 1) {
        printf("YES\n");
        return 0;
    }
    if (n == 4) {
        printf("NO\n");
        return 0;
    }
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            printf("YES\n");
            return 0;
        }
    }
    printf("NO\n");
    return 0;
}
