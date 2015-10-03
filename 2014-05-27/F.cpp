#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

struct Num {
    vector<int> num;

    Num() {
        num.push_back(0);
    }

    Num(vector<int> tmp) {
        num = tmp;
    }

    void in() {
        int l;
        scanf("%d", &l);
        num = vector<int>(l);
        for (int i = l - 1; i >= 0; --i) {
            scanf("%d", &num[i]);
        }
    }

    int size() {
        return num.size();
    }

    int operator[] (int i) {
        return num[i];
    }

    vector<int> multi(int a) {
        vector<int> ret;
        int left = 0;
        for (int i = 0; left || i < (int)num.size(); ++i) {
            int t = left;
            if (i < (int)num.size()) {
                t += num[i] * a;
            }
            left = t / (i + 2);
            t %= (i + 2);
            ret.push_back(t);
        }
        return ret;
    }

    vector<int> plus(vector<int> b) {
        vector<int> ret;
        int left = 0;
        for (int i = 0; left || i < (int)num.size() || i < (int)b.size(); ++i) {
            int t = left;
            if (i < (int)num.size()) {
                t += num[i];
            }
            if (i < (int)b.size()) {
                t += b[i];
            }
            left = t / (i + 2);
            t %= (i + 2);
            ret.push_back(t);
        }
        return ret;
    }

    void print() {
        while (num.size() && num.back() == 0) {
            num.pop_back();
        }
        if (num.size() == 0) {
            num.push_back(0);
        }
        for (int i = (int)num.size() - 1; i >= 0; --i) {
            printf("%d%c", num[i], i ? ' ' : '\n');
        }
    }
};

int main() {
    freopen("factoradic.in", "r", stdin);
    int t;
    scanf("%d", &t);
    while (t--) {
        Num a, b, ans;
        a.in(), b.in();
        for (int i = 1; i <= (int)b.size(); ++i) {
            a = a.multi(i);
            ans = ans.plus(a.multi(b[i - 1]));
        }
        ans.print();
    }
    return 0;
}
