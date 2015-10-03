#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int main() {
    freopen("jousting.in", "r", stdin);
    int t;
    scanf("%d", &t);
    while (t--) {
        unsigned long long n;
        scanf("%llu", &n);
        vector<unsigned long long> ans;
        for (int i = 0; ((1llu << i) + 1) <= n; ++i) {
            ans.push_back((1 + (1llu << i)));
        }
        printf("%d", (int)ans.size());
        for (int i = 0; i < (int)ans.size(); ++i) {
            printf(" %llu", ans[i]);
        }
        printf("\n");
    }
    return 0;
}
