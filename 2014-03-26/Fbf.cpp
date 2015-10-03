#include <cstdio>
#include <cstring>

char buffer[200001];

int main() {
    int n, m;
    scanf("%d%d%s", &n, &m, buffer);
    while (m --) {
        int l, r;
        scanf("%d%d", &l, &r);
        l --, r --;
        int m = l + r;
        for (int i = l; i <= r; ++ i) {
            int ii = m - i;
            if (i < ii) {
                buffer[ii] = buffer[i];
            }
        }
    }
    puts(buffer);
    return 0;
}
