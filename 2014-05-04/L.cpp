#include<set>
#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int n, k;

const int N = 1000005;
long long a[N];

const int K = 65;
char buf[K];

long long in() {
    scanf("%s", buf);
    long long ret = 0;
    for (int i = 0; i < k; ++i) {
        ret = (ret << 1) | (buf[i] - '0');
    }
    return ret;
}

set<long long> has, vis[2];

const int BARR = 10000000;

int main() {
    scanf("%d%d", &k, &n);
    long long s = in(), t = in();
    for (int i = 0; i < n; ++i) {
        a[i] = in();
        has.insert(a[i]);
    }
    vis[0].insert(s);
    vis[1].insert(t);
    queue<long long> q[2];
    q[0].push(s), q[1].push(t);
    int cnt = 0, BAR = BARR / k;
    bool meet = s == t;
    while (q[0].size() != 0 && q[1].size() != 0 && !meet && cnt < BAR) {
        for (int f = 0; f < 2; ++f) {
            ++cnt;
            long long cur = q[f].front();
            q[f].pop();
            for (int i = 0; i < k; ++i) {
                long long next = cur ^ (1ll << i);
                if (!has.count(next) && !vis[f].count(next)) {
                    vis[f].insert(next);
                    q[f].push(next);
                    if (vis[f ^ 1].count(next)) {
                        meet = true;
                        break;
                    }
                }
            }
        }
    }
    puts((meet || q[0].size() > 0 && q[1].size() > 0) ? "TAK" : "NIE");
    return 0;
}
