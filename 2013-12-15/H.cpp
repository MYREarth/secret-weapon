#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int num(char ch) {
    if (ch >= '0' && ch <= '9') {
        return ch - '0';
    } else {
        return ch - 'A' + 10;
    }
}

int main() {
    freopen("wtf8.in", "r", stdin);
    freopen("wtf8.out", "w", stdout);
    vector<int> bytes;
    char byte[3];
    while (scanf("%s", byte) == 1) {
        bytes.push_back((num(byte[0]) << 4) + num(byte[1]));
    }
    long long ans = 0;
    int i = 0;
    while (i < bytes.size()) {
        int y = 0;
        while (bytes[i] & (1 << (7 - y))) {
            bytes[i] ^= (1 << (7 - y));
            ++y;
        }
        long long nowint = bytes[i];
        --y;
        while (y > 0) {
            --y;
            ++i;
            nowint <<= 6;
            nowint += bytes[i] & ((1 << 6) - 1);
        }
        ++i;
        ans += nowint;
    }    
    cout << ans << endl;
    return 0;
}
