#include<vector>
#include<cstdio>
#include<string>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 100 << 1;

int n, top, zero[N], one[N], fa[N];
char cnt[N];
string ans[N];

int main() {
    freopen("huffman.in", "r", stdin);
    freopen("huffman.out", "w", stdout);
    while (scanf("%d", &n) == 1 && n) {
        top = 0;
        for (int i = 0; i < n; ++i) {
            int z, o;
            scanf("%d%d", &z, &o);
            zero[top] = z, one[top] = o, fa[top] = -1, cnt[top] = '\0', ans[top] = "", ++top;
        }
        bool flag = true;
        for (int i = 0; i < n - 1; ++i) {
            int best = -1;
            for (int j = 0; j < top; ++j) {
                if (fa[j] != -1) {
                    continue;
                }
                if (best == -1 || zero[j] + one[j] > zero[best] + one[best] || zero[j] + one[j] == zero[best] + one[best] && one[j] > one[best]) {
                    best = j;
                }
            }
            if (best == -1) {
                flag = false;
                break;
            }
            int lc = best, rc = -1;
            for (int j = 0; j < top; ++j) {
                if (fa[j] != -1 || j == best) {
                    continue;
                }
                if (zero[j] == zero[lc] + 1 & one[j] == one[lc] - 1) {
                    rc = j;
                    break;
                }
            }
            if (rc == -1) {
                flag = false;
                break;
            }
            cnt[lc] = '1', cnt[rc] = '0';
            fa[lc] = fa[rc] = top;
            zero[top] = zero[lc], one[top] = one[rc], fa[top] = -1, cnt[top] = '\0', ans[top] = "", ++top;
        }
        if (flag) {
            int root = top - 1;
            if (zero[root] != 0 || one[root] != 0) {
                puts("No");
            } else {
                puts("Yes");
                for (int i = root - 1; i >= 0; --i) {
                    ans[i] = ans[fa[i]] + cnt[i];
                }
                for (int i = 0; i < n; ++i) {
                    printf("%s\n", ans[i].c_str());
                }
            }
        } else {
            puts("No");
        }
    }
    return 0;
}
