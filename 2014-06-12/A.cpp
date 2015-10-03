#include<cassert>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int n;
const int N = 1000005;
char a[N], b[N], c[N], d[N];

vector<pair<int, int> > minimize(char *s) {
    vector<pair<int, int> > ret;
    int i = 0, j = n - 1 - 1;
    while (true) {
        while (i + 1 < n && !(s[i] == 'b' && s[i + 1] == 'a')) {
            ++i;
        }
        while (j >= 0 && !(s[j] == 'a' && s[j + 1] == 'b')) {
            --j;
        }
        if (i + 1 < j) {
            ret.push_back(make_pair(j + 1, i + 1));
            swap(s[j], s[j + 1]);
            swap(s[i], s[i + 1]);
            if (i > 0) {
                --i;
            }
            if (j < n - 2) {
                ++j;
            }
        } else {
            break;
        }
    }
    return ret;
}

vector<pair<int, int> > reminimize(char *s) {
    vector<pair<int, int> > ret;
    int i = 0, j = n - 1 - 1;
    while (true) {
        while (i + 1 < n && !(s[i] == 'a' && s[i + 1] == 'b')) {
            ++i;
        }
        while (j >= 0 && !(s[j] == 'b' && s[j + 1] == 'a')) {
            --j;
        }
        if (i + 1 < j) {
            ret.push_back(make_pair(i + 1, j + 1));
            swap(s[j], s[j + 1]);
            swap(s[i], s[i + 1]);
            if (i > 0) {
                --i;
            }
            if (j < n - 2) {
                ++j;
            }
        } else {
            break;
        }
    }
    return ret;
}

vector<int> make(char *s) {
    vector<int> ret;
    int last = -1;
    for (int j = 0; j < n; ++j) {
        if (s[j] == 'a') {
            ret.push_back(j - last - 1);
            last = j;
        }
    }
    ret.push_back(n - last - 1);
    return ret;
}

vector<int> process(vector<int> v) {
    int i = 0, j = (int)v.size() - 1;
    while (true) {
        while (i + 1 < j && v[i] == 0) {
            ++i;
        }
        while (i + 1 < j && v[j] == 0) {
            --j;
        }
        if (i + 1 >= j) {
            break;
        }
        int m = min(v[i], v[j]);
        v[i] -= m, v[j] -= m;
        v[i + 1] += m, v[j - 1] += m;
    }
    return v;
}

const int BAR = 1000000;

int main() {
    scanf("%d", &n);
    scanf("%s%s", a, b);
    vector<int> va = process(make(a)), vb = process(make(b));
    if (va != vb) {
        printf("NIE\n");
        return 0;
    }
    printf("TAK\n");
    if (n <= 4000) {
        for (int i = 0; i < n; ++i) {
            c[i] = a[i], d[i] = b[i];
        }
        vector<pair<int, int> > ca = minimize(a), cb = minimize(b);
        if (ca.size() + cb.size() <= BAR) {
            printf("%d\n", (int)(ca.size() + cb.size()));
            for (int i = 0; i < (int)ca.size(); ++i) {
                printf("%d %d\n", ca[i].first, ca[i].second);
            }
            for (int i = (int)cb.size() - 1; i >= 0; --i) {
                printf("%d %d\n", cb[i].second, cb[i].first);
            }
        } else {
            ca = reminimize(c), cb = reminimize(d);
            assert(ca.size() + cb.size() <= BAR);
            printf("%d\n", (int)(ca.size() + cb.size()));
            for (int i = 0; i < (int)ca.size(); ++i) {
                printf("%d %d\n", ca[i].first, ca[i].second);
            }
            for (int i = (int)cb.size() - 1; i >= 0; --i) {
                printf("%d %d\n", cb[i].second, cb[i].first);
            }
        }
    }
    return 0;
}
