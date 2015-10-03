#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int n = 750000;

int main() {
    printf("%d %d\n", n, 2);
    for (int i = 0; i < n; ++i) {
        //printf("%d %d\n",i,i+1);
       if (i * 2 + 1 < n) {
            printf("%d %d\n", i + 1, (i + 1) * 2);
        }
        if (i * 2 + 2 < n) {
            printf("%d %d\n", i + 1, (i + 1) * 2 + 1);
        }
    }
    return 0;
}
