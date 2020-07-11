#include <bits/stdc++.h>
#pragma GCC optimize(2)
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
const int maxN = 1e4 + 10, maxM = 5e5 + 10, INF = 2147483647ll, inf = 1e9;
int n, m, s;
struct Edge {
	int from, to, nxt, val;
} edge[maxM << 1];
int head[maxN], sz = 0;
void add_edge(int u, int v, int w) {
	edge[++sz].from = u; edge[sz].to = v; edge[sz].val = w; edge[sz].nxt = head[u]; head[u] = sz;
}
int M[maxN], d[maxN], p[maxN];
std::deque<int> q;
void desopo_pape(int s) {
	d[s] = 0; q.push_back(s); p[s] = -1;
	while(!q.empty()) {
		int u = q.front(); q.pop_front(); M[u] = 0;
		for(int i = head[u]; i; i = edge[i].nxt) {
			int v = edge[i].to;
			if(d[v] > d[u] + edge[i].val) {
				d[v] = d[u] + edge[i].val;
				p[v] = u; 
				if(M[v] == 2) {
					M[v] = 1; q.push_back(v);
				} else if(!M[v]) {
					M[v] = 1; q.push_back(v);
				}
			}
		}
	} 
}
int main() {
	read(n, m, s);
	_rep(i, 1, m) {
		int u, v, w; read(u, v, w);
		add_edge(u, v, w);
	}
	_rep(i, 1, n) d[i] = inf, M[i] = 2;
	desopo_pape(s);
	_rep(i, 1, n) writesp(d[i] == inf ? INF : d[i], ' ');
	return 0;
}
