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
const int maxn = 2e6 + 5, maxm = 1e6 + 5;
int n, m, a, b, c, sz = 0;
struct Edge {
	int to, nxt;
} edge[maxm << 1];
int head[maxn];
void add_edge(int u, int v) {
	edge[++sz].to = v; edge[sz].nxt = head[u]; head[u] = sz;
}
int dfn[maxn], low[maxn], scc[maxn], len[maxn], stk[maxn], vis[maxn], top = 0, blk = 0, timer = 0;
void tarjan(int u) {
	dfn[u] = low[u] = ++timer;
	vis[u] = true;
	stk[++top] = u;
	for(int i = head[u]; i; i = edge[i].nxt) {
		int v = edge[i].to;
		if(!dfn[v]) {
			tarjan(v);
			low[u] = min(low[u], low[v]);
		} else if(vis[v]) {
			low[u] = min(low[u], dfn[v]);
		}
	}
	if(low[u] == dfn[u]) {
		++blk;
		do {
			scc[u] = blk;
			u = stk[top]; --top;
			vis[u] = false;
		} while(low[u] != dfn[u]);
	//	scc[stk[top]] = blk; len[blk]++; --top;
	}
}
int main() {
	read(n); read(m);
	_rep(i, 1, m) {
		int x1, b1, x2, b2;
		read(x1); read(b1); read(x2); read(b2);
		add_edge(x1 + (1 & b1) * n, x2 + (1 ^ b2) * n);
		add_edge(x2 + (1 & b2) * n, x1 + (1 ^ b1) * n);
	}
	_rep(i, 1, n << 1) {
		if(!dfn[i]) tarjan(i);
	}
	_rep(i, 1, n) {
		if(scc[i] == scc[i + n]) {
			puts("IMPOSSIBLE");
			return 0;
		}
	}
	puts("POSSIBLE");
	
	_rep(i, 1, n) {
		write((scc[i] < scc[i + n])); putchar(' ');
	}
	puts("");
	return 0;
}

