#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 100005 << 1;

int n;
int ans[N], a[N];

int main() {
    freopen("restore.in", "r", stdin);
    freopen("restore.out", "w", stdout);
    memset(ans, -1, sizeof(ans));
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", a + i);
        --a[i];
        int j = a[i];
        if (i == j) {
            continue;
        } else if (i < j) {
            ans[i * 2 + 1] = i * 2 + 1;
        } else {
            ans[i * 2] = i * 2;
        }
    }
    for (int i = 0; i < n; ++i) {
        int j = a[i], tk;
        if (ans[j * 2] == j * 2) {
            tk = j * 2 + 1;
        } else {
            tk = j * 2;
        }
        if (i == j) {
            continue;
        } else if (i < j) {
            ans[i * 2] = tk;
        } else {
            ans[i * 2 + 1] = tk;
        }
    }
/*
for (int i = 0; i < n * 2; ++i) {
    printf("%d ", ans[i] + 1);
}
printf("\n");
*/
    bool check = true;
    for (int i = 0; i < n; ++i) {
        if (ans[i * 2] < ans[i * 2 + 1] || i != 0 && ans[i * 2] < ans[i * 2 - 1]) {
            check = false;
        }
    }
    int cnt = 0;
    for (int i = 0; i < n * 2; ++i) {
        cnt += i == ans[i];
    }
    check &= cnt == n;
    for (int i = 0; i < n * 2; ++i) {
        a[i] = ans[i];
    }
    sort(a, a + n * 2);
    for (int i = 0; i < n * 2; ++i) {
        check = check && a[i] == i;
    }

    if (!check) {
        printf("-1\n");
    } else {
        for (int i = 0; i < 2 * n; ++i) {
            printf("%d%c", ans[i] + 1, i == n * 2 - 1 ? '\n' : ' ');
        }
    }
    return 0;
}
