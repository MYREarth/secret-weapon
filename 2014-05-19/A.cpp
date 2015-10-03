#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

#define next NEXT

const int N = 75;
int next[N], prec[N];

int n;

bool inai[N];
int ans, best[N], top, size, s[N];

void erase(int u) {
    inai[u] = true;
    --size;
    next[prec[u]] = next[u];
    prec[next[u]] = prec[u];
}

void recover(int u) {
    inai[u] = false;
    ++size;
    next[prec[u]] = u;
    prec[next[u]] = u;
}

void go(int i) {
    if (top + size <= ans) {
        return;
    }
    if (i > n) {
        ans = top;
        for (int j = 0; j < top; ++j) {
            best[j] = s[j];
        }
        return;
    }
    vector<int> erased;
    erased.push_back(i);
    for (int j = top - 1; j >= 0; --j) {
        int k = 3 * i - 2 * s[j];
        if (k > n) {
            break;
        }
        if (!inai[k]) {
            erased.push_back(k);
        }
    }
    for (int j = 0; j < (int)erased.size(); ++j) {
        erase(erased[j]);
    }
    s[top++] = i;
    go(next[0]);
    --top;
    for (int j = (int)erased.size() - 1; j > 0; --j) {
        recover(erased[j]);
    }
    go(next[0]);
    recover(i);
}

int main() {
    int m;
    scanf("%d", &m);
    for (n = 1; n <= m; ++n) {
    ans = 0;
    for (int i = 0; i <= n + 1; ++i) {
        next[i] = i + 1;
        prec[i] = i - 1;
    }
    size = n;
    go(1);
    printf("%d\n", ans);
    for (int i = 0; i < ans; ++i) {
        printf("%d%c", best[i], i == ans - 1 ? '\n' : ' ');
    }
    }
    return 0;
}
