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
        if (c == '-')
            f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - 48;
    x *= f;
}
template <typename T>
inline void write(T x) {
	if(x < 0) {putchar('-'); x = -x;}
	if(x > 9) write(x / 10);
	putchar(x % 10 + '0');
}
const int maxn = 1e5 + 5, maxm = 2e5 + 5;
int n, m, s, sz = 0;
struct Edge {
	int to, nxt, val;
} edge[maxm << 1];
int head[maxn];
int dis[maxn], vis[maxn];
void add_edge(int u, int v, int w) {
	edge[++sz].to = v; edge[sz].val = w; edge[sz].nxt = head[u]; head[u] = sz;
}
struct node {
	int id, dis;
	bool operator < (const node &B) const {
		return B.dis < dis;
	}
};
void dijkstra(int u) {
	dis[u] = 0;
	priority_queue<node> heap;
	heap.push((node) {u, 0});
	while(!heap.empty()) {
		node k = heap.top();
		heap.pop();
		int v = k.id, w = k.dis;
		if(vis[v]) continue;
		vis[v] = 1;
		for(int i = head[v]; i; i = edge[i].nxt) {
			if(dis[v] + edge[i].val < dis[edge[i].to]) {
				dis[edge[i].to] = dis[v] + edge[i].val;
				heap.push((node) {edge[i].to, dis[edge[i].to]});
			}
		}
	}
}
int main() {
	read(n); read(m); read(s);
	_rep(i, 1, n) dis[i] = 0x7f7f7f7f;
	_rep(i, 1, m) {
		int x, y, w;
		read(x); read(y); read(w);
		add_edge(x, y, w);
	}
	dijkstra(s);
	_rep(i, 1, n) {
		write(dis[i]); putchar(' ');
	}
	return 0;
}
