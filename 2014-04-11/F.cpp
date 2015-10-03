#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int LOG = 405;

char s[105];

int l;

int top, bin[LOG];

bool iszero() {
    for (int i = 0; i < l; ++i) {
        if (s[i] != '0') {
            return false;
        }
    }
    return true;
}

void div2() {
    int d = 0;
    for (int i = 0; i < l; ++i) {
        int t = (s[i] - '0') / 2 + d;
        if ((s[i] - '0') % 2 == 1) {
            d = 5;
        } else {
            d = 0;
        }
        s[i] = '0' + t;
    }
}

int pos[LOG][2], neg[LOG][2];

const int INF = 1000000000;

int solve(int n) {
    if (n == 0) {
        return INF;
    }
    if (bin[0] == 0) {
        pos[0][0] = 2, neg[0][0] = 2;
        pos[0][1] = 2, neg[0][1] = 2;
    } else {
        pos[0][0] = 1, neg[0][0] = 1;
        pos[0][1] = 3, neg[0][1] = 3;
    }
    for (int i = 1; i < n; ++i) {
        if (bin[i] == 0) {
            pos[i][0] = min(min(pos[i - 1][0] + 2, pos[i - 1][1] + 1), min(neg[i - 1][0] + 1, neg[i - 1][1] + 2));
            pos[i][1] = min(min(pos[i - 1][0] + 2, pos[i - 1][1] + 1), min(neg[i - 1][0] + 3, neg[i - 1][1] + 2));
            neg[i][0] = min(min(pos[i - 1][0] + 2, pos[i - 1][1] + 1), min(neg[i - 1][0] + 1, neg[i - 1][1] + 2));
            neg[i][1] = min(min(pos[i - 1][0] + 4, pos[i - 1][1] + 3), min(neg[i - 1][0] + 2, neg[i - 1][1] + 1));
        } else {
            pos[i][0] = min(min(pos[i - 1][0] + 1, pos[i - 1][1] + 2), min(neg[i - 1][0] + 2, neg[i - 1][1] + 1));
            pos[i][1] = min(min(pos[i - 1][0] + 3, pos[i - 1][1] + 2), min(neg[i - 1][0] + 4, neg[i - 1][1] + 3));
            neg[i][0] = min(min(pos[i - 1][0] + 1, pos[i - 1][1] + 2), min(neg[i - 1][0] + 2, neg[i - 1][1] + 1));
            neg[i][1] = min(min(pos[i - 1][0] + 3, pos[i - 1][1] + 2), min(neg[i - 1][0] + 2, neg[i - 1][1] + 1));
        }
    }
    return pos[n - 1][n != top];
}

int main() {
    freopen("jumper.in", "r", stdin);
    while (scanf("%s", s) == 1) {
        top = 0;
        l = strlen(s);
        while (!iszero()) {
            bin[top++] = (s[l - 1] - '0') % 2;
            div2();
        }
        printf("%d\n", min(solve(top), solve(top - 1)) * 2 + 1);
    }
    return 0;
}
