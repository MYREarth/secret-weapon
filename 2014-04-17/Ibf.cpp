#include <cstdio>
#include <cstring>
#include <map>
#include <vector>

typedef long long Long;

template <typename Key, typename Value>
using Map = std::map <Key, Value>;

const int N = 10;

Long coefficient[N][N];

Long solve(int n) {
    std::vector <std::pair <int, int>> items;
    for (int i = 1; i <= n; ++ i) {
        for (int j = 1; i + j <= n; ++ j) {
            items.push_back(std::make_pair(i, j));
        }
    }
    int m1 = (int)items.size() >> 1;
    Map <std::vector <Long>, int> map;
    for (int i = 0; i <= n + 1; ++ i) { // x^i
        for (int mask = 0; mask < 1 << m1; ++ mask) {
            std::vector <Long> sum(n + 1, 0);
            if (i <= n) {
                sum[i] ++;
            }
            for (int k = 0; k < m1; ++ k) {
                if (mask >> k & 1) {
                    int p = items[k].first;
                    int q = items[k].second;
                    for (int j = p; j <= n; ++ j) {
                        sum[j] += coefficient[q][j - p];
                    }
                }
            }
            map[sum] ++;
        }
    }
    int m2 = (int)items.size() - m1;
    Long result = 0;
    for (int i = 0; i <= n; ++ i) { // (1 - x)^i
        for (int mask = 0; mask < 1 << m2; ++ mask) {
            std::vector <Long> sum(n + 1, 0);
            sum[0] = 1;
            if (i) {
                for (int j = 0; j <= n; ++ j) {
                    sum[j] -= coefficient[i][j];
                }
            }
            for (int k = 0; k < m2; ++ k) {
                if (mask >> k & 1) {
                    int p = items[m1 + k].first;
                    int q = items[m1 + k].second;
                    for (int j = p; j <= n; ++ j) {
                        sum[j] -= coefficient[q][j - p];
                    }
                }
            }
            result += map[sum];
        }
    }
    return result;
}

Long result[N];

int main() {
    coefficient[0][0] = 1;
    for (int i = 0; i + 1 < N; ++ i) {
        for (int j = 0; j < N; ++ j) {
            if (coefficient[i][j]) {
                coefficient[i + 1][j] += coefficient[i][j];
                coefficient[i + 1][j + 1] -= coefficient[i][j];
            }
        }
    }
    for (int i = 0; i < N; ++ i) {
        result[i] = solve(i);
    }
    putchar('{');
    for (int i = 0; i < N; ++ i) {
        Long buffer = result[i];
        if (i) {
            buffer -= result[i - 1];
        }
        printf("%lld%c", buffer, ",}"[i == N - 1]);
    }
    puts("");
    return 0;
}
