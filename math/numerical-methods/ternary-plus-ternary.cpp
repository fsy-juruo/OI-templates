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

const double eps = 1e-5;
double xa, ya, xb, yb, xc, yc, xd, yd, p, q, r;
double dist(double ax, double ay, double bx, double by) {return sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay));}
double func(double px, double py, double qx, double qy) {return dist(px, py, qx, qy) / r + dist(qx, qy, xd, yd) / q;}
double in_ternary(double px, double py) { // enumerate point Q
	double lx = xc, rx = xd, ly = yc, ry = yd;
	while(dist(lx, ly, rx, ry) > eps) {
//		std::cout << lx << " " << ly << " "<< rx << " " << ry << " " << dist(lx, ly, rx, ry) << std::endl;
		double tmpx = (rx - lx) / 3.0, tmpy = (ry - ly) / 3.0;
		double tlx = lx + tmpx, tly = ly + tmpy, trx = rx - tmpx, t_ry = ry - tmpy;
		if(func(px, py, tlx, tly) < func(px, py, trx, t_ry)) {
			rx = trx; ry = t_ry;
		} else {
			lx = tlx; ly = tly;
		}
	}
	return func(px, py, lx, ly);
}
double out_ternary() { // enumerate point P
	double lx = xa, ly = ya, rx = xb, ry = yb;
	while(dist(lx, ly, rx, ry) > eps) {
//		std::cout << lx << " " << ly << " "<< rx << " " << ry << " " << dist(lx, ly, rx, ry) << std::endl;
		double tmpx = (rx - lx) / 3.0, tmpy = (ry - ly) / 3.0;
		double tlx = lx + tmpx, tly = ly + tmpy, trx = rx - tmpx, t_ry = ry - tmpy;
		if(in_ternary(tlx, tly) + dist(xa, ya, tlx, tly) / p < in_ternary(trx, t_ry) + dist(xa, ya, trx, t_ry) / p) {
			rx = trx; ry = t_ry;
		} else {
			lx = tlx; ly = tly;
		}
	}
	return in_ternary(lx, ly) + dist(xa, ya, lx, ly) / p;
}
int main() {
	scanf("%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf", &xa, &ya, &xb, &yb, &xc, &yc, &xd, &yd, &p, &q, &r);
	printf("%.2lf\n", out_ternary());
	return 0;
}

