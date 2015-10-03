#include<set>
#include<queue>
#include<cstdio>
#include<climits>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 100000;
int n, m, a[N];

struct Node {
    int key, size, sum, w, mins, maxs;
    Node *ch[2];
};

set<int> st[N];
Node pool[N << 1];
queue<int> empty;

Node *null;

Node* newNode() {
    int id = empty.front();
    empty.pop();
    return &pool[id];
}

int r[N];
Node* tr[N];

void update(Node *&u) {
    u->size = u->ch[0]->size + 1 + u->ch[1]->size; 
    u->sum = __gcd(__gcd(u->ch[0]->sum, u->key), u->ch[1]->sum);
    u->mins = min(u->ch[0]->mins, u->key);
    u->maxs = max(u->ch[1]->maxs, u->key);
}

void rotate(Node *&x, int t) {
    Node *y = x->ch[t];
    x->ch[t] = y->ch[t ^ 1];
    y->ch[t ^ 1] = x;
    update(x);
    update(y);
    x = y;
}

inline int randd() {
    return ((rand() & ((1 << 16) - 1)) << 10) ^ rand();
}

void insert(Node *&u, int x) {
    if (u == null) {
        u = newNode();
        u->key = u->sum = u->mins = u->maxs = x;
        u->size = 1;
        u->ch[0] = u->ch[1] = null;
        u->w = randd();
        return;
    }
    int t = u->key < x; 
    insert(u->ch[t], x);
    update(u);
    if (u->ch[t]->w > u->w) {
        rotate(u, t);
    }
}

void erase(Node *&u, int x) {
    if (u->key == x) {
        if (u->ch[0] == null && u->ch[1] == null) {
            empty.push(u - pool);
            u = null;
        } else {
            int t = u->ch[1]->w > u->ch[0]->w;
            rotate(u, t);
            erase(u->ch[t ^ 1], x);
            update(u);
        }
        return;
    }
    int t = u->key < x;
    erase(u->ch[t], x);
    update(u);
}

int tmp[N], top;

void get(Node *&u) {
    if (u == null) {
        return;
    }
    tmp[top++] = u->key;
    get(u->ch[0]);
    get(u->ch[1]);
}

void merge(int u, int v) {
    if (tr[u]->size < tr[v]->size) {
        swap(u, v);
    }
    top = 0; 
    get(tr[v]);
    for (int i = 0; i < top; ++i) {
        erase(tr[v], tmp[i]);
        insert(tr[u], tmp[i]);
    }
    while (st[v].size()) {
        r[*st[v].begin()] = u;
        st[u].insert(*st[v].begin());
        st[v].erase(st[v].begin());
    }
}

int gcd(int u, int v) {
    if (u == 0 || v == 0) {
        return u + v;
    }
    int w = u % v;
    while (w) {
        u = v;
        v = w;
        w = u % v;
    }
    return v;
}

int getsum(Node *&u, int l, int r) {
    if (l <= u->mins && u->maxs <= r) {
        return u->sum;
    } 
    int ret = 0;
    if (r <= u->key) {
        ret = getsum(u->ch[0], l, r);
    } else if (l > u->key) {
        ret = getsum(u->ch[1], l, r);
    } else {
        ret = gcd(getsum(u->ch[0], l, r), getsum(u->ch[1], l, r));
    }
    if (l <= u->key && u->key <= r) {
        ret = gcd(ret, u->key);
    }
    return ret;
}

int getnum(Node *&u, int s) {
    if (s == u->ch[0]->size + 1) {
        return u->key;
    }
    if (s > u->ch[0]->size + 1) {
        return getnum(u->ch[1], s - u->ch[0]->size - 1);
    } else {
        return getnum(u->ch[0], s);
    }
}

int lower_bound(Node *&u, int s) {
    if (u == null) {
        return -1;
    }
    if (u->key >= s) {
        int ret = lower_bound(u->ch[0], s);
        if (ret == -1) {
            ret = u->key;
        }
        return ret;
    } else {
        return lower_bound(u->ch[1], s);
    }
}

int solve(Node *&u) {
    if (u->size <= 2) {
        return u->size;
    }
    top = 0; 
    tmp[top++] = getnum(u, 1);
    tmp[top++] = getnum(u, 2);
    int t = lower_bound(u, tmp[top - 2] + tmp[top - 1]);
    while (t != -1) {
        tmp[top++] = t;
        t = lower_bound(u, tmp[top - 2] + tmp[top - 1]);
    }
    return top; 
}


int main() {
    for (int i = 0; i < N * 2; ++i) {
        empty.push(i);
    }
    null = newNode();
    null->key = null->size = null->sum = 0;
    null->mins = INT_MAX;
    null->maxs = INT_MIN;
    null->w = -1;
    null->ch[0] = null->ch[1] = null;
    int t;
    scanf("%d", &t);
    while (t--) {
        static int id = 0;
        printf("Case #%d:\n", ++id);
        int n, m;
        scanf("%d%d", &n, &m); 
        for (int i = 0; i < n; ++i) {
            scanf("%d", a + i);
            r[i] = i;
            tr[r[i]] = null;
            st[r[i]].clear();
            st[r[i]].insert(i);
            insert(tr[r[i]], a[i]);
        }
        while (m--) {
            int op, u, v;
            scanf("%d", &op);
            if (op == 1) {
                scanf("%d%d", &u, &v); 
                --u, --v;
                if (r[u] != r[v]) {
                    merge(r[u], r[v]);
                }
            } else if (op == 2) {
                scanf("%d%d", &u, &v);
                --u, --v;
                erase(tr[r[u]], a[u]);
                st[r[u]].erase(u);
                insert(tr[r[v]], a[u]);
                st[r[v]].insert(u);
                r[u] = r[v];
            } else if (op == 3) {
                int x;
                scanf("%d%d", &u, &x);
                --u;
                erase(tr[r[u]], a[u]);
                a[u] = x;
                insert(tr[r[u]], a[u]);
            } else if (op == 4) {
                scanf("%d", &u);
                --u;
                printf("%d\n", solve(tr[r[u]]));
            } else if (op == 5) {
                int l, ri;
                scanf("%d%d%d", &u, &l, &ri);
                --u;
                int ans = getsum(tr[r[u]], l, ri);
                printf("%d\n", ans == 0 ? -1 : ans);
            }
        }
        for (int i = 0; i < n; ++i) {
            erase(tr[r[i]], a[i]);
        }
    }
    return 0;
}
