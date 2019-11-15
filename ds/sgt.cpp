#include <bits/stdc++.h>
#define _rep(i, x, y) for(int i = x; i <= y; i++)
#define _per(i, x, y) for(int i = x; i >= y; i--)
#define LL long long
using namespace std;
template <typename T>
inline void read(T &x) {
    x = 0; T f = (T) 1;
    char c = getchar();
    for (; !isdigit(c); c = getchar())
        if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - 48;
    x *= f;
}
template <typename T>
inline void write(T x) {
	if(x < 0) {putchar('-'); x = -x;}
	if(x > 9) write(x / 10);
	putchar(x % 10 + '0');
}
template <typename T>
inline void writesp(T x, char sp = '\n') {
	write(x); putchar(sp);
}
const int maxN = 3e5;
int n, m;
LL num[maxN];
struct node {
	LL val, tag;
} tree[maxN];
void push_up(int o) {
	tree[o].val = tree[o << 1].val + tree[o << 1 | 1].val;
}
void build(int o, int l, int r) {
	if(l == r) {
		tree[o].val = num[l];
		return;
	}
	int mid = (l + r) >> 1;
	build(o << 1, l, mid);
	build(o << 1 | 1, mid + 1, r);
	push_up(o);
}
void push_down(int o, int l, int r) {
	if(tree[o].tag) {
		int mid = (l + r) >> 1;
		tree[o << 1].val += 1ll * tree[o].tag * (mid - l + 1);
		tree[o << 1].tag += 1ll * tree[o].tag;
		tree[o << 1 | 1].val += 1ll * tree[o].tag * (r - mid);
		tree[o << 1 | 1].tag += 1ll * tree[o].tag;
		tree[o].tag = 0;
	}
}
void modify(int o, int l, int r, int lx, int rx, int delta) {
	if(rx < l || lx > r) return;
	if(lx <= l && r <= rx) {
		tree[o].val += 1ll * (r - l + 1) * delta;
		tree[o].tag += 1ll * delta;
		return;
	}
	push_down(o, l, r);
	int mid = (l + r) >> 1;
	modify(o << 1, l, mid, lx, rx, delta);
	modify(o << 1 | 1, mid + 1, r, lx, rx, delta);
	push_up(o);
}
LL query(int o, int l, int r, int lx, int rx) {
	if(rx < l || lx > r) return 0;
	if(lx <= l && r <= rx) {
		return tree[o].val;
	}
	push_down(o, l, r);
	int mid = (l + r) >> 1;
	return (query(o << 1, l, mid, lx, rx) + query(o << 1 | 1, mid + 1, r, lx, rx));
}
int main() {
	read(n); read(m);
	_rep(i, 1, n) {
		read(num[i]);
	}
	build(1, 1, n);
	_rep(i, 1, m) {
		int opt; read(opt);
		if(opt == 1) {
			int l, r, delta;
			read(l); read(r); read(delta);
			modify(1, 1, n, l, r, delta);
		} else {
			int l, r;
			read(l); read(r);
			writesp(query(1, 1, n, l, r));
		}
	}
//	root = new_node();
	return 0;
}
