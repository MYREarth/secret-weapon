#include<map>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

struct Big {
    long long a, b;

    Big(long long a = 0, long long b = 0) : a(a), b(b) {};
};

const long long MOD = 1000000000000000000ll;

Big operator + (Big a, Big b) {
    return Big((a.a + b.a) % MOD, (a.b + b.b + (a.a + b.a) / MOD));
}

Big operator / (Big a, long long b) {
    Big ret;
    ret.b = a.b / b;
    ret.a = a.a / b + a.b % b * (MOD / b) + a.b % b * (MOD % b) / b;
    ret.b += ret.a / MOD;
    ret.a %= MOD;
    return ret;
}

long long operator % (Big a, long long b) {
    return (a.b % b * (MOD % b) % b + a.a % b) % b;
}

int main() {
    int n;
    scanf("%d", &n);
    if (n==0)
    {
        printf("Yes\n");
        return(0);
    }
    vector<pair<int, long long> > v(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d%lld", &v[i].first, &v[i].second);
    }
    Big add = Big(0); 
    sort(v.begin(), v.end()); 
    long long cur = v.back().first;
    while (cur) {
        Big tmp = add;
        if (v.size() && cur == v.back().first) {
            tmp = tmp + Big(v.back().second);
            v.pop_back();
        }
        if (tmp % cur) {
            printf("No\n");
            return 0;
        }
        add = add + tmp / cur;
        --cur;
    }
    printf("Yes\n");
    return 0;
}
