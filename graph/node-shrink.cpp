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

const int maxN = 1e4 + 10, maxM = 1e5 + 10;
int n, m, deg[maxN], val[maxN];
struct Edge {
	int from, to, nxt;
} edge[maxM];
int head[maxN], sz = 0;
void add_edge(int u, int v) {
	edge[++sz].from = u; edge[sz].to = v; edge[sz].nxt = head[u]; head[u] = sz;
}

int dfn[maxN], low[maxN], totval[maxN], scc[maxN], stk[maxN], ins[maxN], timer = 0, tp = 0, sccCnt = 0;
void tarjan(int x) {
	ins[x] = 1; stk[++tp] = x; dfn[x] = low[x] = ++timer;
	for(int i = head[x]; i; i = edge[i].nxt) {
		int v = edge[i].to;
		if(!dfn[v]) {
			tarjan(v);
			low[x] = std::min(low[x], low[v]);
		} else if(ins[v]) {
			low[x] = std::min(low[x], dfn[v]);
		}
	}
	if(low[x] == dfn[x]) {
		sccCnt++; int y;
		do {
			y = stk[tp--]; 
			ins[y] = 0; scc[y] = sccCnt; totval[sccCnt] += val[y];
		} while(x != y);
	}
}


int Topo[maxN], in[maxN], qwq = 0, dp[maxN];

void answer(int u) {
	if(dp[u]) return;
	dp[u] = totval[u]; int maxSum = 0;
	for(int i = head[u]; i; i = edge[i].nxt) {
		if(!dp[edge[i].to]) answer(edge[i].to);
		maxSum = std::max(maxSum, dp[edge[i].to]);
	}	
	dp[u] += maxSum;
}
int main() {
	read(n, m);
	_rep(i, 1, n) read(val[i]);
	_rep(i, 1, m) {
		int x, y; read(x, y);
		add_edge(x, y); 
	}
	_rep(i, 1, n) {
		if(!dfn[i]) tarjan(i);
	}
	
	memset(head, 0, sizeof(head)); sz = 0;
	_rep(i, 1, m) {
		if(scc[edge[i].from] != scc[edge[i].to]) {
			add_edge(scc[edge[i].from], scc[edge[i].to]);
//			std::cout << scc[edge[i].from] << " " << scc[edge[i].to] << std::endl;
		}
	}
//	topo();
	int Ans = 0;
	_rep(i, 1, sccCnt) {
		if(!dp[i]) {
			answer(i);
			Ans = std::max(Ans, dp[i]);
		}
	}
	writesp(Ans, '\n');
	return 0;
}

