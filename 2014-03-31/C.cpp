#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>

const int N = 2000;

typedef unsigned long long Hash;

const Hash MAGIC = 257;

Hash power[N + 1];

int  n, m;
char a[N + 1], b[N + 1];
Hash aHash[N + 1], bHash[N + 1];

void prepareHash(char* a, Hash* hash, int n) {
    hash[n] = 0;
    for (int i = n - 1; i >= 0; -- i) {
        hash[i] = hash[i + 1] * MAGIC + a[i] + 1;
    }
}

Hash get(Hash* hash, int l, int r) {
    assert(l <= r);
    return hash[l] - hash[r] * power[r - l];
}

struct Result {
    int al, ar, bl, br;

    Result(int al, int ar, int bl, int br) : al(al), ar(ar), bl(bl), br(br) {}

    int length() const {
        return ar - al + br - bl;
    }
};

bool operator < (const Result &a, const Result &b) {
    return a.length() < b.length();
}

std::ostream &operator <<(std::ostream &stream, const Result &result) {
    stream << "s/";
    for (int i = result.al; i < result.ar; ++ i) {
        stream << a[i];
    }
    stream << "/";
    for (int i = result.bl; i < result.br; ++ i) {
        stream << b[i];
    }
    return stream << "/g";
}

int next[N + 1][N], indices[N];

int main() {
    power[0] = 1;
    for (int i = 1; i <= N; ++ i) {
        power[i] = power[i - 1] * MAGIC;
    }
    freopen("curiosity.in",  "r", stdin);
    freopen("curiosity.out", "w", stdout);
    gets(a);
    gets(b);
    n = strlen(a);
    m = strlen(b);
    prepareHash(a, aHash, n);
    prepareHash(b, bHash, m);
    memset(next, -1, sizeof(next));
    {
        for (int i = 1; i <= n; ++ i) {
            std::map <Hash, int> map;
            for (int j = n - i; j >= 0; -- j) {
                if (j + i + i <= n) {
                    map[get(aHash, j + i, j + i + i)] = j + i;
                }
                Hash hash = get(aHash, j, j + i);
                if (map.count(hash)) {
                    next[i][j] = map[hash];
                }
            }
        }
    }
    Result result(0, n, 0, m);
    for (int aLength = 1; aLength <= n; ++ aLength) {
        for (int i = 0; i + aLength <= n; ++ i) {
            if (next[aLength][i]) {
                int total = 0;
                for (int j = i; ~j; j = next[aLength][j]) {
                    indices[total ++] = j;
                }
                for (int j = 0; j < total; ++ j) {
                    next[aLength][indices[j]] = 0;
                }
                if ((n - m) % total == 0) {
                    int bLength = (m - (n - aLength * total)) / total;
                    if (bLength >= 0) {
                        if (aLength + bLength < result.length()) {
                            if (indices[total - 1] + bLength - (aLength - bLength) * (total - 1) <= m) {
                                break;
                            }
                            int start = indices[0];
                            Hash aPattern = get(aHash, start, start + aLength);
                            Hash bPattern = get(bHash, start, start + bLength);
                            bool valid = get(aHash, 0, start) == get(bHash, 0, start);
                            for (int i = 0; i < total && valid; ++ i) {
                                int delta = (aLength - bLength) * i;
                                valid &= get(aHash, indices[i], indices[i] + aLength) == aPattern;
                                valid &= get(bHash, indices[i] - delta, indices[i] - delta + bLength) == bPattern;
                                if (i + 1 < total) {
                                    valid &= get(aHash, indices[i] + aLength, indices[i + 1]) ==
                                        get(bHash, indices[i] - delta + bLength, indices[i + 1] - delta - (aLength - bLength));
                                } else {
                                    valid &= get(aHash, indices[i] + aLength, n) ==
                                        get(bHash, indices[i] - delta + bLength, m);
                                }
                            }
                            if (valid) {
                                result = Result(start, start + aLength, start, start + bLength);
                            }
                        }
                    }
                }
            }
        }
    }
    std::cout << result << std::endl;
    return 0;
}
