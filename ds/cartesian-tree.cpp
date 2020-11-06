#include <bits/stdc++.h>
#define _rep(i, x, y) for(int i = x; i <= y; i++)
#define _per(i, x, y) for(int i = x; i >= y; i--)
#define LL long long
#define ULL unsigned long long
#define LD long double
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
inline void writesp(T x, char sp = ' ') {
	write(x); putchar(sp);
}
// cartesian tree
const int maxN = 1e7 + 10;
int n;
int val[maxN], ls[maxN], rs[maxN], stk[maxN], top = 0;
void cartesian_build() {
	_rep(i, 1, n) {
		int k = top;
		while(k && val[stk[k]] > val[i]) k--;
		if(k) rs[stk[k]] = i;
		if(k != top) ls[i] = stk[k + 1];
		stk[++k] = i; top = k;
	}
}

int main() {
	read(n);
	_rep(i, 1, n) read(val[i]);
	cartesian_build();
	LL lans = 0, rans = 0;
	_rep(i, 1, n) {
		lans = lans ^ (1ll * (ls[i] + 1) * i);
		rans = rans ^ (1ll * (rs[i] + 1) * i);
	}
	writesp(lans); writesp(rans, '\n');
	return 0;
}

