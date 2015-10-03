#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int main() {
    int n;
    scanf("%d", &n);
    int s = 0, cnt = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int ch;
            scanf("%d", &ch);
            if (ch == 0) {
                ++cnt;
            } else {
                s += ch;
            }
        }
    }
    if (n * n - cnt >= cnt) {
        printf("%d\n", s);
    } else {
        printf("%d\n", -1);
    }
    return 0;
}
