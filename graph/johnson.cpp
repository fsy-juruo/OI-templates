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
const int maxN = 3e3 + 10, maxM = 6e3 + 10, inf = 1e9;
// initial
int n, m;
struct Edge {
	int from, to, nxt, val;
} edge[maxM << 1];
int head[maxN], sz = 0;
void add_edge(int u, int v, int w) {
	edge[++sz].from = u; edge[sz].to = v; edge[sz].val = w; edge[sz].nxt = head[u]; head[u] = sz;
}
struct node {
	int pos, val;
	bool operator < (const node &B) const {
		return B.val < val;
	}
};
LL h[maxN];
int cnt[maxN], vis[maxN];
bool spfa(int s) {
	std::queue<int> q; q.push(s);
	cnt[s] = 1; h[s] = 0; vis[s] = 1;
	while(!q.empty()) {
		int u = q.front(); q.pop();
		vis[u] = 0;
		for(int i = head[u]; i; i = edge[i].nxt) {
			if(h[edge[i].to] > h[u] + edge[i].val) {
				h[edge[i].to] = h[u] + edge[i].val;
				if(!vis[edge[i].to]) {
					q.push(edge[i].to);
					vis[edge[i].to] = 1;
					cnt[edge[i].to] = cnt[u] + 1;
					if(cnt[edge[i].to] > n) return false;
				}
			}
		}
	}
	return true;
}
LL dis[maxN];
void dijkstra(int s) {
	_rep(i, 1, n) dis[i] = inf, vis[i] = 0;
	dis[s] = 0; 
	std::priority_queue<node> q;
	q.push((node){s, 0});
	while(!q.empty()) {
		node u = q.top(); q.pop();
		if(vis[u.pos]) continue;
		vis[u.pos] = 1;
		for(int i = head[u.pos]; i; i = edge[i].nxt) {
			if(dis[edge[i].to] > dis[u.pos] + edge[i].val) {
				dis[edge[i].to] = dis[u.pos] + edge[i].val;
				if(!vis[edge[i].to]) {
					q.push((node){edge[i].to, dis[edge[i].to]});
				}
			}
		}
	}
}
int main() {
	read(n, m);
	_rep(i, 1, m) {
		int u, v, w; read(u, v, w);
		add_edge(u, v, w);
	}
	_rep(i, 1, n) add_edge(0, i, 0);
	_rep(i, 1, n) h[i] = inf;
	if(!spfa(0)) return puts("-1"), 0;
	_rep(i, 1, m) {edge[i].val += h[edge[i].from] - h[edge[i].to];}
	_rep(i, 1, n) {
		dijkstra(i);
		LL ans = 0;
		_rep(j, 1, n) ans = ans + 1ll * j * (dis[j] - (dis[j] == inf ? 0 : h[i] - h[j]));
	//	_rep(j, 1, n) writesp(dis[j], ' ');
		writesp(ans, '\n');
	}
	return 0;
}
