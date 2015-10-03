#include<map>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 1005;

int t, r, k, l, h[N];

vector<pair<int, int> > safe2;

map<pair<int, int>, pair<int, pair<int, int> > > mem;

bool issafe2(int d) {
    int p = upper_bound(safe2.begin(), safe2.end(), make_pair(d, -1)) - safe2.begin();
    --p;
    return safe2[p].first <= d && d <= safe2[p].second;
}

int presafe(int d) {
    int p = upper_bound(safe2.begin(), safe2.end(), make_pair(d, -1)) - safe2.begin();
    --p;
    return safe2[p].second / 2;
}

int nxtsafe(int d) {
    int p = lower_bound(safe2.begin(), safe2.end(), make_pair(d, -1)) - safe2.begin();
    return safe2[p].first / 2;
}

int go(int &cara, int &carb) {
    int dt = min(l - cara, carb - 0);
    cara += dt, carb -= dt;
    return dt;
}

int cal(int &cara, int &carb) {
    if (cara >= carb - 2 || issafe2(cara + carb)) {
        return go(cara, carb);
    }
    int fore = presafe(cara + carb), next = nxtsafe(cara + carb);
    if (fore + next > cara + carb) {
        int dt = carb - fore;
        cara = carb = fore;
        return dt + go(cara, carb);
    } else {
        int dt = next - cara;
        cara = carb = next;
        return dt + go(cara, carb);
    }
}

int main() {
    scanf("%d%d", &t, &r);
    scanf("%d", &k);
    l = 0;
    for (int i = 0; i < k; ++i) {
        scanf("%d", h + i);
        l += h[i];
    }
    int x = 0;
    for (int i = 0; i < k; ++i) {
        if (i % 2 == 0) {
            safe2.push_back(make_pair((x + 1) * 2, (x + h[i] - 1) * 2));
        }
        x += h[i];
    }
    safe2[0].first -= 10;
    safe2[safe2.size() - 1].second += 10;
    int cara = -1, carb = l + 1,
        cnta = 0, cntb = 0, cur = 0;
    bool cycled = false;
    while (true) {
        cur += cal(cara, carb);
        if (cur > t) {
            break;
        }
        if (cara == l) {
            ++cnta;
            cara = -1;
        }
        if (carb == 0) {
            ++cntb;
            carb = l + 1;
        }
        if (!cycled && mem.count(make_pair(cara, carb))) {
            int dt = cur - mem[make_pair(cara, carb)].first,
                da = cnta - mem[make_pair(cara, carb)].second.first,
                db = cntb - mem[make_pair(cara, carb)].second.second;
            int rnd = (t - cur) / dt;
            cur += dt * rnd, cnta += da * rnd, cntb += db * rnd;
            cycled = true;
        }
        if (!cycled) {
            mem[make_pair(cara, carb)] = make_pair(cur, make_pair(cnta, cntb));
        }
    }
    printf("%d %d\n", cnta, cntb);
    return 0;
}
