#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

long long n, t;

long long cur;

long long ans, best, top;

const int N = 1000005;

long long size[N];

int main() {
    cin >> n >> t;
    priority_queue<long long> heap;
    cur = 0;
    for (long long i = 1; i <= n; ++i) {
        cur += i;
        heap.push(i);
    }
    ans = cur, best = 0, top = heap.top();
    for (long long i = 1; i < n - 1; ++i) {
        cur += t;
        long long size = 0;
        while (heap.top() > size * (i + 1) + 1) {
            cur -= heap.top();
            cur += size * (i + 1) + 1;
            heap.push(size * (i + 1) + 1);
            heap.pop();
            ++size;
        }
        if (cur < ans) {
            ans = cur;
            best = i;
            top = heap.top();
        }
    }
    cout << ans << endl;
    cout << best << endl;
    int cnt = 0;
    priority_queue<pair<long long, int> > heap2;
    for (int i = 0; i <= best; ++i) {
        size[i] = 0;
        heap2.push(make_pair(-1, i));
    }
    for (long long i = 0; i < n; ++i) {
        int u = heap2.top().second;
        heap2.pop();
        ++size[u];
        heap2.push(make_pair(-(size[u] * (u + 1) + 1), u));
    }
    for (int i = 0; i < best; ++i) {
        cnt += size[i];
        printf("%d%c", cnt, i == best - 1 ? '\n' : ' ');
    }
    return 0;
}
