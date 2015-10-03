#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int main() {
    //freopen("transformations.in", "r", stdin);
    int k;
    scanf("%d", &k);
    while (k--) {
        unsigned long long n;
        scanf("%lld", &n);
        string ans;
        while (n != 4) {
            if (n % 10 == 0) {
                ans += 'A';
                n /= 10;
            } else if (n % 10 == 4) {
                ans += 'B';
                n /= 10;
            } else {
                ans += 'C';
                n <<= 1;
            }
        }
        reverse(ans.begin(), ans.end());
        printf("%s\n", ans.c_str());
    }
    return 0;
}
