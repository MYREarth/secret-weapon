#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int t, n;

const int N = 10000, NN = N * (N + 1) / 2;

int head[N], w[N];

long long sum[N+1];

short dp[NN];

inline short& f(const int &i, const int &j) {
    return dp[head[i] + j - i];
}

int solve(const int &i, const int &j,const int &fuck) {
    if (i > j) {
        return 0;
    }
    if (i == j) {
        return 1;
    }
    if (f(i, j) != -1) {
        return f(i, j);
    }
    int ret = j-i+1, l, r, s = 0, limit=(sum[j+1]-sum[i]+t-1)/t;
    if (limit>=fuck)
        return(ret);
    if (t>26)
    {
        l = upper_bound(sum+i+1,sum+j+2,sum[i]+t)-sum-1;
        s = sum[l]-sum[i];
        r = lower_bound(sum+l,sum+j+1,sum[j+1]+s-t)-sum-1;
        s+=sum[j+1]-sum[r+1];
    }
    else
    {
        l = i;
        while (l <= j && s + w[l] <= t) {
            s += w[l++];
        }
        r = j;
        while (r >= l && s + w[r] <= t) {
            s += w[r--];
        }
    }
    ret = min(ret, solve(l, r, ret - 1) + 1);
    if (ret>limit)
    {
        while (l > i) {
            s -= w[--l];
            if (s + w[r] <= t) {
                while (r >= l && s + w[r] <= t) {
                    s += w[r--];
                }
                if ((ret = min(ret, solve(l, r,ret-1) + 1)) == limit) {
                    break;
                }
            }
        }
    }
    return f(i, j) = ret;
}

int main() {
    scanf("%d%d", &t, &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", w + i);
    }
    for (int i=1;i<=n;i++)
        sum[i]=sum[i-1]+w[i-1];
    memset(dp, -1, sizeof(dp));
    int cur = 0;
    for (int i = 0; i < n; ++i) {
        head[i] = cur;
        cur += n - i;
    }
    printf("%d\n", solve(0, n - 1, n+1));
    return 0;
}
