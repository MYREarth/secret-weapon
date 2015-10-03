#include<map>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

map<unsigned long long, vector<pair<int, int> > > hash;
char maps[1005][1005];
int h[1005][1005];

int cal(long long i, long long j) {
    unsigned long long where = i * 1000000 + j;
    unsigned hash = 0;
    for (int k = 0; k < 5; ++k) {
        hash += unsigned((where >> (8 * k)) & 255);
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return (hash >> 27) & 1;
}

bool check(int x, int y) {
    for (int i = 0; i < 1000; ++i) {
        for (int j = 0; j < 1000; ++j) {
            if (cal(x + i, y + j) != maps[i][j] - '0') {
                return false;
            }
        }
    }
    return true;
}

int main() {
    /*
    int a, b;
    scanf("%d%d", &a, &b);
    for (int i = 0; i < 1000; ++i) {
        //scanf("%s", maps[i]);
        for (int j = 0; j < 1000; ++j) {
            maps[i][j] = '0' + cal(a + i, b + j);
        }
    }
    */
    freopen("submatrix.in", "r", stdin);
    freopen("submatrix.out", "w", stdout);
    for (int i = 0; i < 1000; ++i) {
        scanf("%s", maps[i]);
    }
    for (int i = 0; i < 1000; ++i) {
        for (int j = 0; j < 1000 - 8; ++j) {
            h[i][j] = 0;
            for (int k = 0; k < 8; ++k) {
                h[i][j] = h[i][j] << 1 | maps[i][j + k] - '0';
            }
        }
    }
    for (int i = 0; i < 1000 - 8; ++i) {
        for (int j = 0; j < 1000 - 8; ++j) {
            unsigned long long p = 0;
            for (int k = 0; k < 8; ++k) {
                p = p << 8 | h[i + k][j];
            }
            hash[p].push_back(make_pair(i, j));
        }
    }
    for (int i = 0; i * 992 + 8 < 1000000; ++i) {
        for (int j = 0; j * 992 + 8 < 1000000; ++j) {
            unsigned long long p = 0;
            for (int x = 0; x < 8; ++x) {
                for (int y = 0; y < 8; ++y) {
                    p = p << 1 | cal(i * 992 + x, j * 992 + y);
                }
            }
            if (hash.count(p)) {
                vector<pair<int, int> > &tmp = hash[p];
                for (int k = 0; k < (int)tmp.size(); ++k) {
                    int x = i * 992 - tmp[k].first, y = j * 992 - tmp[k].second;
                    if (check(x, y)) {
                        printf("%d %d\n", x, y);
                        return 0;
                    }
                }
            }
        }
    }
    printf("ERROR!\n");
    return 0;
}
