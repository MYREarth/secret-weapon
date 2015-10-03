#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 200005;
char s[N];

const int C = 26;

struct State {
    int length;
    State *parent;
    State *go[C];

    State(int length): length(length), parent(NULL) {
        memset(go, 0, sizeof(go));
    }

    State* extend(State *start, int token) {
        State *p = this;
        State *np = new State(this->length + 1);
        while (p != NULL && p->go[token] == NULL) {
            p->go[token] = np;
            p = p->parent;
        }
        if (p == NULL) {
            np->parent = start;
        } else {
            State *q = p->go[token];
            if (p->length + 1 == q->length) {
                np->parent = q;
            } else {
                State *nq = new State(p->length + 1);
                memcpy(nq->go, q->go, sizeof(q->go));
                nq->parent = q->parent;
                np->parent = q->parent = nq;
                while (p != NULL && p->go[token] == q) {
                    p->go[token] = nq;
                    p = p->parent;
                }
            }
        }
        return np;
    }
};

int main() {
    scanf("%s", s);
    int n = strlen(s);
    State *start = new State(0);
    State *last = start;
    long long ans = 0;
    for (int i = 0; i < n; ++i) {
        last = last->extend(start, s[i] - 'a');
        ans += last->length - last->parent->length;
        printf("%lld\n", ans);
    }
    return 0;
}
