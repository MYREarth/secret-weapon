#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;

#define null (node*)0

const int MXPT = 240000000;
int pt = 0;
char buf[MXPT + 5000000];

int MOD = (1 << 30) - 1;
int qwe = 424243, asd = 42424243;

inline int myrand()
{
    int t = qwe * 424243 + asd * 42424243;
    qwe = asd, asd = t;
    return t & MOD;
}

struct node{
	int x, size;
	node * l, * r;
	inline void * operator new(size_t size){
		pt += size;
		return buf + pt - size;
	}
	inline node(int _x = 0, node * _l = null, node * _r = null){
		x = _x, l = _l, r = _r;
		size = 1;
		if (l != null)
			size += l -> size;
		if (r != null)
			size += r -> size;
	};
};

node * root = null;
int T = 1;

node * merge(node * r1, node * r2){
	if (r1 == null && r2 == null)
		return null;
	if (r1 == null)
		return new node(r2 -> x, r2 -> l, r2 -> r);
	if (r2 == null)
		return new node(r1 -> x, r1 -> l, r1 -> r);
	if (myrand() % (r1 -> size + r2 -> size) < r1 -> size)
		return new node(r1 -> x, r1 -> l, merge(r1 -> r, r2));
	else
		return new node(r2 -> x, merge(r1, r2 -> l), r2 -> r);
}

pair<node *, node *> split(node * root, int left){
	if (root == null)
		return make_pair(null, null);
	if (root -> l == null && left == 0){
		return make_pair(null, new node(root -> x, root -> l, root -> r));
	}
	pair<node *, node *> d;
	if (root -> l != null && root -> l -> size >= left){
		d = split(root -> l, left);
		return make_pair(d.first, new node(root -> x, d.second, root -> r));
	}
	else{
		left -= 1;
		if (root -> l != null)
			left -= root -> l -> size;
		d = split(root -> r, left);
		return make_pair(new node(root -> x, root -> l, d.first), d.second);
	}
}

node * do_tree(int * v, int l, int r){
	if (r - l < 1) return null;
	if (r - l == 1) return new node(v[l], null, null);
	return new node(v[(l + r) / 2], do_tree(v, l, (l + r) / 2), do_tree(v, (l + r) / 2 + 1, r));
}

void print(node * root, int * v, int & mx){
	if (root == null)
		return;
	print(root -> l, v, mx);
	v[mx++]=root -> x;
	print(root -> r, v, mx);
}

void condom(){
	if (pt < MXPT)
		return;
	int v[300000];
	int n = 0;
	print(root, v, n);
	pt = 0;
	root = do_tree(v, 0, n);
}

node * create(int n){
	int * v = new int[n];
	for (int i = 0; i < n; ++i)
		v[i] = T++;
	node * ans = do_tree(v, 0, n);
	condom();
	delete v;
	return ans;
}

void set(int l, int r){
	if (r<l)
		swap(l, r);
	pair<node *, node *> d, d1;
	d = split(root, l - 1);
	d1 = split(d.second, r - l + 1);
	node * tmp = create(d1.first -> size);
	d.second = merge(tmp, d1.second);
	root = merge(d.first, d.second);
	condom();
}

node * pow(node * base, int p){
	if (p==1)
		return new node(base -> x, base -> l, base -> r);
	if (p%2 == 0){
		node * t = pow(base, p / 2);
		node * t2 = merge(t, t);
		return t2;
	}
	else{
		node * t = pow(base, p / 2);
		node * t2 = merge(t, base);
		node * t21 = merge(t2, t);
		return t21;
	}
}

void forward(int a, int b, int l){
//	for (int i = 0; i < l; ++i)
//		A[b++] = A[a++];
	if (a == b || l == 0) return;
	pair<node *, node *> d, d1, d2, d3;
	if (b - a >= l || b < a){
		d = split(root, a - 1);
		d1 = split(root, b - 1);
		d2 = split(d1.second, l);
		d3 = split(d.second, l);
//	    d1.first, d3.first, d2.second;
		node * tmp = merge(d1.first, d3.first);
		root = merge(tmp, d2.second);
	}
	else{
		d = split(root, a - 1);
		d1 = split(d.second, b - a);
		d2 = split(d.second, l + b - a);
		d3 = split(d.second, l % (b - a));
		node * tmp, * tmp2, * tmp3;
//		d.first, pow(d1.first, l / (a - b) + 1), d3.first, d2.second;
		tmp3 = pow(d1.first, l / (b - a) + 1);
		tmp = merge(d.first, tmp3);
		tmp2 = merge(d3.first, d2.second);
		root = merge(tmp, tmp2);
	}
	condom();
}

void backward(int a, int b, int l){
//	for (int i = 0; i < l; ++i)
//		A[a--] = A[b--];
	if (a == b || l == 0) return;
	pair<node *, node *> d, d1, d2, d3;
	if (a - b >= l || a > b){
		d = split(root, b - l);
		d1 = split(root, a - l);
		d2 = split(d1.second, l);
		d3 = split(d.second, l);
//	    d1.first, d3.first, d2.second;
		node * tmp = merge(d1.first, d3.first);
		root = merge(tmp, d2.second);
	}
	else{
		d = split(root, a);
		d1 = split(d.second, b - a);
		d2 = split(root, a - l);
		d3 = split(d1.first, (b - a) - l % (b - a));
		node * tmp, * tmp2, * tmp3;
//		d2.first, d3.second, pow(d1.first, l / (b - a) + 1), d1.second;
		tmp = merge(d2.first, d3.second);
		tmp3 = pow(d1.first, l / (b - a) + 1);
		tmp2 = merge(tmp3, d1.second);
		root = merge(tmp, tmp2);
	}
	condom();
}

void print(node * root){
	int ans[300000];
	int mx = 0;
	print(root, ans, mx);
	for (int i = 0; i < mx; ++i)
		printf("%d%c", ans[i], " \n"[i+1 == mx]);
}

int main(){
	int n, t;
	scanf("%d %d\n", &n, &t);
	char c;
	int a, b, l;
	root = create(n);
	for (int i = 0; i < t; ++i){
		scanf("%c ", &c);
		if (c == 'f'){
			scanf("%d %d %d\n", &a, &b, &l);
			forward(a, b, l);
		}
		if (c == 'b'){
			scanf("%d %d %d\n", &a, &b, &l);
			backward(a, b, l);
		}
		if (c == 'x'){
			scanf("%d %d\n", &a, &b);
			set(a, b);
		}
	}
	print(root);
	cerr << clock() / CLOCKS_PER_SEC << endl;
	return 0;
}