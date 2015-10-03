#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int dx[8] = {2, -2, 1, -1, 1, -1, 2, -2},
          dy[8] = {1, -1, 2, -2, -2, 2, -1, 1};
int n;

vector<int> atk[8][8];

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                atk[i][j].clear();
            }
        }
        for (int i = 0; i < n; ++i) {
            char s[3];
            scanf("%s", s);
            int x = s[1] - '1', y = s[0] - 'a';
            for (int d = 0; d < 8; ++d) {
                int tx = x + dx[d], ty = y + dy[d];
                if (tx >= 0 && tx < 8 && ty >= 0 && ty < 8) {
                    atk[x][y].push_back(tx * 8 + ty);
                }
            }
            sort(atk[x][y].begin(), atk[x][y].end());
        }
        unsigned long long ans = 0;
        for (int i = 7; i >= 0; --i) {
            for (int j = 7; j >= 0; --j) {
                int id = i * 8 + j;
                bool need = false;
                for (int d = 0; d < 8; ++d) {
                    int tx = i + dx[d], ty = j + dy[d];
                    if (tx >= 0 && tx < 8 && ty >= 0 && ty < 8) {
                        if (atk[tx][ty].size() && atk[tx][ty][0] == id) {
                            need = true;
                        }
                    }
                }
                if (need) {
                    ans |= 1ull << id;
                    for (int d = 0; d < 8; ++d) {
                        int tx = i + dx[d], ty = j + dy[d];
                        if (tx >= 0 && tx < 8 && ty >= 0 && ty < 8) {
                            atk[tx][ty].clear();
                        }
                    }
                }
            }
        }
        printf("%llu\n", ans);
    }
    return 0;
}
