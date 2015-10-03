#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 1000 + 5;
char a[N], b[N], c[N];

int lcs[N][N], lcsb[N][N], goa[N], gob[N], next[N][26];

void cal(char *s, int l, int go[]) {
    for (int i = 0; i < 26; ++i) {
        next[l][i] = -1;
    }
    for (int i = l - 1; i >= 0; --i) {
        for (int j = 0; j < 26; ++j) {
            next[i][j] = next[i + 1][j];
        }
        next[i][s[i] - 'a'] = i + 1;
    }
    int lc = strlen(c);
    for (int i = 0; i < l; ++i) {
        go[i] = i;    
        for (int j = 0; j < lc && go[i] != -1; ++j) {
            go[i] = next[go[i]][c[j] - 'a'];
        }
    }
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%s%s%s", a, b, c);
        int la = strlen(a), lb = strlen(b), lc = strlen(c);
        memset(lcs, 0, sizeof(lcs)); 
        for (int i = 0; i < la; ++i) {
            for (int j = 0; j < lb; ++j) {
                if (a[i] == b[j]) {
                    lcs[i + 1][j + 1] = max(lcs[i + 1][j + 1], lcs[i][j] + 1);
                }
                lcs[i + 1][j] = max(lcs[i + 1][j], lcs[i][j]);
                lcs[i][j + 1] = max(lcs[i][j + 1], lcs[i][j]);
            }
        }
        memset(lcsb, 0, sizeof(lcsb));
        for (int i = la; i > 0; --i) {
            for (int j = lb; j > 0; --j) {
                if (a[i - 1] == b[j - 1]) {
                    lcsb[i - 1][j - 1] = max(lcsb[i - 1][j - 1], lcsb[i][j] + 1);
                }
                lcsb[i - 1][j] = max(lcsb[i - 1][j], lcsb[i][j]);
                lcsb[i][j - 1] = max(lcsb[i][j - 1], lcsb[i][j]);
            }
        }
        cal(a, la, goa);
        cal(b, lb, gob); 
        int ans = 0;
        for (int i = 0; i < la; ++i) {
            int u = goa[i];  
            if (u == -1) {
                continue;
            }
            for (int j = 0; j < lb; ++j) {
                int v = gob[j];
                if (v == -1) {
                    continue;
                }
//cout << i << ' ' << j << ' ' << u << ' ' << v << ' ' << lcs[i][j] + lcsb[u][v] + lc << endl;
                ans = max(ans, lcs[i][j] + lcsb[u][v] + lc);
            }
        }
        static int id = 0;
        printf("Case #%d: %d\n", ++id, ans);
    }
    return 0;
}
