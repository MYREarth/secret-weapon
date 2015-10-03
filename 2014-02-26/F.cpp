#include<cstdio>
#include<string>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 1005;

int l[2], next[2][N][26];
char s[2][N];
bool flag[2];

int f[N][N];
char path[N][N];

int main() {
    freopen("re.in", "r", stdin);
    freopen("re.out", "w", stdout);
    for (int i = 0; i < 2; ++i) {
        scanf("%s", s[i] + 1);
        l[i] = strlen(s[i] + 1);
        for (int k = 0; k < 26; ++k) {
            next[i][l[i]][k] = l[i] + 1;
        }
        for (int j = l[i] - 1; j >= 0; --j) {
            for (int k = 0; k < 26; ++k) {
                next[i][j][k] = next[i][j + 1][k];
            }
            if (s[i][j + 1] >= 'a' && s[i][j + 1] <= 'z') {
                next[i][j][s[i][j + 1] - 'a'] = j + 1;
            } else if (s[i][j + 1] == '?') {
                for (int k = 0; k < 26; ++k) {
                    next[i][j][k] = j + 1;
                }
            } else {
                flag[i] = true;
                for (int k = 0; k < 26; ++k) {
                    next[i][j][k] = j;
                }
            }
        }
    }
    if (flag[0] && flag[1]) {
        printf("%%)\n");
        return 0;
    }
    for (int i = l[0]; i >= 0; --i) {
        for (int j = l[1]; j >= 0; --j) {
            f[i][j] = 0; 
            for (int k = 0; k < 26; ++k) {
                if (next[0][i][k] != l[0] + 1 && next[1][j][k] != l[1] + 1) {
                    int ii = next[0][i][k], jj = next[1][j][k];
                    if (f[ii][jj] + 1 > f[i][j]) {
                        f[i][j] = f[ii][jj] + 1;
                        path[i][j] = 'a' + k;   
                    }  
                }
            }
        }
    }
    string ans;
    int i = 0, j = 0;
    while (path[i][j] != '\0' && i < l[0] && j < l[1]) {
        int k = path[i][j] - 'a';
        ans += path[i][j];
        i = next[0][i][k];
        j = next[1][j][k]; 
    }
    printf("%s\n", ans.c_str());
    return 0;
}
