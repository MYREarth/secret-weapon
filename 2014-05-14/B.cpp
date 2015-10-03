#include <cstdio>
#include <cstring>
#include <map>

typedef long long Long;
typedef std::map <int, int> Map;

const int N = 100;
const int MOD = (int)1e9 + 7;

int n, b[N], moves;
bool visited[8];
Long a[N];

void update(Map &map, int key, int value) {
    (map[key] += value) %= MOD;
}

int count[N + 1][8];

struct Matrix {
    Matrix(bool identity = false) {
        memset(matrix, 0, sizeof(matrix));
        if (identity) {
            for (int i = 0; i < 8; ++ i) {
                matrix[i][i] = 1;
            }
        }
    }

    int* operator[](int i) {
        return matrix[i];
    }

    const int* operator[](int i) const {
        return matrix[i];
    }

    int matrix[8][8];
};

Matrix operator * (const Matrix &a, const Matrix &b) {
    Matrix c;
    for (int i = 0; i < 8; ++ i) {
        for (int j = 0; j < 8; ++ j) {
            long long result = 0;
            for (int k = 0; k < 8; ++ k) {
                result += (long long)a[i][k] * b[k][j] % MOD;
            }
            c[i][j] = result % MOD;
        }
    }
    return c;
}

Matrix power(Matrix a, long long n) {
    Matrix result(true);
    while (n) {
        if (n & 1) {
            result = result * a;
        }
        a = a * a;
        n >>= 1;
    }
    return result;
}

int main() {
    freopen("gamecount.in", "r", stdin);
    freopen("gamecount.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) {
        scanf("%lld%d", a + i, b + i);
    }
    if (true) {
        int k;
        scanf("%d", &k);
        moves = 0;
        while (k --) {
            int move;
            scanf("%d", &move);
            moves |= 1 << move - 1;
        }
    }
    Map states;
    int all = (1 << 21) - 1;
    states[all] = 1;
    memset(count, 0, sizeof(count));
    for (int i = 1; i <= N; ++ i) {
        Map new_states;
        for (auto &iterator : states) {
            int state = iterator.first;
            update(new_states, (state << 3 | 7) & all, iterator.second);
            memset(visited, 0, sizeof(visited));
            for (int k = 0; k < 6; ++ k) {
                if (moves >> k & 1) {
                    visited[state >> (3 * k) & 7] = true;
                }
            }
            int mex = 0;
            while (visited[mex]) {
                mex ++;
            }
            update(new_states, (state << 3 | mex) & all, iterator.second);
        }
        states = new_states;
        for (auto &iterator : states) {
            int state = iterator.first;
            (count[i][state & 7] += iterator.second) %= MOD;
        }
        count[i][7] = 0;
    }
    Matrix init;
    init[0][0] = 1;
    for (int i = 0; i < n; ++ i) {
        Matrix t;
        for (int j = 0; j < 8; ++ j) {
            for (int k = 0; k < 8; ++ k) {
                t[j][k] = count[b[i]][j ^ k];
            }
        }
//for (int j = 0; j < 8; ++ j) {
//    printf("%4d", count[b[i]][j]);
//}
//puts("");
        init = init * power(t, a[i]);
    }
    int result = 0;
    for (int i = 1; i < 8; ++ i) {
        (result += init[0][i]) %= MOD;
    }
    printf("%d\n", result);
    return 0;
}

