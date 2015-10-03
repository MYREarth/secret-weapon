#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 1005, M = 15, L = 10005;

int n, m, ord[M][N];

vector<pair<int, int> > ans;

int stamp, use[L], cnt[L], mem[L];

bool by_cnt(int i, int j) {
    return cnt[i] != cnt[j] ? cnt[i] > cnt[j] : i < j;
}

const int INF = 1000000000;

int real_rank = 1;

void deal(vector<pair<int, vector<int> > > data, int rank, int n) {
    if (rank > n || data.size() == 1) {
        for (int i = 0; i < (int)data.size(); ++i) {
            int u = data[i].first;
            ans.push_back(make_pair(real_rank, u));
        }
        real_rank += data.size();
        return;
    }
    vector<pair<pair<int, int>, int> > tmp;
    for (int i = 0; i < (int)data.size(); ++i) {
        int major = 0, sum = 0;
        for (int j = 0; j < m; ++j) {
            int t = data[i].second[j];
            if (t <= rank) {
                ++major;
                sum += t;
            }
        }
        tmp.push_back(make_pair(make_pair(major, INF - sum), i));
    }
    sort(tmp.begin(), tmp.end());
    reverse(tmp.begin(), tmp.end());
    
    for (int i = 0; i < (int)tmp.size(); ++i) {
        vector<pair<int, vector<int> > > tmp2;
        int j = i;
        while (j < (int)tmp.size() && tmp[j].first == tmp[i].first) {
            tmp2.push_back(data[tmp[j].second]);
            ++j;
        }
        deal(tmp2, rank + 1, n);
        i = j - 1;
    }
    /*
    vector<pair<int, vector<int> > > tmp2;
    int j = 0;
    while (j < (int)tmp.size() && tmp[j].first == tmp[0].first) {
        tmp2.push_back(data[tmp[j].second]);
        ++j;
    }
    deal(tmp2, rank + 1, n);
    if (j == (int)tmp.size()) {
        return ;
    }
    tmp2.clear();
    for (int i = j; i < (int)tmp.size(); ++i) {
        tmp2.push_back(data[tmp[i].second]);
    }
    deal(tmp2, max(rank, real_rank), n);
    */
}

vector<int> burn(vector<int> couples) {
    ++stamp;
    int nn = n;
    int n = couples.size();
    if (n <= 8) {
        for (int i = 0; i < n; ++i) {
            use[couples[i]] = stamp;
            mem[couples[i]] = i;
        }
        vector<vector<int> > mark(n);
        for (int i = 0; i < m; ++i) {
            int cnt = 1;
            for (int j = 0; j < nn; ++j) {
                if (use[ord[i][j]] == stamp) {
                    mark[mem[ord[i][j]]].push_back(cnt++);
                }
            }
        }
        for (int i = 0; i < n; ++i) {
            sort(mark[i].begin(), mark[i].end());
        }
        bool out[8];
        memset(out, 0, sizeof(out));
        for (int rank = 1; real_rank <= n; ++rank) {
            vector<pair<int, int> > tmp;
            for (int j = 0; j < n; ++j) {
                if (out[j]) {
                    continue;
                }
                int cnt = 0;
                for (int k = 0; k < m; ++k) {
                    if (mark[j][k] <= rank) {
                        ++cnt;
                    }
                } 
                tmp.push_back(make_pair(cnt,  j));
            }
            sort(tmp.begin(), tmp.end());
            reverse(tmp.begin(), tmp.end());
            int major = (m + 1) / 2;
            int has_major = 0;
            while (has_major < (int)tmp.size() && tmp[has_major].first >= major) {
                ++has_major;
            }
            if (has_major == 0) {
                continue;
            } else {
                tmp.erase(tmp.begin() + has_major, tmp.end());
                vector<pair<int, vector<int> > > tmp2;
                for (int j = 0; j < (int)tmp.size(); ++j) {
                    tmp2.push_back(make_pair(couples[tmp[j].second], mark[tmp[j].second]));
                    out[tmp[j].second] = true;
                }
                deal(tmp2, rank, n);
            }
        }
        vector<int> empty;
        return empty;
    } else {
        for (int i = 0; i < n; ++i) {
            use[couples[i]] = stamp;
            cnt[couples[i]] = 0;
        }
        for (int i = 0; i < m; ++i) {
            int left = (n + 1) / 2;
            for (int j = 0; j < nn && left; ++j) {
                if (use[ord[i][j]] == stamp) {
                    ++cnt[ord[i][j]];
                    --left;
                }
            }
        }
        sort(couples.begin(), couples.end(), by_cnt);
        int left = (n + 1) / 2;
        vector<int> callback(couples.begin(), couples.begin() + left);
        for (int i = left; i < n; ++i) {
            int rank = i + 1, j = i;
            while (j < n && cnt[couples[j]] == cnt[couples[i]]) {
                ans.push_back(make_pair(rank, couples[j]));
                ++j;
            }
            i = j - 1;
        }
        return callback; 
    }
}

int main() {
    freopen("skating.in", "r", stdin);
    freopen("skating.out", "w", stdout);
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%d", &ord[i][j]);
        }
    }
    vector<int> couples;
    for (int i = 0; i < n; ++i) {
        couples.push_back(ord[0][i]);
    }
    while (couples.size()) {
        couples = burn(couples);
    }
    sort(ans.begin(), ans.end()); 
    if (ans.size() != n) {
        while (true) {
            int i = 1 * 1 + 1;
            continue;
        }
    }
    for (int i = 0; i < n; ++i) {
        printf("%d %d\n", ans[i].second, ans[i].first);
    }
    return 0;
}
