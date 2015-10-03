#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>
#include <algorithm>

const int N = 100001;

int       node_count, key[N], weight[N], children[N][2], root[2];
long long count[N], size[N], sum[N];

void update(int &x) {
    size[x] = size[children[x][0]] + count[x] + size[children[x][1]];
    sum[x]  = sum[children[x][0]] + key[x] * count[x] + sum[children[x][1]];
}

void rotate(int &x, int t) {
    int y = children[x][t];
    children[x][t] = children[y][1 ^ t];
    children[y][1 ^ t] = x;
    update(x);
    update(y);
    x = y;
}

void insert(int &x, int k, int v) {
    if (x) {
        if (k == key[x]) {
            count[x] += v;
        } else {
            int t = key[x] < k;
            insert(children[x][t], k, v);
            if (weight[children[x][t]] < weight[x]) {
                rotate(x, t);
            }
        }
    } else {
        x = ++ node_count;
        key[x] = k;
        count[x] = v;
        weight[x] = rand();
    }
    update(x);
}

int find_kth(int &x, long long k) {
    assert(x && 1 <= k && k <= size[x]);
    if (k <= size[children[x][0]]) {
        return find_kth(children[x][0], k);
    }
    if (k <= size[children[x][0]] + count[x]) {
        return key[x];
    }
    return find_kth(children[x][1], k - size[children[x][0]] - count[x]);
}

long long get_count(int &x, int k) {
    if (x) {
        if (key[x] >= k) {
            return get_count(children[x][0], k);
        }
        return size[children[x][0]] + count[x] + get_count(children[x][1], k);
    } else {
        return 0;
    }
}

long long get_sum(int &x, long long k) {
    if (x) {
        if (k <= size[children[x][0]]) {
            return get_sum(children[x][0], k);
        }
        if (k <= size[children[x][0]] + count[x]) {
            return sum[children[x][0]] + key[x] * (k - size[children[x][0]]);
        }
        return sum[children[x][0]] + key[x] * count[x] + get_sum(children[x][1], k - size[children[x][0]] - count[x]);
    } else {
        assert(k == 0);
        return 0;
    }
}

long long search(int &x, long long bc) {
    if (x) {
        long long sc = get_count(root[0], key[x]);
        long long offset = sc - (bc + count[x] + size[children[x][1]]);
        if (offset == 0) {
            return sc;
        }
        if (offset < 0) {
            return std::max(std::min(sc, sc - offset), search(children[x][1], bc));
        } else {
            return std::max(std::min(sc, sc - offset), search(children[x][0], bc + count[x] + size[children[x][1]]));
        }
    } else {
        return 0;
    }
}

long long work() {
    long long rank = search(root[1], 0);
    return (sum[root[1]] - get_sum(root[1], size[root[1]] - rank)) - get_sum(root[0], rank);
}

int main() {
    node_count = 0;
    weight[0] = INT_MAX;
    size[0] = sum[0] = 0;
    root[0] = root[1] = 0;
    char buffer[5];
    while (scanf("%s", buffer) == 1) {
        if (*buffer == 'e') {
            break;
        }
        int k, v;
        scanf("%d%d", &k, &v);
        insert(root[*buffer == 'b'], v, k);
        printf("%lld\n", work());
        fflush(stdout);
    }
    return 0;
}
