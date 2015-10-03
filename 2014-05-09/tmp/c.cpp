#include <iostream>
#include <string>
#include <cmath>
#include <cstring>

using namespace std;

typedef long long LL;

const int MAXN = 200100;

int d[2][MAXN+1];
LL S[2][MAXN+1];
LL F[2][MAXN+1];

string s;

int n;

void correct() {
    memset(S, 0, sizeof(S));
    memset(F, 0, sizeof(F));
    int l=0;
    int r=-1;
    for (int i=0; i<n; ++i) {
        int k = (i>r ? 0 : min(d[1][l+r-i], r-i)) + 1;
        while (i+k < n && i-k >= 0 && s[i+k] == s[i-k])
            k++;
        k--;
        d[1][i] = k;
        S[1][i-k]++;
        S[1][i+1]--;
        F[1][i+1]++;
        F[1][i+k+2]--;
        if (i+k > r) {
            l = i-k;
            r = i+k;
        }
    }
    l=0;
    r=-1;
    for (int i=0; i<n; ++i) {
        int k = (i>r ? 0 : min(d[0][l+r-i+1], r-i+1)) + 1;
        while (i+k-1 < n && i-k >= 0 && s[i+k-1] == s[i-k])
            k++;
        k--;
        d[0][i] = k;
        S[0][i-k]++;
        S[0][i]--;
        F[0][i+1]++;
        F[0][i+k+1]--;
        if (i+k > r) {
            l = i-k;
            r = i+k-1;
        }
    }
    for (int i=0; i<2; i++) {
        for (int j=1; j<=n; j++) {
            S[i][j] += S[i][j-1];
            F[i][j] += F[i][j-1];
        }
    }
}


int main() {
    cin >> s;
    n = s.length();
    correct();
    LL ans = 0;
    for (int i=0; i<=n; i++)
        ans += S[0][i]*F[1][i] + F[0][i]*S[1][i] + 2*S[0][i]*F[0][i] + 2*S[0][i] + S[1][i];
    cout << ans << endl;
    return 0;
}
