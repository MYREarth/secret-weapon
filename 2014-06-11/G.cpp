#include<cassert>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const char* noSoluition = "Impossible";

pair<long long, char> c[3];

const int N = 1 << 17;

char ans[N];

int main() {
    scanf("%lld%lld%lld", &c[0].first, &c[1].first, &c[2].first);
    c[0].second = 'W', c[1].second = 'G', c[2].second = 'B';
    long long s = c[0].first + c[1].first + c[2].first;
    long long n = 0;
    while (n * (n + 1) / 2 < s) {
        ++n;
    }
    if (n * (n + 1) / 2 != s) {
        printf("%s\n", noSoluition);
        return 0;
    }

    int cnt1 = (c[0].first == 1) + (c[1].first == 1) + (c[2].first == 1),
        cnt2 = (c[0].first == 2) + (c[1].first == 2) + (c[2].first == 2);
    if (cnt1 >= 2 || cnt2 >= 2) {
        printf("%s\n", noSoluition);
        return 0;
    }

    sort(c, c + 3);
    for (int i = 0; i <= n; ++i) {
        ans[i] = ' ';
    }
    ans[n + 1] = '\n';

    if (c[2].first < n) {
        printf("%s\n", noSoluition);
        return 0;
    }

    int posB = 0;
    for (int i = n; i > 0; --i) {
        if (c[2].first >= i) {
            c[2].first -= i;
            ans[i] = c[2].second;
        } else {
            posB = i;
            break;
        }
    }
    if (c[2].first != 0) {
        ans[c[2].first] = c[2].second;
        c[2].first = 0;
    }

    for (int i = posB; i > 0; --i) {
        if (ans[i] == ' ') {
            if (c[1].first >= i) {
                c[1].first -= i;
                ans[i] = c[1].second;
            } else {
                break;
            }
        } else {
            continue;
        }
    }

    if (c[1].first != 0) {
        if (ans[c[1].first] == ' ') {
            ans[c[1].first] = c[1].second;
            c[1].first = 0;
        } else {
            if (c[1].first >= 3) {
                ans[1] = ans[c[1].first - 1] = c[1].second;
                c[1].first = 0;
            } else if (c[1].first == 2) {
                swap(ans[posB], ans[posB + 1]);
                ans[3] = c[2].second, ans[1] = c[1].second, ans[2] = ' ';
                c[1].first = 0;
            } else if (c[1].first == 1) {
                swap(ans[posB], ans[posB + 1]);
                c[1].first= 0;
                ans[2] = c[2].second, ans[1] = ' ';
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        if (ans[i] == ' ') {
            c[0].first -= i;
            ans[i] = c[0].second;
        }
    }

    assert(c[0].first == 0);

    printf("%s\n", ans + 1);
    return 0;
}
