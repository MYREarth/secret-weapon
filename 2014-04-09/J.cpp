#include<map>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 100005;

int cra[N], box[N], lb[5], lc[5];

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    long long n, m, k, ans = 0;
    cin >> n >> m >> k;
    if (n >= k) {
        cout << m << endl;
        return 0;
    }
    cra[0] = n, box[0] = k;
    int pos = 0;
    while (pos < m) {
        if (box[pos] + box[pos + 1] == k && cra[pos] + cra[pos + 1] == n) {
            long long round = max(box[pos + 0] / (cra[pos + 0] + cra[pos + 1]) - 2, 0);
            box[pos] -= round * (cra[pos + 0] + cra[pos + 1]);
            box[pos + 1] += round * (cra[pos + 0] + cra[pos + 1]);
            ans += round * 2;
        }
        int sumb = 0, sumk = 0, cnt = 0;
        for (int i = 0; sumb < k || sumk < n; ++i) {
            sumb += box[pos + i], sumk += cra[pos + i], ++cnt;
            lb[i] = box[pos + i], lc[i] = cra[pos + i];
            box[pos + i] = cra[pos + i] = 0;
        }
        for (int i = 0; i < cnt; ++i) {
            for (int j = 0; j < cnt; ++j) {
                int match = min(lb[i], lc[j]);
                lb[i] -= match, lc[j] -= match;
                if (j < i) {
                    box[pos + i] += match;
                    cra[pos + j + 1] += match;
                } else if (j == i) {
                    box[pos + i + 1] += match;
                    cra[pos + j + 1] += match;
                } else if (j > i) {
                    box[pos + i] += match;
                    cra[pos + j - 1] += match;
                }
            }
            box[pos + i] += lb[i];
        }
        ++ans;
        while (box[pos] == 0) {
            ++pos;
        }
    }
    cout << ans << endl;
    //cout << (2 * k * m + n - 1) / n - m << endl;
    return 0;
}
