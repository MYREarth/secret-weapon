#include <cstdio>
#include <algorithm>
#include <set>
#include <vector>
#include <map>
#include <cmath>
#include <iostream>
#include <ctime>

using namespace std;

const int MAXN = 50000;

int vm (int cx, int cy, int ax, int ay, int bx, int by) {
	return (ax-cx)*(by-cy) - (bx-cx)*(ay-cy);
}

int x[MAXN], y[MAXN];
int v[MAXN], p[MAXN], R[MAXN], a[MAXN], f[MAXN];
int S[MAXN];
vector<int> backup[MAXN];
map<int, double> answers;

int triangle (int a, int b, int c) {
	return abs(vm(x[a],y[a], x[b],y[b], x[c],y[c]));
}

int dist (int a, int b) {
	return (x[a]-x[b])*(x[a]-x[b]) + (y[a]-y[b])*(y[a]-y[b]);
}

bool cmp_version (int i, int j) {
	return v[i] < v[j];
}

int CX, CY;

bool cmp_angle (int a, int b) {
	int x1 = x[a]-CX;
	int y1 = y[a]-CY;
	int x2 = x[b]-CX;
	int y2 = y[b]-CY;
	if (y1>=0 && y2<0)
		return true;
	if (y1<0 && y2>=0)
		return false;
	if (y1==0 && y2==0)
		return abs(x1) < abs(x2);
	int vp = x1*y2 - x2*y1;
	if (vp > 0) return true;
	if (vp < 0) return false;
	return x1*x1 + y1*y1 < x2*x2 + y2*y2;
}

bool otherside (int a, int b, int v1, int v2) {
	long long vc = vm(x[a],y[a], x[b],y[b], x[v2],y[v2]);
	long long vv = vm(x[a],y[a], x[b],y[b], x[v1],y[v1]);
	if (vc*vv > 0) return false;
	if (vc*vv < 0) return true;
	return (x[a]-x[v1])*(x[b]-x[v1]) + (y[a]-y[v1])*(y[b]-y[v1]) > 0;
}

typedef set<int> pointset;
typedef pair<int, vector<int> > change;

pointset polygon;
int square;
vector<change> change_stack;

pointset::iterator prev (pointset::iterator x) {
	if (x == polygon.begin())
		x = polygon.end();
	x--;
	return x;
}

pointset::iterator next (pointset::iterator x) {
	x++;
	if (x == polygon.end())
		x = polygon.begin();
	return x;
}

void remove (int ver) {
	pointset::iterator P = polygon.find(ver);
	if (P==polygon.end()) return;
	pointset::iterator L = prev(P);
	pointset::iterator R = next(P);
	square -= triangle(a[*L], a[*P], a[*R]);
	polygon.erase(P);
}

vector<int> add (int ver) {
	vector<int> buf;
	pointset::iterator R = polygon.upper_bound(ver);
	if (R==polygon.end()) R = polygon.begin();
	pointset::iterator L = prev(R);
	if (polygon.size()==2) {
		int S = triangle(a[*L],a[ver],a[*R]);
		if (S==0) {
			int LR = dist(a[*L],a[*R]);
			int LV = dist(a[*L],a[ver]);
			int RV = dist(a[*R],a[ver]);
			if (LV > LR && LV > RV) {
				buf.push_back(*R);
				polygon.erase(R);
				polygon.insert(ver);
			} else
			if (RV > LR && RV > LV) {
				buf.push_back(*L);
				polygon.erase(L);
				polygon.insert(ver);
			}
		}
		else {
			polygon.insert(ver);
			square += S;
		}
		return buf;
	}
	pointset::iterator RR = next(R);
	pointset::iterator LL = prev(L);
	int inside;
	if (!otherside(a[*L],a[*R],a[ver],a[*RR]))
		return buf;
	inside = *L;
	while (otherside(a[*RR],a[*R],a[ver],a[inside]) && R!=L) {
		inside = *R;
		buf.push_back(*R);
		R = RR;
		RR = next(R);
	}
	if (inside == *L) inside = *R;
	while (otherside(a[*LL],a[*L],a[ver],a[inside]) && L!=R) {
		inside = *L;
		buf.push_back(*L);
		L = LL;
		LL = prev(L);
	}
	square += triangle(a[*L],a[ver],a[*R]);
	for (int i=0; i<buf.size(); i++)
		remove (buf[i]);
	polygon.insert(ver);
	return buf;
}

void push (int ver) {
	change_stack.push_back(change (ver, add(ver)));
}

void pop() {
	change backup = change_stack[change_stack.size()-1];
	remove (backup.first);
	for (int i=0; i<backup.second.size(); i++)
		add (backup.second[i]);
	change_stack.pop_back();
}

int Smax = 0;
int ans = 0;

void process (int l, int r) {
	if (l==r) {
		if (answers.count(v[p[l]])==0 || square/8.0 > answers[v[p[l]]]) {
			answers[v[p[l]]] = square / 8.0;
		}
		return;
	}
	int m = (l+r)/2;
	for (int i=r-1; i>=m; i--)
		push(f[p[i]]);
	process (l,m);
	for (int i=m; i<r; i++)
		pop();
	for (int i=R[l]+1; i<=R[m+1]; i++)
		push(f[p[i]]);
	process (m+1,r);
	for (int i=R[m+1]; i>R[l]; i--)
		pop();
}

set<pair<int,int> > points;

int main() {
//	freopen ("input.txt", "r", stdin);
//	freopen ("output.txt", "w", stdout);
	int n,m;
	scanf ("%d%d", &n, &m);
	for (int i=0; i<n; i++) {
		scanf ("%d%d%d", x+i, y+i, v+i);
		x[i] *= 2;
		y[i] *= 2;
		p[i] = i;
		points.insert(pair<int,int>(x[i],y[i]));
	}
	sort (p, p+n, cmp_version);
	for (int i=0; i<n; i++) {
		int l=i, r=n;
		while (r-l>1) {
			int s = (r+l)/2;
			if (v[p[s]] > v[p[i]]+m) r=s;
			else l=s;
		}
		R[i] = l;
		S[i] = 0;
	}
	int u = 0;
	while (u<n-1) {
		if (R[u] > u+1) {
			for (int i=u; i<=R[R[u]]; i++)
				a[i-u] = p[i];
			CX = (x[p[R[u]]] + x[p[R[u]-1]]) / 2;
			CY = (y[p[R[u]]] + y[p[R[u]-1]]) / 2;
			while (points.find(pair<int,int>(CX,CY)) != points.end()) {
				CX = (x[p[R[u]]] + CX) / 2;
				CY = (y[p[R[u]]] + CY) / 2;
			}
			sort(a,a+(R[R[u]]-u+1), cmp_angle);
			for (int i=0; i<=R[R[u]]-u; i++)
				f[a[i]] = i;
			polygon.clear();
			square = 0;
			change_stack.clear();
			polygon.insert(f[p[R[u]]]);
			polygon.insert(f[p[R[u]-1]]);
			process (u, R[u]-1);
			u = R[u];
		}
		else u++;
	}
	for (int i=0; i<n; i++) {
		if (answers.count(v[i]) > 0)
			printf("%.7lf\n", answers[v[i]]);
		else
			printf("%.7lf\n", 0.0);
	}
	return 0;
}
