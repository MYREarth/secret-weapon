#include<map>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

map<vector<int>, int> mem;

int solve(vector<int> a) {
    sort(a.begin(), a.end());
    reverse(a.begin(), a.end());
    while (a.size() && a.back() == 0) {
        a.pop_back();
    }
    if (mem.count(a)) {
        return mem[a];
    }
    int ret = 0;
    if (a.size() == 0) {
        ret = 2;
    } else {
        bool win[3] = {0, 0, 0};
        for (int i = 0; i < (int)a.size(); ++i) {
            int ori = a[i];
            for (int j = 0; j < ori; ++j) {
                a[i] = j;
                win[(solve(a) + 1) % 3] = true;
            }
            a[i] = ori;
        }
        for (int i = 0; i <= 2; ++i) {
            if (win[i]) {
                ret = i;
                break;
            }
        }
    }
    return mem[a] = ret;
}

int cnt[5];

int main() {
    int t;
    scanf("%d", &t);
    while(t--) {
        int n;
        scanf("%d", &n);
        vector<int> v(n);
        for (int i = 0; i < 5; ++i) {
            cnt[i] = 0;
        }
        for (int i = 0; i < n; ++i) {
            //scanf("%d", &v[i]);
            v[i] = rand() % 4 + 1;
            for (int j = 0; j < 5; ++j) {
                cnt[j] += v[i] >> j & 1;
            }
        }
        sort(v.begin(), v.end());
        for (int i = 0; i < n; ++i) {
            printf("%d ", v[i]);
        }
        printf("\n");
        for (int i = 0; i < 5; ++i) {
            printf("%d", cnt[i] % 3);
        }
        printf("\n");
        printf("%c\n", 'A' + solve(v));
    }
    return 0;
}
