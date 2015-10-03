#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 3005;

char s[N];

int n;

int sg[N];

int stamp, used[N * N];

int main() {
    scanf("%s", s);
    n = strlen(s);
    for (int i = n - 1; i >= 0; --i) {
        ++stamp;
        used[0] = stamp;
        for (int d = (n - i); d >= 1; --d) {
            int t = 0;
            for (int k = i + d; k < n; k += d) {
                t ^= sg[k];
                if (t < N * N) {
                    used[t] = stamp;
                }
            }
        }
        sg[i] = 0;
        while (used[sg[i]] == stamp) {
            ++sg[i];
        }
    }
    int cur = 0;
    for (int i = n - 1; i >= 0; --i) {
        if (s[i] == 'N') {
            cur ^= sg[i];
        }
    }
    if (cur == 0) {
        printf("NIE\n");
    } else {
        int mi = -1, md = -1, ml = -1;
        for (int i = n - 1; i >= 0 && mi == -1; --i) {
            if (s[i] == 'S') {
                continue;
            }
            for (int d = (n - i); d >= 1 && mi == -1; --d) {
                int t = 0;
                for (int k = i; k < n && mi == -1; k += d) {
                    t ^= sg[k];
                    if (t == cur) {
                        mi = i, md = d, ml = k;
                    }
                }
            }
        }
        for (int i = mi; i <= ml; i += md) {
            if (s[i] == 'S') {
                s[i] = 'N';
            } else {
                s[i] = 'S';
            }
        }
        printf("%s\n", s);
    }
    return 0;
}
