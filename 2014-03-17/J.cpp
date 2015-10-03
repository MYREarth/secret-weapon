#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int n, m;
vector<int> v[50];

int main() {
    int t = 1;
    while (t--) {
        scanf("%d%d", &n, &m);
        for (int i = 0; i < m; ++i) {
            v[i].clear();
            v[i].push_back(0);
            int tm;
            scanf("%d", &tm);
            for (int j = 1; j < tm; ++j) {
                int d;
                scanf("%d", &d);
                v[i].push_back(d - 1);
            }
        }
        long long ansa = 0, ansb = (long long)n * n, ansc = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < (int)v[i].size(); ++j) {
                ansc += (long long)max(n - v[i][j], 0);
            }
            for (int j = i + 1; j < m; ++j) {
                for (int ii = 0; ii < (int)v[i].size(); ++ii) {
                    for (int jj = 0; jj < (int)v[j].size(); ++jj) {
                        ansa += max(0ll, (long long)(n - v[j][jj]) - max(v[i][ii] - v[j][jj], 0)) * 2;
                    }
                }
            }
        }
        long long outk = 0, outa = 0, outb = 0;
        outk += ansa / ansb, outa = ansa % ansb, outb = ansb;
        outk += ansc / n, outa += ansc % n * n;
        outk += outa / outb, outa %= outb;
        long long g = __gcd(outa, outb);
        outa /= g, outb /= g;
        cout << outk << '+' << outa << '/' << outb << endl;
    }
    return 0;
}
