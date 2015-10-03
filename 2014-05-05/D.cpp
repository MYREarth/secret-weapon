#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 105;
int cnt[N], ord[N];

int l;

const int L = 20005;
char s[L];

const char p[2][4] = {"int", "for"};

int count() {
    int ret = 0;
    for (int i = 0; i < l; i += 4) {
        for (int j = 0; j < 2; ++j) {
            bool find = true;
            for (int k = 0; k < 3 && find; ++k) {
                bool choose = false;
                for (int o = 0; o <= 3 && !choose; ++o) {
                    if (s[i + o] == p[j][k]) {
                        choose = true;
                    }
                }
                find = find && choose;
            }
            ret += find;
        }
    }
    return ret;
}

bool by_cnt(int i, int j) {
    return cnt[i] > cnt[j];
}

int n;

bool ans[N];

int main() {
    freopen("detect.in", "r", stdin);
    freopen("detect.out", "w", stdout);
    scanf("%d", &n);
    gets(s);
    for (int i = 0; i < n; ++i) {
        gets(s);
        l = strlen(s);
        cnt[i] = count();
        ord[i] = i;
    }
    sort(ord, ord + n, by_cnt);
    for (int i = 0; i < n / 2; ++i) {
        ans[ord[i]] = true;
    }
    for (int i = 0; i < n; ++i) {
        puts(ans[i] ? "block" : "random");
    }
    return 0;
}
