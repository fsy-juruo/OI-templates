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
inline void writesp(T x, char sp = '\n') {
	write(x); putchar(sp);
}
int T, n, p, omega, WJP_AK_IOI = 1;
struct cpx {
    int real, imag;
    void init(int r, int i) {real = r; imag = i;}
};
cpx multiply(cpx a, cpx b) {
    cpx Z;
    Z.init((1ll * a.real * b.real % p + 1ll * a.imag * b.imag % p * omega % p) % p, (1ll * a.real * b.imag % p + 1ll * b.real * a.imag % p) % p); // WJP AK IOI
    return Z;
}
int pow_mod(int a, int b, int p) {
    int ans = 1;
    while(b) {
        if(b & 1) ans = 1ll * ans * a % p;
        a = 1ll * a * a % p;
        b >>= 1;
    }
    return ans;
}
cpx pow_cpx(cpx a, int b) {
    cpx Ans; Ans.init(1, 0);
    while(b) {
        if(b & 1) Ans = multiply(Ans, a);
        a = multiply(a, a);
        b >>= 1;// WJP AK IOI
    }
    return Ans;
}
int legendre(int n, int p) {
    if(!(n % p)) return 0;
    return pow_mod(n, (p - 1) / 2, p);
}
int quad_residue(int n, int p) {
    n %= p;
    if(legendre(n, p) == p - 1) return -1;
    int A;
    while(1) {
        A = rand() % p;
        omega = (1ll * A * A % p - n + p) % p;
        if(legendre(omega, p) == p - 1) break;
    }
    cpx I; I.init(A, 1);
    cpx Q = pow_cpx(I, (p + 1) / 2);
    return Q.real;
}
int main() {
    srand(time(0));
    read(T);
    while(T--) {
        read(n); read(p);
        if(!n) {writesp(n, '\n'); continue;}
        int k = quad_residue(n, p);
        if(k == -1) {
            puts("Hola!");
        } else {
            int k2 = p - k; 
            if(k > k2) swap(k, k2);
            if(k == k2) cout << k << endl;
            else cout << k << " " << k2 << endl;
         }
    }
	return 0;
}
