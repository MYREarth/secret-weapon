#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int LOG = 405;

char s[105];

int l;

int top, ori[LOG], bin[LOG];

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

int pos[LOG][LOG], neg[LOG][LOG];

const int INF = 1000000000;

int main() {
    //freopen("jumper.in", "r", stdin);
    scanf("%s", s);
    l = strlen(s);
    while (!iszero()) {
        bin[top++] = (s[l - 1] - '0') % 2;
        div2();
    }
    for (int i = 0; i < LOG; ++i) {
        for (int j = 0; j < LOG; ++j) {
            pos[i][j] = neg[i][j] = INF;
        }
    }
    if (bin[0] == 0) {
        pos[0][0] = 0, neg[0][1] = 2;
    } else {
        pos[0][1] = 1, neg[0][1] = 1;
    }
    for (int i = 0; i < top - 1; ++i) {
        int b = bin[i + 1];
        for (int j = 0; j < LOG - 1; ++j) {
            if (pos[i][j] != INF) {
                pos[i][j + 1] = min(pos[i][j + 1], pos[i][j] + 2);
                if (b == 0) {
                    pos[i + 1][j] = min(pos[i + 1][j], pos[i][j]);
                    if (j >= i + 2) {
                        neg[i + 1][j] = min(neg[i + 1][j], pos[i][j]);
                    } else if (j == i + 1) {
                        neg[i + 1][j + 1] = min(neg[i + 1][j + 1], 2 + pos[i][j]);
                    }
                } else {
                    if (j >= i + 2) {
                        pos[i + 1][j] = min(pos[i + 1][j], pos[i][j] + 1);
                        neg[i + 1][j] = min(neg[i + 1][j], pos[i][j] + 1);
                    } else if (j == i + 1) {
                        pos[i + 1][j + 1] = min(pos[i + 1][j + 1], pos[i][j] + 1);
                        neg[i + 1][j + 1] = min(neg[i + 1][j + 1], pos[i][j] + 1);
                    }
                }
            }
            if (neg[i][j] != INF) {
                neg[i][j + 1] = min(neg[i][j + 1], neg[i][j] + 2);
                if (b == 0) {
                    if (j >= i + 2) {
                        pos[i + 1][j] = min(pos[i + 1][j], neg[i][j] + 1);
                        neg[i + 1][j] = min(neg[i + 1][j], neg[i][j] + 1);
                    } else if (j == j + 1) {
                        pos[i + 1][j + 1] = min(pos[i + 1][j + 1], neg[i][j] + 1);
                        neg[i + 1][j + 1] = min(neg[i + 1][j + 1], neg[i][j] + 1);
                    }
                } else {
                    if (j >= i + 2) {
                        pos[i + 1][j] = min(pos[i + 1][j], neg[i][j]);
                    } else if (j == i + 1) {
                        pos[i + 1][j + 1] = min(pos[i + 1][j + 1], 2 + neg[i][j]);
                    }
                    neg[i + 1][j] = min(neg[i + 1][j], neg[i][j]);
                }
            }
        }
    }
    int ans = INF;
    for (int j = 0; j < LOG; ++j) {
        ans = min(ans, pos[top - 1][j]);
    }
    printf("%d\n", ans * 2 + 1);
    return 0;
}
