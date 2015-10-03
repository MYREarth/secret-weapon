#include<set>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 100005;
int n;
char s[N];

const int C = 26;

struct State;

int top;
State *pool[N << 1];
vector<int> sub[N << 1];
set<int> *mem[N << 1];

struct State {
    int length, id;
    State *parent;
    State *go[C];

    State(int length) : length(length), id(top), parent(NULL) {
        pool[top] = this;
        mem[top] = new set<int>;
        ++top;
        memset(go, 0, sizeof(go));
    }

    State *extend(State *start, int token) {
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

set<int> *merge(set<int> *a, set<int> *b) {
    if (a->size() > b->size()) {
        swap(a, b);
    }
    for (set<int>::iterator it = a->begin(); it != a->end(); ++it) {
        b->insert(*it);
    }
    return b;
}

int ans[N];

int main() {
    freopen("substr.in", "r", stdin);
    freopen("substr.out", "w", stdout);
    scanf("%s", s);
    n = strlen(s);
    State *root = new State(0), *last = root;
    for (int i = n - 1; i >= 0; --i) {
//cout << 2 << ' ' << i << ' ' << s[i] << endl;
        last = last->extend(root, s[i] - 'a');
    }
    State *cur = root;
    vector<pair<int, int> > c;
    for (int i = n - 1; i >= 0; --i) {
//cout << 1 << ' ' << i << endl;
        cur = cur->go[s[i] - 'a'];
        int id = cur->id;
        mem[id]->insert(i);
    }
    for (int i = 1; i < top; ++i) {
        c.push_back(make_pair(pool[i]->length, pool[i]->id));
    }
    sort(c.begin(), c.end());
    for (int i = (int)c.size() - 1; i >= 0; --i) {
//cout << i << endl;
        State *cur = pool[c[i].second];
        int l0 = cur->parent->length, l1 = cur->length, id = cur->id, fa = cur->parent->id;
        if (mem[id]->size()) {
            int l = *(*mem[id]).begin(), r = *(*mem[id]).rbegin(), mid = l + r >> 1;
            int maxlen = 0;
            set<int>::iterator it = (*mem[id]).lower_bound(mid);
            if (it != (*mem[id]).end()) {
                int p = *it;
                maxlen = max(maxlen, min(r - p, p - l));
            }
            it = (*mem[id]).upper_bound(mid);
            if (it != (*mem[id]).end()) {
                int p = *it;
                maxlen = max(maxlen, min(r - p, p - l));
            }
            if (it != (*mem[id]).begin()) {
                --it;
                int p = *it;
                maxlen = max(maxlen, min(r - p, p - l));
            }
            maxlen = min(maxlen, l1);
            if (maxlen > l0) {
                ++ans[l0 + 1];
                --ans[maxlen + 1];
            }
            mem[fa] = merge(mem[fa], mem[id]);
        }
    }
    long long sum = 0;
    for (int i = 1; i * 3 <= n; ++i) {
        sum += ans[i];
        printf("%lld%c", sum, i == n ? '\n' : ' ');
    }
    return 0;
}
