#include<map>
#include<queue>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

typedef map<long long, long long> Functionz;

struct Function {
    Functionz main;
    int delta;

    Function() {
        delta = 0;
    }

    Functionz::iterator begin() {
        return main.begin();
    }

    Functionz::iterator end() {
        return main.end();
    }

    size_t size() {
        return main.size();
    }

    void erase(Functionz::iterator it) {
        main.erase(it);
    }

    long long& operator[] (long long x) {
        return main[x];
    }

    long long botton (long long x) {
        return x + delta;
    }
};

inline Functionz::iterator getsecond(Function &a) {
    Functionz::iterator ret = a.begin();
    return ++a.begin();
}

void shrink(Function *now) {
    Function &f = *now;
    if (!f.main.count(-f.delta)) {
        f[-f.delta] = 0;
        return;
    }
    while (f.size() > 1) {
        auto first = f.begin(), second = first;
        ++second;
        if (first->second + f.botton(first->first) >= f.botton(second->first)) {
            first->second += second->second;
            f.erase(second);
        } else {
            break;
        }
    }
}


Function* addhead (Function *ff, long long p, bool untouch = false) {
    if (ff == NULL) {
        ff = new Function();
    }
    Function &f = *ff;
    if (p > 0) {
        f[-f.delta] += p;
        /*
        while (f.size() > 1) {
            auto tmp = getsecond(f);
            if (f.begin()->second >= tmp->first) {
                f.begin()->second += tmp->second;
                f.erase(tmp);
            } else {
                break;
            }
        }
        */
    } else if (p < 0) {
        shrink(&f);
        f[-f.delta] += p;
        while (f.size() > 1) {
            auto tmp = getsecond(f);
            if (f.begin()->second <= 0) {
                tmp->second += f.begin()->second;
                f.erase(f.begin());
            } else {
                break;
            }
        }
        if (f.begin()->second <= 0) {
            f.main.clear();
            f.delta = 0;
        } else {
            if (!untouch) {
                f.delta += -p;
            }
        }
    }
    return ff;
}

void add(Function &a, long long x, long long delta) {
    a[x - a.delta] += delta;
    //do front
    /*
    auto cur = a.find(x);
    while (cur != a.begin()) {
        auto front = cur;
        --front;
        if (front->second >= cur->first - front->first) {
            long long pos = front->first;
            front->second += cur->second;
            a.erase(cur);
            cur = a.find(pos);
        } else {
            break;
        }
    }
    //do next
    cur = --a.upper_bound(x);
    while (true) {
        auto next = cur;
        ++next;
        if (next == a.end()) {
            break;
        }
        if (cur->second >= next->first - cur->first) {
            long long pos = cur->first;
            cur->second += next->second;
            a.erase(next);
            cur = a.find(pos);
        }
    }
    */
}

Function* merge(Function *a, Function *b) {
    if (a == NULL) {
        return b;
    }
    if (b == NULL) {
        return a;
    }
    if (a->size() < b->size()) {
        return merge(b, a);
    }
    for (auto it = b->begin(); it != b->end(); ++it) {
        add(*a, (*b).botton(it->first), it->second);
    }
    delete b;
    return a;
}

const int N = 200005;

vector<int> edge[N], ch[N];

int dist[N], diss[N], hp[N];

void dfs(int u, int fa, int dis[]) {
    for (int j = 0; j < (int)edge[u].size(); ++j) {
        int v = edge[u][j];
        if (v == fa) {
            continue;
        }
        dis[v] = dis[u] + 1;
        dfs(v, u, dis);
    }
}

void bfs(int u, int n, int dis[]) {
    for (int i = 0; i < n; ++i) {
        dis[i] = -1;
    }
    queue<int> q;
    dis[u] = 0;
    q.push(u);
    while (q.size()) {
        int u = q.front();
        q.pop();
        for (int i = 0; i < (int)edge[u].size(); ++i) {
            int v = edge[u][i];
            if (dis[v] == -1) {
                dis[v] = dis[u] + 1;
                q.push(v);
            }
        }
    }
}

#define next NEXT

int next[N], fa[N], ii[N];

Function* c[N];

void go(int u) {
    c[u] = NULL;
    for (ii[u] = 0; ii[u] < (int)edge[u].size(); ++ii[u]) {
        if (edge[u][ii[u]] == fa[u]) {
            continue;
        }
        fa[edge[u][ii[u]]] = u;
        go(edge[u][ii[u]]);
        c[u] = merge(c[u], c[edge[u][ii[u]]]);
    }
    c[u] = addhead(c[u], hp[u]);
}

int n, t;
int main() {
    int ts;
    scanf("%d", &ts);
    while (ts--) {
        scanf("%d%d", &n, &t);
        --t;
        for (int i = 0; i < n; ++i) {
            scanf("%d", hp + i);
        }
        for (int i = 0; i < n; ++i) {
            ch[i].clear();
            edge[i].clear();
        }
        for (int i = 0; i < n - 1; ++i) {
            int u, v;
            scanf("%d%d", &u, &v);
            --u, --v;
            edge[u].push_back(v);
            edge[v].push_back(u);
        }
//cout << "BFS" << endl;
        diss[0] = 0;
        bfs(0, n, diss);
        dist[t] = 0;
        bfs(t, n, dist);
//cout << "BFS" << endl;
        for (int i = 0; i < n; ++i) {
            int u = i;
            if (diss[u] + dist[u] == diss[t]) {
                if (u == t) {
                    c
                        ntinue;
                }
                for (int j = 0; j < (int)edge[u].size(); ++j) {
                    int v = edge[u][j];
                    if (diss[v] + dist[v] == diss[t]) {
                        if (dist[v] < dist[u]) {
                            next[u] = v;
//cout << "NEXT" << ' ' << u << ' ' << v << endl;
                        }
                    } else {
//cout << "ch" << ' ' << u << ' ' << v << endl;
                        ch[u].push_back(v);
                    }
                }
            }
        }
        bool escape = true;
        Function *now = new Function();
        for (int pos = 0; ; pos = next[pos]) {
//cout << pos << endl;
            shrink(now);
cout << pos + 1 << endl;
for (auto it = (*now).begin(); it != (*now).end(); ++it) {
    cout << (*now).botton(it->first) << ' ' << it->second << endl;
}
            if ((*now)[-(*now).delta] + hp[pos] < 0) {
                escape = false;
                break;
            }
            addhead(now, hp[pos], true);
            if (pos == t) {
                break;
            }
            for (int j = 0; j < (int)ch[pos].size(); ++j) {
                int v = ch[pos][j];
//cout << pos << ' ' << v << endl;
                fa[v] = pos;
                go(v);
                now = merge(now, c[v]);
            }
        }
        delete now;
        puts(escape ? "escaped" : "trapped");
    }
    return 0;
}
