#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int MOD1 = 5333, MOD2 = 1000003;

vector<int> xx[MOD1], yy[MOD1], z[MOD1];

void mark(int b0, int b1, int e0, int e1, vector<int> hash[MOD1]) {
    for (int b = b0; b <= b1; ++b) {
        int m1 = 1, m2 = 1;
        for (int e = 1; e <= e1; ++e) {
            (m1 *= b) %= MOD1;
            (m2 *= b) %= MOD2;
            if (e >= e0) {
                hash[m1].push_back(m2);
            }
        }
    }
}

int stamp, vis[MOD2], cnt[MOD2];

int b_min[3], b_max[3], e_min[3], e_max[3];

const int N = 155;
int top, xs[N * N], xm[N * N];

int main() {
    for (int i = 0; i < 3; ++i) {
        scanf("%d%d%d%d", b_min + i, b_max + i, e_min + i, e_max + i);
    }
    mark(b_min[0], b_max[0], e_min[0], e_max[0], xx);
    mark(b_min[1], b_max[1], e_min[1], e_max[1], yy);
    mark(b_min[2], b_max[2], e_min[2], e_max[2], z);
    for (int i = 0; i < MOD1; ++i) {
        for (int j = 0; j < (int)xx[i].size(); ++j) {
            xs[top] = i, xm[top] = xx[i][j];
            ++top;
        }
    }
    long long ans = 0;
    for (int s = 0; s < MOD1; ++s) {
if (s % 100 == 0) {
    cout << s << endl;
}
        if (z[s].size() == 0) {
            continue;
        }
        ++stamp;
        for (int i = 0; i < (int)z[s].size(); ++i) {
            int k = z[s][i];
            if (vis[k] != stamp) {
                vis[k] = stamp;
                cnt[k] = 0;
            }
            ++cnt[k];
        }
        for (int _ = 0; _ < top; ++_) {
            int x = xs[_], y = s - x;
            if (y < 0) {
                y += MOD1;
            }
            if (yy[y].size() == 0) {
                continue;
            }
            int j, p;
            for (j = 0; j < (int)yy[y].size(); ++j) {
                if ((p = xm[_] + yy[y][j]) >= MOD2) {
                    p -= MOD2;
                }
                if (vis[p] == stamp) {
                    ans += cnt[p];
                }
            }
        }
    }
    printf("%lld\n", ans);
    return 0;
}
