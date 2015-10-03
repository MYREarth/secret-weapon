#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 55;

int n;
char a[N], b[N];

int last_return;

bool succ;

void dup(int pos) {
    if (!succ) {
        printf("dup %d\n", pos + 1);
        fflush(stdout);
        scanf("%d", &last_return);
    }
    if (last_return == -1) {
        succ = true;
        return;
    }
    --last_return;
    a[last_return] = a[pos];
}

void clr(int pos) {
    if (!succ) {
        printf("clr %d\n", pos + 1);
        fflush(stdout);
        a[pos] = '.';
        scanf("%d", &last_return);
    }
    if (last_return == -1) {
        succ = true;
    }
}

int findfirst(char *a, char ch) {
    for (int i = 0; i < n; ++i) {
        if (a[i] == ch) {
            return i;
        }
    }
    return -1;
}

void cover(int x, int y) {
    if (succ) {
        a[y] = a[x];
        return;
    }
    if (a[y] != '.') {
        clr(y);
    }
    vector<int> dupped;
    do {
        dup(x);
        dupped.push_back(last_return);
    } while (!succ && dupped.back() != y);
}

void exchange(int x, int y) {
    if (succ) {
        swap(a[x], a[y]);
        return;
    }
    if (x == y) {
        return ;
    }
    if (a[x] == '.') {
        cover(y, x);
        clr(y);
        return ;
    }
    if (a[y] == '.') {
        cover(x, y);
        clr(x);
        return ;
    }
    dup(x);
    int nx = last_return;
    cover(y, x);
    cover(nx, y);
    clr(nx);
}

int main() {
    scanf("%s%s", a, b);
    n = strlen(a);
    for (int i = 0; i < n && !succ; ++i) {
        if (a[i] != '.' && (findfirst(a, a[i]) != i || findfirst(b, a[i]) == -1)) {
            clr(i);
        }
    }
    for (int i = 0; i < n && !succ; ++i) {
        if (b[i] != '.' && findfirst(b, b[i]) == i) {
            exchange(i, findfirst(a, b[i]));
        }
    }
    for (int i = 0; i < n && !succ; ++i) {
        if (b[i] != '.' && a[i] != b[i]) {
            cover(findfirst(a, b[i]), i);
        }
    }
    for (int i = 0; i < n && !succ; ++i) {
        if (b[i] == '.' && a[i] != '.') {
            clr(i);
        }
    }
    return 0;
}
