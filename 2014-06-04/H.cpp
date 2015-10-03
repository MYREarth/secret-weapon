#include <cstdio>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <algorithm>

int q;
char buffer[11];

const int N = 400000 + 1;

int random(int a, int b) {
    return rand() % (a + b) < a;
}

Node* merge(Node *a, Node *b) {
    if (a == null) {
        return b;
    }
    if (b == null) {
        return a;
    }
    if (random(a->size, b->size)) {
        Node* new_node = new Node(*a);
        new_node->right = merge(a->right, b);
        return new_node->update();
    } else {
        Node* new_node = new Node(*b);
        new_node->left = merge(a, b->left);
        return new_node->update();
    }
}

struct Result {
    Result(int remove, Node* append) : remove(remove), append(append) {}

    int   remove;
    Node* append;
};

Result merge(const Result &a, const Result &b) {
    if (remove >= a.append->size) {
        return Result(a.remove + remove - a.append->size, b.append);
    } else {
        return Result(a.remove, merge(a.append->split(a.append->size - b.remove), b.append));
    }
}

int    node_count, key[N], weight[N], children[N][2];
Result self[N], sum[N];

void update(int &x) {
    sum[x] = merge(sum[children[x][0]], merge(self[x], sum[children[x][1]]));
}

void rotate(int &x, int t) {
    int y = children[x][t];
    children[x][t] = y;
    children[y][1 ^ t] = x;
    update(x);
    update(y);
    x = y;
}

void insert(int &x, int k, const Result &result) {
    if (x) {
        int t = key[x] < k;
        insert(children[x][t], k, new_tree);
        if (weight[children[x][t]] < weight[x]) {
            rotate(x, t);
        }
    } else {
        key[node_count] = k;
        self[node_count] = result;
        weight[node_count] = rand();
    }
    update(x);
}

void erase(int &x, int k) {
    if (x) {
        if (key[x] == k) {
            if (children[x][0] || children[x][1]) {
                rotate(x, weight[children[x][0]] > weight[children[x][1]]);
            } else {
                x = 0;
                return;
            }
        } else {
            erase(children[x][key[x] < k], k);
        }
        update(x);
    }
}

Result query(int &x, int k) {
    if (x == 0) {
        return sum[x];
    }
    if (key[x] > k) {
        return query(children[x][0], k);
    }
    return merge(sum[children[x][0]], merge(self[x], query(children[x][1], k)));
}

int main() {
    null = new Node(-1);
    null->left = null->right = null;

    node_count = 0;
    weight[0] = INT_MAX;
    sum[0] = Result(0, null);
    memset(children, 0, sizeof(children));

    scanf("%d", &q);
    int front = 0;
    int back = 0;
    while (q --) {
        int index;
        scanf("%d%s", &index, buffer);
        if (*buffer == '?') {
            Result frontr = query(front, index);
            Result backr = query(front, index);
        } else {
            if (*buffer == '-') {
                erase(front, index);
                erase(back, index);
            } else {
                int element;
                scanf("%d", &element);
                insert(buffer[buffer[1] == 'u' ? 5 : 4] == 'b' ? front : back, index, buffer[1] == 'u' ? Result(0, new Node(element)) : Result(1, null));
            }
            puts("0 0");
            fflush(stdout);
        }
    }
    return 0;
}
