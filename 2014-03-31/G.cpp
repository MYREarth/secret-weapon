#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int main() {
    freopen("garage.in", "r", stdin);
    freopen("garage.out", "w", stdout);
    long long W, H, w, h;
    cin >> W >> H >> w >> h;
    cout << ((W / w + 1) / 2) * ((H / h + 1) / 2) << endl;
    return 0;
}
