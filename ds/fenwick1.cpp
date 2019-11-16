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
const int maxN = 5e5 + 5;
int m;
struct Fenwick {
	LL num[maxN], n;
	int lowbit(int x) {
		return x & (-x);
	}
	void add(int x, LL delta) {
		for(; x <= n; x += lowbit(x)) {
			num[x] += delta;
		}
	}
	LL query(int x) {
		LL ans = 0;
		for(; x; x -= lowbit(x)) ans += num[x];
		return ans;
	}
	LL query(int l, int r) {
		return query(r) - query(l - 1);
	}
} BIT;
int main() {
	read(BIT.n); read(m);
	_rep(i, 1, BIT.n) {
		LL x; read(x);
		BIT.add(i, x);
	}
	_rep(i, 1, m) {
		int opt, x; LL k;
		read(opt); read(x); read(k);
		if(opt == 1) {
			BIT.add(x, k);
		} else {
			writesp(BIT.query(x, k));
		}
	}
	return 0;
}

