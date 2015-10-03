#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int C = 26;
const int N = 10005;


struct State;

State* nodes[N << 1];

struct State {
    static int state_count;

    int id, length, count;
    State *parent;
    State *go[C];

    State(int length): length(length), count(0), parent(NULL) {
        nodes[id = state_count ++] = this;
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

int State::state_count;

State *root;

int n, m, k;
char s1[N], s2[N];

bool compare(const State *p, const State *q) {
    return p->length > q->length;
}

int stamp, vis[N << 1];
State *place[N];

int main() {
    State::state_count = 0;
    freopen("strings.in", "r", stdin);
    freopen("strings.out", "w", stdout);
    scanf("%s%s%d", s1, s2, &k);
    n = strlen(s1), m = strlen(s2);
    State *q = root = new State(0);
    for (int i = 0; i < m; ++i) {
        q = q->extend(root, s2[i] - 'a');
    }
//for (int i = 0; i <= State::state_count; ++ i) {
//    printf("%d: ", i);
//    for (int c = 0; c < 26; ++ c) {
//        if (nodes[i]->go[c]) {
//            printf("%c%d", 'a' + c, nodes[i]->go[c]->id);
//        }
//    }
//    puts("");
//}
    for (State *p = q; p != root; p = p->parent) {
        p->count ++;
    }
    std::sort(nodes, nodes + State::state_count, compare);
    for (int i = 0; i < State::state_count; ++ i) {
        State *p = nodes[i];
        for (int c = 0; c < 26; ++ c) {
            if (p->go[c]) {
                p->count += p->go[c]->count;
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        place[i] = root;
    }
    for (int len = 1; len <= n; ++len) {
        for (int i = 0; i + len - 1 < n; ++i) {
            if (place[i]) {
                place[i] = place[i]->go[s1[i + len - 1] - 'a'];
            }
        }
        ++stamp;
        for (int i = 0; i + len - 1 < n; ++i) {
            if (place[i]) {
                if (vis[place[i]->id] != stamp && place[i]->count == k) {
                    ++ans;
                    vis[place[i]->id] = stamp;
                }
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}
