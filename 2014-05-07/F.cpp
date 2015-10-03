#include<cstdio>
#include<string>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int r, c;

void show(long long x) {
    long long bar = 26;
    int cnt = 0;
    while (x >= bar) {
        x -= bar;
        bar *= 26;
        ++cnt;
    }
    string ans;
    for (int i = cnt; i >= 0; --i) {
        ans += 'A' + x % 26;
        x /= 26;
    }
    reverse(ans.begin(), ans.end());
    printf("%s", ans.c_str());
}

void solve1(char *s) {
    long long num = 0;
    for (char *ch = s; *ch; ++ch) {
        num = num * 10 + (*ch - '0');
    }
    long long x = (num - 1) / c, y = num - x * c - 1;
    show(y);
    printf("%lld\n", x + 1);
}

void solve2(char *s) {
    int cnt = 0;
    long long x = 0, y = 0;
    for (char *ch = s; *ch >= 'A' && *ch <= 'Z'; ++ch) {
        ++cnt;
        y = y * 26 + (*ch - 'A');
    }
    long long mul = 26;
    for (int i = 0; i < cnt - 1; ++i) {
        y += mul;
        mul *= 26;
    }
    for (char *ch = s + cnt; *ch; ++ch) {
        x = x * 10 + (*ch - '0');
    }
    printf("%lld\n", (x - 1) * c + y + 1);
}

int main() {
    scanf("%d%d", &r, &c);
    int q;
    scanf("%d", &q);
    while (q--) {
        char buf[25];
        scanf("%s", buf);
        if (buf[0] >= '0' && buf[0] <= '9') {
            solve1(buf);
        } else {
            solve2(buf);
        }
    }
    return 0;
}
