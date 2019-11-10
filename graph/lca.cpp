#include <bits/stdc++.h>
#define _rep(i, x, y) for(int i = x; i <= y; i++)
#define _per(i, x, y) for(int i = x; i >= y; i--)
#define LL long long
using namespace std;
template <typename T>
inline void read(T &x) {
    x = 0;
    LL f = 1;
    char c = getchar();
    for (; !isdigit(c); c = getchar())
        if (c == '-')
            f = -1;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - 48;
    x *= f;
}
template <typename T>
inline void write(T x) {
	if(x < 0) {putchar('-'); x = -x;}
	if(x > 9) write(x / 10);
	putchar(x % 10 + '0');
}
const int maxn = 5e5 + 5, maxlog = 25;
int n, m, s;
struct Edge {
	int to, nxt;
} edge[maxn << 1];
int head[maxn], sz = 0;
void add_edge(int x, int y) {
	edge[++sz].to = y; edge[sz].nxt = head[x]; head[x] = sz;
}
int fa[maxn][maxlog], dep[maxn], lg[maxn];
void dfs(int root, int anc) {
	fa[root][0] = anc; 
	dep[root] = dep[anc] + 1;
	for(register int i = 1; i <= lg[dep[root]]; i++) {
		fa[root][i] = fa[fa[root][i - 1]][i - 1]; 
	} 
	for(register int i = head[root]; i; i = edge[i].nxt) {
		if(edge[i].to != anc) dfs(edge[i].to, root);
	}
}
int lca_query(int x, int y) {
	if(dep[x] < dep[y]) swap(x, y);
	while(dep[x] > dep[y]) x = fa[x][lg[dep[x] - dep[y]] - 1];
	if(x == y) return x;
	for(int i = lg[dep[x]] - 1; i >= 0; i--) {
		if(fa[x][i] != fa[y][i]) {
			x = fa[x][i]; y = fa[y][i];
		}
	}
	return fa[x][0];
}
int main() {
	read(n); read(m); read(s);
	_rep(i, 1, n - 1) {
		int a, b;
		read(a); read(b);
		add_edge(a, b); add_edge(b, a);
	}
	_rep(i, 1, n) {
		lg[i] = lg[i - 1] + (1 << lg[i - 1] == i);
	}
	dfs(s, 0);
	_rep(i, 1, m) {
		int a, b;
		read(a); read(b);
		write(lca_query(a, b)); puts("");
	}
	return 0;
}

