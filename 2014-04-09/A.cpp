#include<vector>
#include<cstdio>
#include <cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int dx[6] = {1, -1,  0, 0, 1, -1};
const int dy[6] = {0,  0, -1, 1, -1, 1};
const int N = 100005;
int n, x[N], y[N];

long long dist(int x0, int y0, int i) {
    long long dx = std::abs(x0 - x[i]);
    long long dy = std::abs(y0 - y[i]);
    long long dz = std::abs(((long long)x0 + y0) - ((long long)x[i] + y[i]));
    return dx + dy + dz - std::max(dx, std::max(dy, dz));
}

long long dist(int x, int y) {
    long long ret = 0;
    for (int i = 0; i < n; ++i) {
        ret += dist(x, y, i);
    }
    return ret;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    scanf("%d", &n);
    vector<int> xx, yy, zz;
    for (int i = 0; i < n; ++i) {
        scanf("%d%d", x + i, y + i);
        xx.push_back(x[i]);
        yy.push_back(y[i]);
        zz.push_back(x[i] + y[i]);
    }
    sort(xx.begin(), xx.end());
    sort(yy.begin(), yy.end());
    sort(zz.begin(), zz.end());
    int ansx = zz[n / 2] - yy[n / 2], ansy = zz[n / 2] - xx[n / 2], tmpx, tmpy;
    long long ansd = dist(ansx, ansy), tmpd;
    do {
        bool flag = true;
        for (int i = 0; i < 6 && flag; ++i) {
            tmpx = ansx + dx[i], tmpy = ansy + dy[i];
printf("%d %d\n", tmpx, tmpy);
            tmpd = dist(tmpx, tmpy);
            if (tmpd < ansd) {
                ansx = tmpx, ansy = tmpy;
                flag = false;
            }
        }
        if (flag) {
            break;
        }
    } while (true);
    printf("%d %d\n", ansx, ansy);
    return 0;
}
