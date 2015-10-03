#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int main() {
    int n, m, x1, y1, x2, y2, s;
    scanf("%d%d", &n, &m);
    x1 = 1, y1 = 1, x2 = n, y2 = m, s = 0;
    do {
        printf("%d %d\n", x1, ++s);
        fflush(stdout);
        if (s == y2) {
            ++x1;
            s = y1 - 1;
        }
        char buf[10];
        scanf("%s", buf);
        int l = strlen(buf);
        if (l != 1) {
            break;
        }
        if (buf[0] == 'L') {
            --y1, --s, --y2;
            if (y1 == 0) {
                y1 = 1;
                if (s == -1) {
                    s = 0;
                }
            }
        } else if (buf[0] == 'R') {
            ++y1, ++s, ++y2;
            if (y2 == m + 1) {
                y2 = m;
                if (s == m) {
                    ++x1;
                    s = y1 - 1;
                }
            }
        } else if (buf[0] == 'U') {
            --x1, --x2;
            if (x1 == 0) {
                x1 = 1;
                s = y1 - 1;
            }
        } else if (buf[0] == 'D') {
            ++x1, ++x2;
            if (x2 == n + 1) {
                x2 = n;
            }
        }
    } while (true);
    return 0;
}
