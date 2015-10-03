#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>

const int N   = 1000;
const int MOD = (int)1e9 + 7;

int power[N * N + 1], sum[N + 1][N + 1];

void add(int &x, int a) {
    x += a;
    if (x >= MOD) {
        x -= MOD;
    }
}

int combine(int* count) {
    int ways[2][1 << 4];
    memset(ways, 0, sizeof(ways));
    int total = 0;
    ways[0][0] = 1;
    for (int type = 0; type < 1 << 4; ++ type) {
        if (count[type]) {
            total ^= 1;
            memset(ways[total], 0, sizeof(ways[total]));
            for (int mask = 0; mask < 1 << 4; ++ mask) {
                add(ways[total][mask], ways[total ^ 1][mask]);
                add(ways[total][mask | type], (long long)ways[total ^ 1][mask] * (power[count[type]] - 1) % MOD);
            }
        }
    }
    return ways[total][15];
}

int identity(int n, int m) {
    assert(n <= m);
    if (n == 1) {
        if (m == 1) {
            return 1;
        }
        assert(m >= 2);
        return power[m - 2];
    }
    assert(n >= 2 && m >= 2);
    int count[1 << 4];
    memset(count, 0, sizeof(count));
    count[1 | 2] = count[2 | 4] = count[4 | 8] = count[8 | 1] = 1;
    count[1] = count[4] = n - 2;
    count[2] = count[8] = m - 2;
    count[0] = (n - 2) * (m - 2);
    return combine(count);
}

int reflection(int n, int m) {
    if (n == 1) {
        if (m == 1) {
            return 1;
        }
        assert(m >= 2);
        return power[m - 2];
    }
    assert(n >= 2);
    if (m == 1) {
        return power[(n - 2 + 1) / 2];
    }
    assert(m >= 2);
    int count[1 << 4];
    memset(count, 0, sizeof(count));
    count[8 | 1 | 2] = count[2 | 4 | 8] = 1;
    count[1] = count[4] = (n - 2 + 1) / 2;
    count[2 | 8] = m - 2;
    count[0] = (n - 2 + 1) / 2 * (m - 2);
    return combine(count);
}

int reflection(int n) {
    if (n == 1) {
        return 1;
    }
    assert(n >= 2);
    int count[1 << 4];
    memset(count, 0, sizeof(count));
    count[1 | 2 | 4 | 8] = 1;
    count[1 | 2] = count[4 | 8] = n - 1;
    int x = n - 2;
    count[0] = (1 + x) * x / 2;
    return combine(count);
}

int rotate180(int n, int m) {
    assert(n <= m);
    if (n == 1) {
        if (m == 1) {
            return 1;
        }
        assert(m >= 2);
        return power[(m - 2 + 1) / 2];
    }
    assert(n >= 2 && m >= 2);
    int count[1 << 4];
    memset(count, 0, sizeof(count));
    count[1 | 2 | 4 | 8] = 2;
    count[1 | 4] = n - 2;
    count[2 | 8] = m - 2;
    count[0] = ((n - 2 + 1) / 2) * ((m - 2 + 1) / 2);
    return combine(count);
}

int rotate90(int n) {
    if (n == 1) {
        return 1;
    }
    assert(n >= 2);
    int count[1 << 4];
    memset(count, 0, sizeof(count));
    count[1 | 2 | 4 | 8] = n - 1;
    count[0] = ((n - 2 + 1) / 2) * ((n - 2 + 1) / 2);
    if (n & 1) {
        count[0] -= (n - 2) / 2;
    }
    return combine(count);
}

constexpr int inverse(int a) {
    return a == 1 ? 1 : (long long)(MOD - MOD / a) * inverse(MOD % a) % MOD;
}

const int INV4 = inverse(4);
const int INV8 = inverse(8);

//#define IS_DEBUG

#ifdef IS_DEBUG
#define DEBUG(command) command
#else
#define DEBUG(command)
#endif

int solve(int n, int m) {
    assert(n <= m);
    int result = identity(n, m);
DEBUG(printf("%d\n", result);)
    add(result, reflection(n, m));
DEBUG(printf("%d\n", result);)
    add(result, reflection(m, n));
DEBUG(printf("%d\n", result);)
    add(result, rotate180(n, m));
DEBUG(printf("%d\n", result);)
    if (n != m) {
        return (long long)result * INV4 % MOD;
    }
    add(result, rotate90(n) * 2 % MOD);
DEBUG(printf("%d\n", result);)
    add(result, reflection(n) * 2 % MOD);
DEBUG(printf("%d\n", result);)
    return (long long)result * INV8 % MOD;
}

void prepare() {
    memset(sum, 0, sizeof(sum));
    for (int i = 1; i <= N; ++ i) {
        for (int j = i; j <= N; ++ j) {
            sum[i][j] = solve(i, j);
        }
    }
    for (int i = 1; i <= N; ++ i) {
        for (int j = 1; j <= N; ++ j) {
            sum[i][j] = ((long long)sum[i][j] + sum[i - 1][j] + sum[i][j - 1] + MOD - sum[i - 1][j - 1]) % MOD;
        }
    }
}

int main() {
    freopen("punch.in", "r", stdin);
    freopen("punch.out", "w", stdout);
    power[0] = 1;
    for (int i = 1; i <= N * N; ++ i) {
        power[i] = (power[i - 1] << 1) % MOD;
    }
    prepare();
    int n, m;
    while (scanf("%d%d", &n, &m) == 2 && n && m) {
        if (n > m) {
            std::swap(n, m);
        }
        printf("%d\n", sum[n][m]);
    }
    return 0;
}
