#include <cstdio>
#include <cstring>
#include <utility>

const int N = 100000;

int count, key[N], children[N][2];

void print(const std::pair <bool, int> &result) {
    printf("%s %d\n", result.first ? "TRUE" : "FALSE", result.second);
}

std::pair <bool, int> insert(int depth, int &x, int k) {
    if (!x) {
        x = ++ count;
        key[x] = k;
        return std::make_pair(true, depth);
    }
    if (key[x] == k) {
        return std::make_pair(false, depth);
    }
    return insert(depth + 1, children[x][key[x] < k], k);
}

std::pair <bool, int> find(int depth, int &x, int k) {
    if (!x) {
        return std::make_pair(false, depth - 1);
    }
    if (key[x] == k) {
        return std::make_pair(true, depth);
    }
    return find(depth + 1, children[x][key[x] < k], k);
}

int find_least(int depth, int &x) {
    if (children[x][0]) {
        return find_least(depth + 1, children[x][0]);
    }
    return x;
}

std::pair <bool, int> remove(int depth, int &x, int k) {
    if (!x) {
        return std::make_pair(false, depth - 1);
    }
    if (key[x] == k) {
        if (children[x][0] && children[x][1]) {
            int y = find_least(depth + 1, children[x][1]);
            std::pair <bool, int> result = remove(depth + 1, children[x][1], key[y]);
            children[y][0] = children[x][0];
            children[y][1] = children[x][1];
            x = y;
            return result;
        }
        x = children[x][0] | children[x][1];
        return std::make_pair(true, depth);
    }
    return remove(depth + 1, children[x][key[x] < k], k);
}

int main() {
    int n;
    scanf("%d", &n);
    count = 0;
    memset(children, 0, sizeof(children));
    int root = 0;
    while (n --) {
        char type[7];
        int value;
        scanf("%s%d", type, &value);
        if (*type == 'A') {
            print(insert(1, root, value));
        } else if (*type == 'F') {
            if (root == 0) {
                puts("FALSE 1");
            } else {
                print(find(1, root, value));
            }
        } else if (*type == 'R') {
            if (root == 0) {
                puts("FALSE 1");
            } else {
                print(remove(1, root, value));
            }
        }
    }
    return 0;
}
