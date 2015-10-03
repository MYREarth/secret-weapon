#if ( _WIN32 || __WIN32__ || _WIN64 || __WIN64__ )
#define INT64 "%I64d"
#else
#define INT64 "%lld"
#endif

#if ( _WIN32 || __WIN32__ || _WIN64 || __WIN64__ )
#define UNS64 "%I64u"
#else
#define UNS64 "%llu"
#endif
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <vector>
#include <cstring>
#include <string.h>
#include <set>
#include <map>
#include <bitset>
#include <queue>
#include <complex>

using namespace std;

#define pb push_back
#define mp make_pair
#define next _next
#define prev _prev
#define rank _rank
#define fs first
#define sc second

typedef long long ll;
typedef unsigned long long ull;
typedef complex <double> tc;
typedef pair <int, int> pii;
typedef vector <int> vi;

const int inf = int(1e9);
const double pi = acos(double(-1));
const double eps = 1e-9;
const int RMQ_SIZE = int(9e6);
const int N = 100100;

struct tr{
	int val;
	tr *ls, *rs;
};

struct point{
	int x, y;
};

int cur, ans, maxv;
point p[N];
int my[N], pos[N];
tr *ptr;
tr *q[1000];
int ql[1000], qr[1000];
tr *v1[N], *v2[N], *v3[N], *v4[N];
tr rmq[RMQ_SIZE];

bool operator < (const point &a, const point &b){
	return a.x < b.x;
}

tr *clone(tr *v){
	*ptr = *v;
	return ptr++;
}

tr *update(tr *v, int l, int r, int p, int val){
	v = clone(v);
	if(!v->ls){
		v->val = min(v->val, val);
		return v;
	}
	int m = (l + r) / 2;
	if(p <= m){
		v->ls = update(v->ls, l, m, p, val);
	}
	else{
		v->rs = update(v->rs, m + 1, r, p, val);
	}
	v->val = min(v->ls->val, v->rs->val);
	return v;
}

inline void get(tr *v, int l, int r){
	int ll = 0, rr = 1;
	q[0] = v;
	ql[0] = 0;
	qr[0] = maxv - 1;
	while(ll < rr){
		v = q[ll];
		int L = ql[ll];
		int R = qr[ll++];
		if(v->val + cur > ans){
			continue;
		}
		if(l <= L && R <= r){
			ans = v->val + cur;
			continue;
		}
		int M = (L + R) / 2;
		if(max(L, l) <= min(M, r) && v->ls->val + cur < ans){
			q[rr] = v->ls;
			ql[rr] = L;
			qr[rr++] = M;
		}
		if(max(M + 1, l) <= min(R, r) && v->rs->val + cur < ans){
			q[rr] = v->rs;
			ql[rr] = M + 1;
			qr[rr++] = R;
		}
	}
}

int main(){
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	int n, m;
	scanf("%d %d", &n, &m);
	int M;
	scanf("%d", &M);
	int A, B, C;
	scanf("%d %d %d", &A, &B, &C);
	int D, E, F;
	scanf("%d %d %d", &D, &E, &F);
	for(int i = 0; i < n; i++){
		int x, y;
		scanf("%d %d", &x, &y);
		p[i].x = x + y;
		p[i].y = x - y;
		my[i] = p[i].y;
	}
	sort(my, my + n);
	int k = unique(my, my + n) - my;
	maxv = 1;
	while(maxv < k){
		maxv *= 2;
	}
	ptr = &rmq[2 * maxv];
	for(int i = 1; i < 2 * maxv; i++){
		rmq[i].val = inf;
		if(i < maxv){
			rmq[i].ls = &rmq[i * 2];
			rmq[i].rs = &rmq[i * 2 + 1];
		}
	}
	tr *v = &rmq[1];
	sort(p, p + n);
	for(int i = 0; i < n; i++){
		pos[i] = lower_bound(my, my + k, p[i].y) - my;
		v = update(v, 0, maxv - 1, pos[i], -p[i].x + p[i].y);
		v1[i] = v;
	}
	v = &rmq[1];
	for(int i = 0; i < n; i++){
		v = update(v, 0, maxv - 1, pos[i], -p[i].x - p[i].y);
		v2[i] = v;
	}
	v = &rmq[1];
	for(int i = n - 1; i >= 0; i--){
		v = update(v, 0, maxv - 1, pos[i], p[i].x + p[i].y);
		v3[i] = v;
	}
	v = &rmq[1];
	for(int i = n - 1; i >= 0; i--){
		v = update(v, 0, maxv - 1, pos[i], p[i].x - p[i].y);
		v4[i] = v;
	}
	int x, y;
	scanf("%d %d", &x, &y);
	ll sum = 0;
	for(int i = 0; i < m; i++){
		ans = inf;
		int xx = x + y, yy = x - y;
		int posx = n, l = 0, r = n - 1;
		while(l <= r){
			int mid = (l + r) / 2;
			if(p[mid].x >= xx){
				posx = mid;
				r = mid - 1;
			}
			else{
				l = mid + 1;
			}
		}
		int posy = lower_bound(my, my + k, yy) - my;
		if(posx > 0){
			cur = xx - yy;
			if(posy < k){
				get(v1[posx - 1], posy, k - 1);
			}
			cur = xx + yy;
			if(posy > 0){
				get(v2[posx - 1], 0, posy - 1);
			}
		}
		if(posx < n){
			cur = -xx - yy;
			if(posy < k){
				get(v3[posx], posy, k - 1);
			}
			cur = -xx + yy;
			if(posy > 0){
				get(v4[posx], 0, posy - 1);
			}
		}
		ans /= 2;
		sum += ans;
		if(i + 1 < m){
			x = abs(ll(A) * x + ll(B) * ans + C) % (2 * M + 1) - M;
			y = abs(ll(D) * y + ll(E) * ans + F) % (2 * M + 1) - M;
		}
	}
	printf(INT64 "\n", sum);
	return 0;
}
