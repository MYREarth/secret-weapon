#include<cstdio>
#include<iostream>
using namespace std;

int main() {
    unsigned n, k, x0, x1, x2, a, b, c, mask;
    mask = (1ll << 31) - 1;
    cin >> n >> k >> x0 >> x1 >> a >> b >> c;
    for (int i = 0; i < n; ++i) {
        x2 = (a * x0 + b * x1 + c) & mask;
        x0 = x1, x1 = x2;
    }
    cout << x2 << endl;
    return 0;
}
