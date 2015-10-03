#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

char s[100005];

int main() {
    freopen("energy.in", "r", stdin);
    freopen("energy.out", "w", stdout);
    int n;
    scanf("%d", &n);
    scanf("%s", s);
    int l = strlen(s);
    long long ans = 0;
    int one = 0, two = 0;
    for (int i = 0; i < l; ++i) {
        if (s[i] == '1') {
            if (one + 1 + two * 2 <= n) {
                ++one;
            } else if (two > 0) {
                --two;
                ++one;
            }
        } else {
            if (one + two * 2 + 2 <= n) {
                ++two;
            }
        }
        ans += one + two;
    }
    cout << ans << endl;
    return 0;
}
