#include<vector>
#include<cstdio>
#include<string>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

struct Key {
    string s;
    int r;

    Key(string s = "", int r = 0) : s(s), r(r) {}
};

Key max(const Key &a, const Key &b) {
    return (a.r > b.r || a.r == b.r && a.s < b.s) ? a : b;
}

struct Node {
    Key cur, sum;
    Node* next[26];

    Node () {
        for (int i = 0; i < 26; ++i) {
            next[i] = NULL;
        }
    }
};

Node root;

void insert(Node *&x, int i, const Key &cur) {
    int l = cur.s.size();
    if (x == NULL) {
        x = new Node();
        if (i == l) {
            x->cur = cur;
        } else {
            x->sum = cur;
            insert(x->next[cur.s[i] - 'a'], i + 1, cur);
        }
    } else {
        if (i == l) {
            x->cur = cur;
            return;
        }
        x->sum = max(x->sum, cur);
        insert(x->next[cur.s[i] - 'a'], i + 1, cur);
    }
}

int ask(Node *&x, int i, const string &s, int cover = 0) {
    if (cover) {
        return ask(x->next[s[i] - 'a'], i + 1, s, cover - 1);
    }
    int l = s.size();
    if (x == NULL) {
        x = new Node();
        if (i == l) {
            x->cur = Key(s, 0);
            return 1;
        } else {
            x->sum = Key(s, 0);
            return 1 + ask(x->next[s[i] - 'a'], i + 1, s);
        }
    } else {
        if (i == l) {
            if (x->cur.s.size() == 0) {
                x->cur.s = s;
            }
            return 1;
        }
        if (s == x->sum.s) {
            return 1;
        } else if (!x->sum.s.empty() && x->sum.s.size() < s.size() && s.substr(0, x->sum.s.size()) == x->sum.s) {
            return 1 + ask(x->next[s[i] - 'a'], i + 1, s, (int)x->sum.s.size() - i - 1);
        } else {
            return 1 + ask(x->next[s[i] - 'a'], i + 1, s);
        }
    }
}

void update(Node *&x, int i, const string &s) {
//cout << i << ' ' << s << ' ' << s.size() << endl;
    if (i == s.size()) {
        ++x->cur.r;
    } else {
        //cout << "HI" << ' ' << s[i] - 'a' << endl;
        update(x->next[s[i] - 'a'], i + 1, s);
        if (i + 1 == s.size()) {
            x->sum = max(x->sum, x->next[s[i] - 'a']->cur);
        } else {
            x->sum = max(x->sum, x->next[s[i] - 'a']->sum);
        }
    }
}

int main() {
    freopen("goondex.in", "r", stdin);
    freopen("goondex.out", "w", stdout);
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        char buf[15];
        int r;
        scanf("%s%d", buf, &r);
        insert(root.next[buf[0] - 'a'], 1, Key(buf, r));
    }
    int q = 0;
    scanf("%d", &q);
    int sum1 = 0, sum2 = 0;
    while (q--) {
//cout << "HAHA" << endl;
        char buf[15];
        scanf("%s", buf);
        sum2 += strlen(buf) + 1;
        int delta = 0;
        sum1 += 1 + (delta = ask(root.next[buf[0] - 'a'], 1, buf));
//cout << delta + 1 << endl;
//cout << "HEHE" << endl;
        update(root.next[buf[0] - 'a'], 1, buf);
//cout << "HIHI" << endl;
    }
    printf("%d %d\n", sum1, sum2);
    return 0;
}
