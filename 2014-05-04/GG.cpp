#include<set>
#include<ctime>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int n, s;

char buf[60];

long long in() {
    //scanf("%s", buf);
    long long ret = 0;
    for (int i = 0; i < n; ++i) {
        ret = (ret << 1) | (rand() & 1);//(buf[i] - '0');
    }
    return ret;
}

int main() {
srand((unsigned)time(NULL));
    scanf("%d%d", &n, &s);
    long long mask = 0, cmask = (1ll << n) - 1;
    for (int i = 0; i < s; ++i) {
        int p = i ? rand() % n + 1 : 1;
        printf("%d ", p);
        //scanf("%d", &p);
        mask |= (1ll << (n - p));
    }
cout << endl;
    long long cur = in(), tar = in();
cout << cur << ' ' << tar << endl;
    set<long long> vis;
    while (!vis.count(cur)) {
        vis.insert(cur);
        cur = ((cur << 1) | __builtin_parity(cur & mask)) & cmask;
    }
    printf("%d\n", (int)vis.size());
    return 0;
}
