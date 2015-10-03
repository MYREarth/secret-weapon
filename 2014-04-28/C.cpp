#include<queue>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

long long n, m, k, w, s;

const int K = 100005;

struct Toy {
    long long p, h, cnt;

    void in() {
        scanf("%lld%lld%lld", &p, &h, &cnt);
    }
} toy[K];

bool cmp(const Toy &a, const Toy &b) {
    return a.h > b.h;
}

bool operator < (const Toy &a, const Toy &b) {
    return a.p > b.p;
}

int p;
long long ans;

priority_queue<Toy> heap;

void putin(long long lev) {
    while (p < k && toy[p].h >= lev) {
        heap.push(toy[p]);
        ++p;
    }
}

void cal(long long &cnt) {
    while (heap.size() && cnt) {
        Toy t = heap.top();
        heap.pop();
        long long tmp = min(cnt, t.cnt);
        ans += t.p * tmp;
        t.cnt -= tmp, cnt -= tmp;
        if (t.cnt > 0) {
            heap.push(t);
        }
    }
}

int main() {
    scanf("%lld%lld%lld%lld%lld", &n, &m, &k, &w, &s);
    for (int i = 0; i < k; ++i) {
        toy[i].in();
    }
    long long g = __gcd(w, m),
              b = s / (w / g),
              left = (s % (w / g) * m + w - 1) / w,
              l = b / g,
              leftover = b % g * (m / g) + left;
    sort(toy, toy + k, cmp);
    p = 0;
    long long cur = leftover, curlev = l + 1;
    putin(curlev);
    cal(cur);
    if (cur > 0) {
        printf("-1\n");
        return 0;
    }
    curlev = l;
    putin(curlev);
    for (; curlev > 0;) {
        long long delta = (p < k) ? (curlev - toy[p].h) : curlev;
        cur = delta * m;
        cal(cur);
        if (cur > 0) {
            printf("-1\n");
            return 0;
        }
        curlev -= delta;
        putin(curlev);
    }
    printf("%lld\n", ans);
    return 0;
}
