#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

char s[1000005];

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        bool flag = true;
        scanf("%s", s);
        int l = strlen(s);
        if (s[0] != 'M') {
            flag = false;
        }         
        int cnt = 0;
        for (int i = 1; i < l; ++i) {
            if (s[i] == 'I') {
                ++cnt;
            } else if (s[i] == 'U') {
                cnt += 3;
            } else {
                flag = false;
            }
        }
        if (cnt == 1 || cnt % 6 == 2 || cnt % 6 == 4) {
        } else {
            flag = false;
        }
        puts(flag ? "Yes" : "No");
    }
    return 0;
}
