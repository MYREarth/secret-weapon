#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int n, m;

const int N = 100005;
vector<long long> v[2];

int main() {
    while (scanf("%d%d", &n, &m) == 2) {
        v[0].resize(n), v[1].resize(m);
        for (int i = 0; i < n; ++i) {
            scanf("%lld", &v[0][i]);
        }
        for (int i = 0; i < m; ++i) {
            scanf("%lld", &v[1][i]);
        }
        sort(v[0].begin(), v[0].end());
        reverse(v[0].begin(), v[0].end());
        sort(v[1].begin(), v[1].end());
        reverse(v[1].begin(), v[1].end());
        bool win = false;
        if (v[0][0] > v[1][0]) {
            if (v[1].size() == 1) {
                win = true;
            } else {
                long long sum[2];
                sum[0] = v[0][0], sum[1] = v[1][1];
                int i = 1, winner = -1;
                while (winner == -1) {
                    if (i + 1 < v[1].size()) {
                        sum[1] += v[1][i + 1];
                    }
                    if (sum[1] < sum[0]) {
                        winner = 0;
                        break;
                    }
                    if (i < v[0].size()) {
                        sum[0] += v[0][i];
                    }
                    if (sum[0] < sum[1]) {
                        winner = 1;
                        break;
                    }
                    ++i;
                }
                win |= winner == 0;
            }
        }
        if (v[0].size() > 1) {
            long long sum[2];
            sum[0] = v[0][0], sum[1] = v[1][0];
            int i = 1, winner = -1;
            while (winner == -1) {
                if (i < v[0].size()) {
                    sum[0] += v[0][i];
                }
                if (sum[0] < sum[1]) {
                    winner = 1;
                    break;
                }
                if (i < v[1].size()) {
                    sum[1] += v[1][i];
                }
                if (sum[1] < sum[0]) {
                    winner = 0;
                    break;
                }
                ++i;
            }
            win |= winner == 0;
        }
        static int id = 0;
        printf("Case %d: %s\n", ++id, win ? "Takeover Incorporated" : "Buyout Limited");
    }
    return 0;
}
