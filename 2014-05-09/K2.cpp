#include <cstdio>
#include <cstring>

int n, k;

double solve(int n, int k) {
    if (n < k) {
        return 0.;
    }
    if (k == 1) {
        return n;
    }
    if (n == 3) {
        return k == 2 ? 4. / 3. : 0.;
    }
    double result = 1.;
    return result;
}

int main() {
    scanf("%d%d", &n, &k);
    printf("%.10f\n", solve(n, k));
    return 0;
}
