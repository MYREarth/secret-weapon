#include<deque>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 20;
int n, speed[N];

deque<char> supply[N], discard[N];

int main() {
    freopen("jungle.in", "r", stdin);
    freopen("jungle.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", speed + i);
    }
    char buf[55];
    for (int i = 0; i < n; ++i) {
        scanf("%s", buf);
        int l = strlen(buf);
        for (int j = 0; j < l; ++j) {
            supply[i].push_front(buf[j]);
        }
    }
    int move = 0, cur = 0;
    while (move < 1000000) {
        if (supply[cur].size()) {
            ++move;
            discard[cur].push_front(supply[cur].front());
            supply[cur].pop_front();
            int s = 0, match = -1;
            for (int i = 0; i < n; ++i) {
                s += supply[i].size();
                if (i != cur) {
                    if (discard[i].size() > 0 && discard[i].front() == discard[cur].front()) {
                        match = i;
                    }
                }
            }
            if (match == -1 && s == 0) {
                printf("Draw after %d moves.\n", move);
                return 0;
            }
            if (match != -1) {
                int winner, loser;
                if (speed[cur] < speed[match]) {
                    winner = cur, loser = match;
                } else {
                    winner = match, loser = cur;
                }
                while (discard[loser].size()) {
                    supply[loser].push_back(discard[loser].front());
                    discard[loser].pop_front();
                }
                while (discard[winner].size()) {
                    supply[loser].push_back(discard[winner].front());
                    discard[winner].pop_front();
                }
                if (supply[winner].size() == 0 && discard[winner].size() == 0) {
                    printf("Player %d wins after %d moves.\n", winner + 1, move);
                    return 0;
                }
            }
        }
        ++cur;
        if (cur == n) {
            cur = 0;
        }
    }
    printf("Abandoned after 1000000 moves.\n");
    return 0;
}
