#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 1000005;
int n, a[N];

int main() {
    freopen("irreducible.in", "r", stdin);
    freopen("irreducible.out", "w", stdout);
    int sum = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", a + i);
        sum += a[i];
    }
    vector<int> ans;
    for (int i = 0; i * (i + 1) / 2 <= sum; ++i) {
        if (i * (i + 1) / 2 % 2 != sum % 2) {
            continue;
        }
        int row = 0, cur = i;
        bool flag = true;
        while (row < n) {
            if (row + cur > n || cur > a[row] || cur < 0) {
                flag = false;
                break;
            }
            if (cur != 0) {
                cur += ((cur ^ a[row]) & 1) ? 1 : -1;
            } else {
                if (a[row] % 2 == 1) {
                    ++cur;
                }
            }
            ++row;
        }
        flag = flag && (row == n && cur == 0);
        if (flag) {
            ans.push_back(i);
        }
    }
    printf("%d\n", (int)ans.size());
    for (int i = 0; i < (int)ans.size(); ++i) {
        int u = ans[i];
        printf("%d", u);
        for (int j = u; j > 0; --j) {
            printf(" %d", j);
        }
        printf("\n");
    }
    return 0;
}
