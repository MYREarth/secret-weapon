#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int n, k, rk, d;

#define pow POW

long long pow[11];
vector<long long> a;
vector<int> la, last;

inline int len(long long a) {
    int ret = 0;
    while (a) {
        a /= 10;
        ++ret;
    }
    return ret;
}

void init() {
    pow[0] = 1;
    for (int i = 1; i <= 10; ++i) {
        pow[i] = pow[i - 1] * 10;
    }
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; ++i) {
        int t;
        scanf("%d", &t);
        a.push_back(t);
        la.push_back(len(t));
        last.push_back(0);
    }
    vector<int> tmp = la;
    sort(tmp.begin(), tmp.end());
    d = tmp[k - 1];
    rk = 0;
    while (rk < k && tmp[k - 1 - rk] == d) {
        ++rk;
    }
    int cnt = 0;
    for (int i = n - 1; i >= 0; --i) {
        if (la[i] == d) {
            last[i] = cnt++;
        }
    }
}

vector<long long> nums;
vector<int> lens;

long long getnum(int p, int l) {
    int i = p / 10, j = p % 10;
    long long ret = nums[i] % pow[lens[i] - j];
    if (l > lens[i] - j) {
        ret *= pow[l - (lens[i] - j)];
        ret += nums[i + 1] / pow[lens[i + 1] - (l - (lens[i] - j))];
    } else if (l < lens[i] - j) {
        ret /= pow[lens[i] - j - l];
    }
    return ret;
}

void trunc(int p) {
    int i = p / 10;
    while (nums.size() > i + 1) {
        nums.pop_back();
        lens.pop_back();
    }
    if (p % 10 == 0) {
        nums.pop_back();
        lens.pop_back();
    } else {
        nums[nums.size() - 1] /= pow[lens.back() - p % 10];
        lens[lens.size() - 1]  = p % 10;
    }
}

void append(long long a) {
    int l = len(a);
    if (nums.size() == 0) {
        nums.push_back(a);
        lens.push_back(l);
        return;
    }
    if (lens.back() + l <= 10) {
        nums[nums.size() - 1] *= pow[l];
        nums[nums.size() - 1] += a;
        lens[lens.size() - 1] += l;
    } else {
        nums[nums.size() - 1] *= pow[10 - lens.back()];
        nums[nums.size() - 1] += a / pow[l - (10 - lens.back())];
        nums.push_back(a % pow[l - (10 - lens.back())]);
        lens.push_back(l - (10 - lens.back()));
        lens[lens.size() - 2] = 10;
    }
}

vector<pair<int, int> > pos;

void print() {
    for (int i = 0; i < (int)nums.size(); ++i) {
        int zero = lens[i] - len(nums[i]);
        for (int j = 0; j < zero; ++j) {
            printf("0");
        }
        printf("%lld", nums[i]);
        //printf("|");
    }
    printf("\n");
}

int main() {
    init();
    pos.push_back(make_pair(0, rk));
    for (int i = 0; i < n; ++i) {
/*
cout << i << endl;
print();
for (int j = 0; j < (int)pos.size(); ++j) {
    printf("%d %d\n", pos[j].first, pos[j].second);
}
*/
        int l = la[i];
        long long num = a[i];

//cout << "New Entry" << ' ' << l << ' ' << num << endl;
        if (l < d) {
            continue;
        } else if (l > d) {
            vector<pair<int, int> > npos;
            append(num);
            npos.push_back(make_pair(pos[0].first + l, pos[0].second));
            for (int j = 1; j < (int)pos.size(); ++j) {
                long long block = getnum(pos[j].first, l);
                if (num < block) {
                    continue;
                } else if (num > block) {
                    trunc(pos[j].first);
                    append(num);
                    npos.clear();
                    npos.push_back(make_pair(pos[j].first + l, pos[j].second));
                } else {
                    npos.push_back(make_pair(pos[j].first + l, pos[j].second));
                }
            }
            sort(npos.begin(), npos.end());
            npos.erase(unique(npos.begin(), npos.end()), npos.end());
            reverse(npos.begin(), npos.end());
            pos = npos;
        } else if (l == d) {
            vector<pair<int, int> > npos;
            int left = last[i];
            if (left >= pos[0].second) {
                append(num);
                npos.push_back(make_pair(pos[0].first + l, pos[0].second));
            }
            if (pos[0].second > 0) {
                npos.push_back(make_pair(pos[0].first, pos[0].second - 1));
            }
            for (int j = 1; j < (int)pos.size(); ++j) {
                long long block = getnum(pos[j].first, l);
//cout << "CUT" << ' ' << pos[j].first << ' ' << block << endl;
                if (left >= pos[j].second) {
                    if (num < block) {
                    } else if (num > block) {
                        trunc(pos[j].first);
                        append(num);
                        npos.clear();
                        npos.push_back(make_pair(pos[j].first + l, pos[j].second));
                    } else {
                        npos.push_back(make_pair(pos[j].first + l, pos[j].second));
                    }
                }
                if (pos[j].second > 0) {
                    npos.push_back(make_pair(pos[j].first, pos[j].second - 1));
                }
            }
            sort(npos.begin(), npos.end());
            npos.erase(unique(npos.begin(), npos.end()), npos.end());
            reverse(npos.begin(), npos.end());
            pos = npos;
        }
    }
    print();
    return 0;
}
