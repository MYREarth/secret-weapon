#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <stack>

const int N = 1000;
const long long INF = 1000000000000000000LL;

int b, s, n, m, parameter[N], next[N];
char type[N], buffer[8];

int new_name[N];

struct Data {
    Data() : first(-1), last(-1), total(0), count(m * m, 0) {}

    Data repeat(int n) {
        for (int i = 0; i < m * m; ++ i) {
            count[i] *= n;
        }
        if (last != -1 && first != -1) {
            count[last * m + first] += n - 1;
        }
        total *= n;
        return *this;
    }

    Data &dump() {
        printf("(%d, %d, %lld\n", first, last, total);
        for (int i = 0; i < m; ++ i) {
            for (int j = 0; j < m; ++ j) {
                printf("%4lld", count[i * m + j]);
            }
            puts("");
        }
        return *this;
    }

    int first, last;
    long long total;
    std::vector <long long> count;
};

Data operator + (const Data &a, const Data &b) {
    Data result;
    for (int i = 0; i < m * m; ++ i) {
        result.count[i] = a.count[i] + b.count[i];
    }
    if (a.last != -1 && b.first != -1) {
        result.count[a.last * m + b.first] ++;
    }
    result.first = a.first != -1 ? a.first : b.first;
    result.total = a.total + b.total;
    result.last = b.last != -1 ? b.last : a.last;
    return result;
}

Data parse(int l, int r) {
    if (l == r) {
        return Data();
    } else if (type[l] == 'V') {
        Data result;
        result.total = 1;
        result.first = result.last = new_name[parameter[l]];
        return result + parse(l + 1, r);
    } else {
        return parse(l + 1, next[l]).repeat(parameter[l]) + parse(next[l] + 1, r);
    }
}

const int V = 13;

int elements[V];
long long sum[1 << V];

long long search(int mask, int group) {
    if (!mask) {
        return 0;
    }
    long long result = -INF;
    if (group < b) {
        int i = -mask & mask;
        mask &= ~i;
        for (int subset = mask; ; subset = subset - 1 & mask) {
            if (__builtin_popcount(subset) <= s - 1) {
                int new_mask = subset | i;
                result = std::max(result, sum[new_mask] + search(mask & ~subset, group + 1));
            }
            if (!subset) {
                break;
            }
        }
    }
    return result;
}

int main() {
    scanf("%d%d", &b, &s);
    n = 0;
    while (scanf("%s", buffer) == 1) {
        type[n] = *buffer;
        if (type[n] != 'E') {
            sscanf(buffer + 1, "%d", parameter + n);
        }
        n ++;
    }
    int v = 0;
    for (int i = 0; i < n; ++ i) {
        if (type[i] == 'V') {
            v = std::max(v, parameter[i]);
            parameter[i] --;
        }
    }
    std::stack <int> indices;
    for (int i = n - 1; i >= 0; -- i) {
        if (type[i] == 'R') {
            next[i] = indices.top();
            indices.pop();
        }
        if (type[i] == 'E') {
            indices.push(i);
        }
    }
    s = std::min(s, v);
    long long answer = INF;
    for (int mask = 0; mask < 1 << v; ++ mask) {
        if (__builtin_popcount(mask) == s) {
            m = 0;
            memset(new_name, -1, sizeof(new_name));
            for (int i = 0; i < v; ++ i) {
                if (~mask >> i & 1) {
                    new_name[i] = m ++;
                }
            }
            Data result = parse(0, n);
            long long extra = result.total;
            for (int i = 0; i < m; ++ i) {
                for (int j = 0; j < m; ++ j) {
                    extra += result.count[i * m + j];
                }
            }
            bool found = false;
            for (int i = 0; i < n; ++ i) {
                if (type[i] == 'V') {
                    found |= new_name[parameter[i]] != -1;
                }
            }
            extra += found;
            for (int mask = 0; mask < 1 << m; ++ mask) {
                sum[mask] = 0;
                for (int i = 0; i < m; ++ i) {
                    if (mask >> i & 1) {
                        for (int j = 0; j < m; ++ j) {
                            if (mask >> j & 1) {
                                sum[mask] += result.count[i * m + j];
                            }
                        }
                    }
                }
            }
            answer = std::min(answer, extra - search((1 << m) - 1, 1));
        }
    }
    std::cout << answer << std::endl;
    return 0;
}
