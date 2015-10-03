#include<set>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int n, k;

const int N = 1000005;

int a[N];

set<int> tr;

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; ++i) {
        scanf("%d", a + i);
    }
    for (int i = 0; i < k; ++i) {
        tr.insert(a[i]);
    }
    int pos = n - k;
    for (int i = 0; i + k < n; ++i) {
        if (*tr.begin() != a[i]) {
            pos = i;
            break;
        }
        tr.erase(a[i]);
        tr.insert(a[i + k]);
    }
    sort(a + pos, a + pos + k);
    for (int i = 0; i < n; ++i) {
        printf("%d%c", a[i], i == n - 1 ? '\n' : ' ');
    }
    return 0;
}
