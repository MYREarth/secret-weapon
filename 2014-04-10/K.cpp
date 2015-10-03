#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;

const int K = 1500000;

unsigned tmp[K];

#define x0 X0

unsigned n, k, x0, x1, x2, a, b, c, mask;

void generate(unsigned z[], int n) {
    for (int i = 0; i < n; ++i) {
        x2 = (a * x0 + b * x1 + c) & mask;
        x0 = x1, x1 = x2;
        z[i] = x2;
    }
}

int main() {
    mask = (1ll << 31) - 1;
    cin >> n >> k >> x0 >> x1 >> a >> b >> c;
    if (n < K) {
        generate(tmp, n);
        sort(tmp, tmp + n);
        for (int i = 0; i < k; ++i) {
            printf("%d%c", tmp[n - 1 - i], i == k - 1 ? '\n' : ' ');
        }
        return 0;
    }
    generate(tmp, K);
    nth_element(tmp, tmp + K - k, tmp + K);
    for (int i = K; i < n; i += (K - k)) {
        int g = min(n - i, (unsigned)(K - k));
        generate(tmp, g);
        nth_element(tmp, tmp + K - k, tmp + K);
    }
    sort(tmp + K - k, tmp + K);
    for (int i = 0; i < k; ++i) {
        printf("%d%c", tmp[K - i - 1], i == k - 1 ? '\n' : ' ');
    }
    return 0;
}
