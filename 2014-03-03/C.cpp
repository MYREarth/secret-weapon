#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 100005;
int n, b[N], c[N];

bool check() {
    for (int i = 0; i < n; ++i) {
        if (((i + b[i]) >= n ? i + b[i] - n : i + b[i]) != c[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for (int i = 0; i < n; ++i) {
            scanf("%d", b + i);
            c[i] = i;
        }
        int l = 0;
        while (!check()) {
            cout << ++l << endl;
            random_shuffle(c, c + n); 
        }
        for (int i = 0; i < n; ++i) {
            printf("%d%c", i, i == n - 1 ? '\n' : ' ');
        }
        for (int i = 0; i < n; ++i) {
            printf("%d%c", c[i], i == n - 1 ? '\n' : ' ');
        }
    }
    return 0;
}
