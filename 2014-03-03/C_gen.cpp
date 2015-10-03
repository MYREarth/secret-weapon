#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 100005;
int a[N], c[N];

int main() {
    int n = 100;
    for (int i = 0; i < n; ++i) {
        a[i] = c[i] = i;
    }
    int t = 10;
    printf("%d\n", t);
    while (t--) {
        random_shuffle(a, a + n);
        random_shuffle(c, c + n);
        printf("%d\n", n);
        for (int i = 0; i < n; ++i) {
            int b = c[i] - a[i];
            if (b < 0) {
                b += n;
            }
            printf("%d%c", b, i == n - 1 ? '\n' : ' ');
        }
    }
    return 0;
}
