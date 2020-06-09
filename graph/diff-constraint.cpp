#include <bits/stdc++.h>
#define LL long long
#define ULL unsigned long long
#define LD long double
#define _rep(i, x, y) for(int i = x; i <= y; i++)
#define _per(i, x, y) for(int i = x; i >= y; i--)
using namespace std;
template <typename T>
inline void read(T &x) {
	x = 0; T f = (T) 1;
	char c = getchar();
	for(; !isdigit(c); c = getchar()) {if(c == '-') f = -f;}
	for(; isdigit(c); c = getchar()) x = x * 10 + c - '0';
	x *= f;
}
template <typename T>
inline void write(T x) {
	if(x < 0) {x = -x; putchar('-');}
	if(x > 9) write(x / 10);
	putchar(x % 10 + '0');
}
template <typename T>
inline void writesp(T x, char sp = ' ') {
	write(x); putchar(sp);
}
const int maxN = 5e3 + 10, maxM = 5e3 + 10;
int n, m;
struct edge {
	int to, nxt, val;
} edge[maxM << 1];
int head[maxN], sz = 0;
int dis[maxN], vis[maxN], cnt[maxN];
struct node {
	int id, dis;
};
void add_edge(int u, int v, int w) {
	edge[++sz].to = v; edge[sz].val = w; edge[sz].nxt = head[u]; head[u] = sz;
}
int neg = 0;
bool spfa(int s) {
	vis[s] = 1; dis[s] = 0;
	queue<node> q;
	q.push((node){s, 0});
	while(!q.empty()) {
		node u = q.front(); q.pop();
		int v = u.id, w = u.dis; vis[v] = 0;
		for(int i = head[v]; i; i = edge[i].nxt) {
			int v1 = edge[i].to;
			if(dis[v1] > dis[v] + edge[i].val) {
				cnt[v1] = cnt[v] + 1;
				if(cnt[v1] >= n) return false; 
				dis[v1] = dis[v] + edge[i].val;
				if(!vis[v1]) {
					q.push((node){v1, dis[v1]}); vis[v1] = 1;
				}
			}
		}
	}
	return true;
}
int main() {
//	freopen(".in", "r", stdin);
//	freopen(".out", "w", stdout);
	read(n); read(m);
	_rep(i, 1, m) {
		int u, v, w;
		read(u); read(v); read(w);
		add_edge(v, u, w);
	}
	_rep(i, 1, n) {
		add_edge(0, i, 0);
	}
	_rep(i, 1, n) dis[i] = 1e9 + 10;
	bool flg = spfa(0);
	if(!flg) puts("NO");
	else {
		_rep(i, 1, n) {
			writesp(dis[i], ' ');
		}
		cout << endl;
	}
	return 0;
}
