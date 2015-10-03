#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 2005;
int cnt[N], b[N];

int main() {
    int t = 10;
    printf("%d\n", t);
    for (int i = 0; i < t; ++i) {
        int n = 2000;
        memset(cnt, 0, sizeof(cnt));
        for (int j = 0; j < n / 2; ++j) {
            int a = rand() % n + 1;
            while (cnt[a] == 2) {
                a = rand() % n + 1;
            }
            a = j / 2;
            b[j] = a; 
            ++cnt[a];
        }
        printf("%d\n", n);
        int use[2] = {0, 0};
        for (int j = 0; j < n; ++j) {
            int tag;
            if (use[1] == use[0]) {
                tag = 0;
            } else if (use[0] == n / 2) {
                tag = 1;
            } else {
                tag = rand() % 2;
            }
            printf("%d ", b[use[tag]++]);
        }
        printf("\n");
    }
    return 0;
}
