#include <cassert>
#include <cstdio>
#include <cstring>
#include <bitset>

const int N     = 2014;
const int MAGIC = 127;

typedef unsigned long long ULL;

int  n;
char string[N];

bool graph[N][N];
ULL  hash[N + N + 1], power[N + 1];

ULL get_hash(int s, int l) {
    return hash[s] - hash[s + l] * power[l];
}

typedef std::bitset <N> Bitset;

Bitset in[N], out[N];

int main() {
    power[0] = 1;
    for (int i = 1; i <= N; ++ i) {
        power[i] = power[i - 1] * MAGIC;
    }
    scanf("%s", string);
    n = strlen(string);
    memset(hash, 0, sizeof(hash));
    for (int i = n + n - 1; i >= 0; -- i) {
        hash[i] = hash[i + 1] * MAGIC + string[i % n];
    }
    memset(graph, 0, sizeof(graph));
    for (int i = 0; i < n; ++ i) {
        for (int length = 1; length < n; ++ length) {
            int j = (i + length) % n;
            int low = 0;
            int high = std::min(length, n - length);
            while (low < high) {
                int middle = low + high + 1 >> 1;
                if (get_hash(i, middle) == get_hash(j, middle)) {
                    low = middle;
                } else {
                    high = middle - 1;
                }
            }
            if (low < std::min(length, n - length)) {
                graph[i][j] = string[(i + low) % n] < string[(j + low) % n];
            } else {
                graph[i][j] = length < n - length;
            }
        }
    }
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < n; ++ j) {
            if (graph[i][j]) {
                out[i].set(j);
            }
            if (graph[j][i]) {
                in[i].set(j);
            }
        }
    }
    int result = 0;
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < n; ++ j) {
            if (i != j && graph[i][j]) {
                result += (in[i] & out[j]).count();
            }
        }
    }
    assert(result % 3 == 0);
    printf("%d\n", result / 3);
    return 0;
}
