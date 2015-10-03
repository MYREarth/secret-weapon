#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 0; i < (1 << n); ++i) {
        int a = i % (1 << k + 1), cnt = 0;
        for (int j = k; j > 0; --j) {
            if (a >= (1 << j)) {
                a -= 1 << j;
                cnt ^= 1;
            }
        }
        printf("%c", (a ^ cnt) ? 'B' : 'A');
    }
    printf("\n");
    return 0;
}
