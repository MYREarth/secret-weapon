#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int main() {
    FILE *in1, *in2;
    in1 = fopen("G.ans", "r");
    in2 = fopen("G.out", "r");
    int a, b, n = 0, ac = 0;
    int err[3][3];
    memset(err, 0, sizeof(err));
    while (fscanf(in1, "%d", &a) == 1) {
        fscanf(in2, "%d", &b);
        ++n;
        ac += a == b;
        ++err[a][b];
    }
    printf("%d/%d\n%f\n", ac, n, (double)ac / n);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            printf("%d ", err[i][j]);
        }
        printf("\n");
    }
    return 0;
}
