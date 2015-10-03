#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int M = 1001;

int n, m;
char ask[M];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++i) {
        ask[i] = '0';
    }
    ask[m] = '\0';
    int last = 0;
    for (int i = 0; i < m; ++i) {
        ask[i] = '1';
        printf("R %s\n", ask);
        fflush(stdout);
        int tmp;
        scanf("%d", &tmp);
        if (tmp - last != 3) {
            ask[i] = '0';
        } else {
            last = tmp;
        }
        if (last == 3 * n) {
            break;
        }
    }
    printf("A %s\n", ask);
    return 0;
}
