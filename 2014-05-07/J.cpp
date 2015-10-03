#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <string>

const int N = 8;
const int M = 18;

const double EPS = 1e-8;

int signum(double x) {
    return x < -EPS ? -1 : x > EPS;
}

int n, m, cost[N], length[M], degree[N], graph[N][N];
std::string rooms[N];

int find_room(const std::string &room) {
    return std::find(rooms, rooms + n, room) - rooms;
}

double expected[1 << M][N], coefficient[N][N + 1];

int main() {
    std::cin >> n >> m;
    for (int i = 0; i < n; ++ i) {
        std::cin >> rooms[i] >> cost[i];
    }
    memset(degree, 0, sizeof(degree));
    memset(graph, -1, sizeof(graph));
    for (int i = 0; i < m; ++ i) {
        std::string u, v;
        std::cin >> u >> v >> length[i];
        int a = find_room(u);
        int b = find_room(v);
        degree[a] ++;
        degree[b] ++;
        graph[a][b] = graph[b][a] = i;
//printf("%d %d\n", a, b);
    }
    for (int i = 0; i < n; ++ i) {
        expected[(1 << m) - 1][i] = cost[i];
    }
    for (int mask = (1 << m) - 2; mask >= 0; -- mask) {
        memset(coefficient, 0, sizeof(coefficient));
        for (int i = 0; i < n; ++ i) {
            coefficient[i][i] -= 1.;
            coefficient[i][n] += cost[i];
            for (int j = 0; j < n; ++ j) {
                if (~graph[i][j]) {
                    coefficient[i][n] += (double)length[graph[i][j]] / degree[i];
                    if (mask >> graph[i][j] & 1) {
                        coefficient[i][j] += 1. / degree[i];
                    } else {
                        int newMask = mask | 1 << graph[i][j];
                        if (newMask == (1 << m) - 1) {
                            coefficient[i][n] += ((double)expected[newMask][j] - (degree[j] > 1 ? cost[j] : 0)) / degree[i];
                        } else {
                            coefficient[i][n] += (double)expected[newMask][j] / degree[i];
                        }
                    }
                }
            }
        }
        for (int j = 0; j < n; ++ j) {
            int pivot = j;
            for (int k = j; k < n; ++ k) {
                if (std::abs(coefficient[k][j]) > std::abs(coefficient[pivot][j])) {
                    pivot = k;
                }
            }
            for (int k = 0; k <= n; ++ k) {
                std::swap(coefficient[j][k], coefficient[pivot][k]);
            }
            for (int i = 0; i < n; ++ i) {
                if (i != j) {
                    double scale = coefficient[i][j] / coefficient[j][j];
                    for (int k = 0; k <= n; ++ k) {
                        coefficient[i][k] -= scale * coefficient[j][k];
                    }
                }
            }
        }
        for (int i = 0; i < n; ++ i) {
            expected[mask][i] = -coefficient[i][n] / coefficient[i][i];
        }
    }
    double best = *std::min_element(expected[0], expected[0] + n);
    std::vector <std::string> result;
    for (int i = 0; i < n; ++ i) {
        if (signum(expected[0][i] - best) == 0) {
            result.push_back(rooms[i]);
        }
    }
    std::sort(result.begin(), result.end());
    for (int i = 0; i < (int)result.size(); ++ i) {
        printf("%s%c", result[i].c_str(), " \n"[i == (int)result.size() - 1]);
    }
    printf("%.10f\n", best);
    return 0;
}
