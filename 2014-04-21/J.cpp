#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

#define next NEXT

int n, k, q;

const int N = 100, Q = 1005;
int next[N][Q];
char f[N][Q];

int ord[N];

bool by_first(int i, int j) {
    return next[i][0] > next[j][0];
}

bool use[N];

int main() {
    scanf("%d%d%d", &n, &k, &q);
    for (int i = 0; i < n; ++i) {
        scanf("%s", f[i]);
        next[i][q] = q;
        for (int j = q - 1; j >= 0; --j) {
            if (f[i][j] == '0') {
                next[i][j] = j;
            } else {
                next[i][j] = next[i][j + 1];
            }
        }
        ord[i] = i;
    }
    sort(ord, ord + n, by_first);
    vector<int> start;
    for (int i = 0; i < k; ++i) {
        start.push_back(ord[i]);
        use[ord[i]] = true;
    }
    vector<pair<int, pair<int, int> > > sub;
    for (int i = 0; i < q; ++i) {
        bool correct = true;
        for (int j = 0; j < n; ++j) {
            if (use[j] && f[j][i] == '0') {
                correct = false;
            }
        }
        if (!correct) {
            puts("FAIL");
            return 0;
        }
        if (i == q - 1) {
            break;
        }
        int first = -1, second = -1;
        for (int j = 0; j < n; ++j) {
            if (use[j] && (first == -1 || next[first][i + 1] > next[j][i + 1])) {
                first = j;
            }
            if (!use[j] && (second == -1 || next[second][i + 1] < next[j][i + 1])) {
                second = j;
            }
        }
        if (first == -1 || second == -1) {
            continue;
        }
        if (next[first][i + 1] < next[second][i + 1]) {
            sub.push_back(make_pair(i + 1, make_pair(first + 1, second + 1)));
            use[first] = false;
            use[second] = true;
        }
    }
    puts("WIN");
    sort(start.begin(), start.end());
    for (int i = 0; i < k; ++i) {
        printf("%d%c", start[i] + 1, i == k - 1 ? '\n' : ' ');
    }
    printf("%d\n", (int)sub.size());
    for (int i = 0; i < (int)sub.size(); ++i) {
        printf("%d %d %d\n", sub[i].first, sub[i].second.first, sub[i].second.second);
    }
    return 0;
}
