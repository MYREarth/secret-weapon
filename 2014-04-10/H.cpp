#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;

int dist(int x, int y, int x0, int y0) {
    return abs(x - x0) + abs(y - y0);
}

int main() {
    int ax, ay, bx, by;
    scanf("%d%d%d%d", &ax, &ay, &bx, &by);
    int cx, cy;
    scanf("%d%d", &cx, &cy);
    puts(dist(ax, ay, bx, by) == dist(ax, ay, cx, cy) + dist(cx, cy, bx, by) ? "Yes" : "No");
    return 0;
}
