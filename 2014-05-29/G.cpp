#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int n, s, q;

int main() {
    while (scanf("%d%d%d", &n, &s, &q) == 3 && n) {
        static int id = 0;
        printf("SMS %d:", ++id);
        s %= (n + 1);
        for (int i = 0; i < q; ++i) {
            long long a, lb;
            scanf("%lld", &a);
            --a;
            for (int j = 0; j < s; ++j) {
                if (a) {
                    lb = a & -a;
                } else {
                    lb = 1ll << n;
                }
                a = (1ll << n) - (1ll << n) / lb + ((a / lb) >> 1);
            }
            printf(" %lld", a + 1);
        }
        printf("\n");
    }
    return 0;
}
