#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

struct TrieNode {
    int next[4], sum, cnt;

    TrieNode () {
        memset(next, -1, sizeof(next));
        sum = 0, cnt = 0;
    }
};

const int N = 1000005;

int top;
TrieNode pool[N];

int l;
char s[N];

void insert(int x, int p) {
    if (p == l) {
        ++pool[x].cnt;
        return;
    }
    if (pool[x].next[s[p] - 'a'] == -1) {
        pool[x].next[s[p] - 'a'] = top++;
    }
    ++pool[x].sum;
    insert(pool[x].next[s[p] - 'a'], p + 1);
}

int ask(int x, int p) {
    if (p == l) {
        return pool[x].sum;
    }
    if (pool[x].next[s[p] - 'a'] == -1) {
        return 0;
    }
    return ask(pool[x].next[s[p] - 'a'], p + 1);
}

int main() {
    top = 1;
    int n;
    scanf("%d", &n);
    while (n--) {
        scanf("%s", s);
        l = strlen(s);
        if (s[0] == '+') {
            insert(0, 1);
        } else {
            printf("%d\n", ask(0, 1));
        }
    }
    return 0;
}
