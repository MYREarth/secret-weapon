#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

struct Node {
    int prize, weight;
    long long num, size, sum;
    Node *ch[2];

    void update() {
        size = ch[0]->size + ch[1]->size + num;
        sum = ch[0]->sum + ch[1]->sum + num * prize;
    }
};

int cnt;
Node pool[100005];

Node *root[2], *null;

Node* newNode(int prize = 0, long long num = 0) {
    Node *ret = &pool[cnt++];
    ret->ch[0] = ret->ch[1] = null;
    ret->prize = prize;
    ret->num  = num;
    ret->weight = rand();
    return ret;
}

void rotate(Node* &x, int t) {
    Node *y = x->ch[t];
    x->ch[t] = y->ch[t ^ 1];
    y->ch[t ^ 1] = x;
    x->update();
    y->update();
    x = y;
}

void insert(Node* &x, int prize, long long num) {
    if (x == null) {
        x = newNode(prize, num);
    } else if (prize == x->prize) {
        x->num += num;
    } else {
        int t = x->prize < prize;
        insert(x->ch[t], prize, num);
        if (x->ch[t]->weight < x->weight) {
            rotate(x, t);
        }
    }
    x->update();
}

int count(Node *&x, long long bar) {
    if (bar == 0) {
        return 0;
    }
    if (bar <= x->ch[0]->size) {
        return count(x->ch[0], bar);
    }
    if (bar <= x->ch[0]->size + x->num) {
        return x->prize;
    }
    return count(x->ch[1], bar - (x->ch[0]->size + x->num));
}

long long getsum(Node *&x, long long bar) {
    if (bar == 0) {
        return 0;
    }
    if (bar <= x->ch[0]->size) {
        return getsum(x->ch[0], bar);
    }
    if (bar <= x->ch[0]->size + x->num) {
        return x->ch[0]->sum + x->prize * (bar - x->ch[0]->size);
    }
    return x->ch[0]->sum + x->num * x->prize + getsum(x->ch[1], bar - x->ch[0]->size - x->num);
}

long long solve() {
    long long l = 0, r = min(root[0]->size, root[1]->size), m;
    while (l < r) {
        m = l + r + 1 >> 1;
        int buy = count(root[1], root[1]->size - m + 1), sell = count(root[0], m);
        if (buy > sell) {
            l = m;
        } else {
            r = m - 1;
        }
    }
    return (root[1]->sum - getsum(root[1], root[1]->size - l)) - getsum(root[0], l);
}

void dump(Node *x) {
    if (x != null) {
        dump(x->ch[0]);
        printf(" (%d, %lld, %lld) ", x->prize, x->num, x->size);
        dump(x->ch[1]);
    }
}

int main() {
    null = newNode();
    null->weight = (1ll << 31) - 1;
    null->ch[0] = null->ch[1] = null;
    root[0] = root[1] = null;
    char op[5];
    while (scanf("%s", op) == 1) {
        if (op[0] == 'e') {
            return 0;
        }
        int num, prize;
        scanf("%d%d", &num, &prize);
        insert(root[op[0] == 'b'], prize, num);
        printf("%lld\n", solve());
        fflush(stdout);
    }
    return 0;
}
