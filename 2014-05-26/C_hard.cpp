#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int MOD = 1000003, MOD2 = 1000777;

vector<pair<int, int> > cnt[MOD];
vector<int> rem[MOD];

int main() {
    for (int z = 11; z <= 150; ++z) {
        int m = 1, m1 = 1;
        for (int c = 1; c <= 150; ++c) {
            (m *= z) %= MOD;
            (m1 *= z) %= MOD2;
            if (c > 10) {
                cnt[m].push_back(make_pair(z, c));
                rem[m].push_back(m1);
            }
        }
    }
    for (int x = 11; x <= 150; ++x) {
        int mx = 1, mx1 = 1;
        for (int a = 1; a <= 150; ++a) {
            (mx *= x) %= MOD;
            (mx1 *= x) %= MOD2;
            if (a > 10) {
                for (int y = 11; y <= 150; ++y) {
                    int my = 1, my1 = 1;
                    for (int b = 1; b <= 150; ++b) {
                        (my *= y) %= MOD;
                        (my1 *= y) %= MOD2;
                        if (b > 10) {
                            int p = mx + my, p1 = mx1 + my1;
                            if (p >= MOD) {
                                p -= MOD;
                            }
                            if (p1 >= MOD2) {
                                p1 -= MOD2;
                            }
                            for (int i = 0; i < (int)cnt[p].size(); ++i) {
                                if (rem[p][i] == p1) {
                                    printf("{%d, %d, %d, %d, %d, %d},\n", x, a, y, b, cnt[p][i].first, cnt[p][i].second);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}
