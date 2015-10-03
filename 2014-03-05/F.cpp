#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 1000005;

bool win[N];

bool check(long long n) {
    long long cnt = 2, delta = 1;
    while (cnt < n) {
        ++delta;
        if (delta * delta > cnt + delta) {
            --delta;
        }
        cnt += delta + 1;
    }
    return cnt == n;
}
int main() {
    /*
    win[0] = false;
    for (int i = 1; i < N; ++i) {
        for (int j = 1; j * j <= i; ++j) {
            win[i] |= !win[i - j];
        }
        if (!check(i) != win[i]) {
            printf("%d\n", i);
        }
    }
    */
    long long n;
    cin >> n;
    puts(check(n) ? "LOSE" : "WIN");
    return 0;
}
