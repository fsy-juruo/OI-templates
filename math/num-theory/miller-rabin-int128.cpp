#include <bits/stdc++.h>
#define LL long long
#define ULL unsigned long long
#define LD long double
#define reg register
#define _rep(i, x, y) for(int i = x; i <= y; i++)
#define _per(i, x, y) for(int i = x; i >= y; i--)
template <typename T>
inline void read(T &x) {
	x = 0; T f = (T) 1;
	char c = getchar();
	for(; !isdigit(c); c = getchar()) {if(c == '-') f = -f;}
	for(; isdigit(c); c = getchar()) x = x * 10 + c - 48;
	x *= f;
}
template <typename T, typename... Args>
inline void read(T& x, Args&... args) {
    read(x); read(args...);
}
template <typename T>
inline void write(T x) {
	if(x < 0) {x = -x; putchar('-');}
	if(x > 9) write(x / 10);
	putchar(x % 10 + '0');
}
template <typename T>
inline void writesp(T x, char sp = ' ') {write(x); putchar(sp);}
int primes[13] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
LL mul_mod(LL a, LL b, LL p) {
	return (__int128) a * b % p;
}
LL pow_mod(LL a, LL b, LL p) {
	LL sum = 1;
	while(b) {
		if(b & 1) sum = mul_mod(sum, a, p);
		a = mul_mod(a, a, p);
		b >>= 1;
	}
	return sum;
}
bool miller_rabin(LL x, int c = 12) {
	if(x < 2) return false;
	LL rem = x - 1; int cnt = 0;
	while(!(rem & 1)) rem >>= 1, cnt++;
	_rep(i, 0, c - 1) {
		if(x == primes[i]) return true;
		if(!(x % primes[i])) return false;
		LL q = pow_mod(primes[i], rem, x), p = q;
        _rep(i, 1, cnt) {
            q = mul_mod(q, q, x);
            if(q == 1 && p != 1 && p != x - 1) return false;
            p = q;
        }
        if(q != 1) return false;
	}
    return true;
}
int main() {
    LL n;
    while(scanf("%lld", &n) != EOF) {
        puts(miller_rabin(n) ? "Y" : "N");
    }
	return 0;
}
