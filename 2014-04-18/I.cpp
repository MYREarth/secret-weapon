#include<map>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

map<pair<int, int>, map<int, int> > table;

int cnt;

struct Record {
    int uid, cid, ct, heu, aid, st, cf, stamp;

    Record(int uid, int cid, int ct, int heu, int aid, int st, int cf) : uid(uid), cid(cid), ct(ct), heu(heu), aid(aid), st(st), cf(cf) {
        stamp = cnt++;
    }
};

bool operator < (const Record &a, const Record &b) {
    if (a.heu != b.heu) {
        return a.heu < b.heu;
    }
    if (a.uid != b.uid) {
        return a.uid < b.uid;
    }
    if (a.cid != b.cid) {
        return a.cid < b.cid;
    }
    if (a.ct != b.ct) {
        return a.ct < b.ct;
    }
    if (a.aid != b.aid) {
        return a.aid < b.aid;
    }
    if (a.st != b.st) {
        return a.st < b.st;
    }
    return a.stamp < b.stamp;
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i) {
        int uid, cid, ct, heu;
        scanf("%d%d%d%d", &uid, &cid, &ct, &heu);
        table[make_pair(uid, cid)][ct] = heu;
    }
    vector<Record> ans;
    for (int i = 0; i < m; ++i) {
        int uid, cid, aid, st, cf;
        scanf("%d%d%d%d%d", &uid, &cid, &aid, &st, &cf);
        map<int, int>::iterator find = table[make_pair(uid, cid)].lower_bound(st);
        if (find == table[make_pair(uid, cid)].begin()) {
            continue;
        }
        --find;
        ans.push_back(Record(uid, cid, find->first, find->second, aid, st, cf));
    }
    if (ans.size()) {
        sort(ans.begin(), ans.end());
    }
    printf("%d\n", (int)ans.size());
    for (int i = 0; i < (int)ans.size(); ++i) {
        printf("%d %d %d %d %d %d %d\n", ans[i].uid, ans[i].cid, ans[i].ct, ans[i].heu, ans[i].aid, ans[i].st, ans[i].cf);
    }
    return 0;
}
