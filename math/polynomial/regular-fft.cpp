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
const int maxN = 3e6 + 10;
const double PI = acos(-1);
int n, m, r[maxN], LIM, LG; // r : butterfly conversion
struct Complex {
	double real, imag;
	Complex() {};
	Complex(double R, double I) : real(R), imag(I) {};
} a[maxN], b[maxN];
Complex operator + (Complex a, Complex b) {return Complex(a.real + b.real, a.imag + b.imag);}
Complex operator - (Complex a, Complex b) {return Complex(a.real - b.real, a.imag - b.imag);}
Complex operator * (Complex a, Complex b) {return Complex(a.real * b.real - a.imag * b.imag, a.real * b.imag + a.imag * b.real);}
void fft(Complex *Poly, int len, int rev) { // rev = 1: DFT, rev = -1 : IDFT
	_rep(i, 0, len - 1) if(i < r[i]) std::swap(Poly[i], Poly[r[i]]);
	for(int l = 2; l <= len; l <<= 1) {
		Complex omega(cos(2.0 * PI / l), rev * sin(2.0 * PI / l));
		for(int i = 0; i < len; i += l) {
			Complex omega_0(1, 0);
			for(int j = i; j < i + (l >> 1); j++) {
				Complex g = Poly[j], h = omega_0 * Poly[j + l / 2]; // wjp ak ioi
				Poly[j] = g + h; Poly[j + l / 2] = g - h;
				omega_0 = omega_0 * omega;
			}
		}
	} 
	if(rev == -1) _rep(i, 0, len - 1) Poly[i].real = (Poly[i].real / len + 0.5);
}
int main() {
	read(n, m); LIM = 1; LG = 0;
	_rep(i, 0, n) {int x; read(x); a[i].real = x;}
	_rep(i, 0, m) {int x; read(x); b[i].real = x;}
	while(LIM <= n + m) {LIM <<= 1; LG++;}
	r[0] = 0; _rep(i, 1, LIM - 1) r[i] = (r[i >> 1] >> 1) | ((i & 1) << (LG - 1));
	fft(a, LIM, 1); fft(b, LIM, 1);
	_rep(i, 0, LIM) a[i] = a[i] * b[i];
	fft(a, LIM, -1);
	_rep(i, 0, m + n) writesp((int)a[i].real, ' ');
	puts("");
	return 0;
}

