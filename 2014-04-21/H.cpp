#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int n, k, p;

const int N = 105;
int ans[N];

int main() {
    scanf("%d%d%d", &n, &k, &p);
    if (p == 100) {
        ans[1] = 1;
    } else if (p >= 50) {
        printf("0\n");
        return 0;
    } else {
        bool flag = false;
        for (int sum = 1; sum <= 100 && !flag; ++sum) {
            if (sum * (100 - 2 * p) % 100 == 0 &&
                sum * 2 * p % 100 == 0) {
                ans[0] = sum * (100 - 2 * p) / 100;
                int left = sum * 2 * p / 100;
                for (int j = 1; j < n; ++j) {
                    int tmp = min(left, k);
                    ans[j] = tmp;
                    left -= tmp;
                }
                if (left > 0 || ans[0] > k) {
                    break;
                }
                flag = true;
            }
        }
        if (!flag) {
            printf("0\n");
            return 0;
        }
    }
    printf("1\n");
    for (int i = 0; i < n; ++i) {
        printf("%d%c", ans[i], i == n - 1 ? '\n' : ' ');
    }
    return 0;
}
