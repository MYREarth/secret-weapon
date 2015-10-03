#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

long long n, t;

const int N = 1000005;

int fa[N];
long long f[N], a[N];

int main() {
    cin >> n >> t;
    f[0] = -t;
    a[0] = f[0];
    long long best = 0;
    for (long long i = 1; i <= n; ++i) {
        while (best + 1 < i && a[best] - best * i >= a[best + 1] - (best + 1) * i) {
            ++best;
        }
        f[i] = a[best] - best * i + (i * i + i) / 2 + t + n - i;
        a[i] = f[i] + (i * i - i) / 2;
        fa[i] = best;
cout << i << ' ' << f[i] << ' ' << a[i] << endl;
    }
    cout << f[n] << endl;
    vector<int> ans;
    int u = n;
    while (u) {
        if (u != n) {
            ans.push_back(u);
        }
        u = fa[u];
    }
    printf("%d\n", (int)ans.size());
    for (int i = (int)ans.size() - 1; i >= 0; --i) {
        printf("%d%c", ans[i], i ? '\n' : ' ');
    }
    return 0;
}
