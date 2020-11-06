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
const int maxN = 2.5e5 + 10, maxM = 5e5 + 10, maxLog = 20;
int n, m;
struct Graph { // for being convenient
	struct Edge {
		int from, to, nxt, val;
	} edge[maxN << 1];
	int head[maxN], sz = 0;	
	void add_edge(int u, int v, int w = 1) {edge[++sz].from = u; edge[sz].to = v; edge[sz].val = w; edge[sz].nxt = head[u]; head[u] = sz;}
	void add(int u, int v, int w = 1) {add_edge(v, u, w); add_edge(u, v, w);}
	void init(int x = 0) {
		if(!x) memset(head, 0, sizeof(head)), sz = 0;
		else head[x] = 0;
	}
	void debug() {
		_rep(i, 1, sz) {
			printf("Edge %d: (%d, %d) weight: %d, nxt = %d\n", i, edge[i].from, edge[i].to, edge[i].val, edge[i].nxt);
		}
	}
} graph;
int dfn[maxN], fa[maxN][maxLog], lg[maxN], dep[maxN], timer = 0; // mindis[] : minimum 
LL mindis[maxN];
void dfs(int u, int f, int d, LL dis) {
	dep[u] = d; fa[u][0] = f; mindis[u] = dis; dfn[u] = ++timer;
	_rep(i, 1, lg[dep[u]]) fa[u][i] = fa[fa[u][i - 1]][i - 1];
	for(int i = graph.head[u]; i; i = graph.edge[i].nxt) {if(graph.edge[i].to != f) dfs(graph.edge[i].to, u, d + 1, std::min(mindis[u], 1ll * graph.edge[i].val));}
}
int lca_query(int x, int y) {
	if(dep[x] < dep[y]) std::swap(x, y);
	while(dep[x] > dep[y]) x = fa[x][lg[dep[x] - dep[y]] - 1];
	if(x == y) return x;
	for(int i = lg[dep[x]] - 1; i >= 0; i--) {
		if(fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
	}
	return fa[x][0];
}
bool cmp(int x, int y) {return dfn[x] < dfn[y];}
int stk[maxN], top = 0;
Graph virt;
int k, h[maxN], dev[maxN];
void build() {
    std::sort(h + 1, h + k + 1, cmp);
    stk[top = 1] = 1; virt.init(1); virt.sz = 0;
    _rep(i, 1, k) {
        if(h[i] == 1) continue;
        int l = lca_query(h[i], stk[top]);
//        _rep(j, 1, top) std::cout << stk[j] << ", ";
        if(l != stk[top]) {
            while(dfn[l] < dfn[stk[top - 1]]) {
                virt.add(stk[top - 1], stk[top]); --top;
            }
            if(dfn[l] > dfn[stk[top - 1]]) {
                virt.init(l); virt.add(stk[top], l); stk[top] = l;
            } else {
                virt.add(l, stk[top--]);
            }
        } 
        virt.init(h[i]); stk[++top] = h[i];
//        _rep(j, 1, top) std::cout << stk[j] << ", ";
//        std::cout << "size = " << virt.sz << "\n";
    }
    while(top > 1) {
        virt.add(stk[top - 1], stk[top]); top--;
    }
}
LL dp(int u, int f) {
    // let DP(u) =
    LL ans = 0; 
    for(int i = virt.head[u]; i; i = virt.edge[i].nxt) {
//    	std::cout << virt.edge[i].to << std::endl;
		if(virt.edge[i].to == f) continue;
        ans += dp(virt.edge[i].to, u);
    }
    if(dev[u]) ans = 1ll * mindis[u];
    else ans = std::min(ans, 1ll * mindis[u]);
    dev[u] = 0; virt.init(u); return ans;
}
int main() {
//	freopen(".in", "r", stdin);
//	freopen(".out", "w", stdout);
	read(n);
	_rep(i, 1, n - 1) {
		int x, y, z; read(x, y, z);
		graph.add(x, y, z);
	}
	lg[1] = 0;
	_rep(i, 1, n) lg[i] = lg[i >> 1] + 1;
    dfs(1, 0, 0, INT_MAX * 10086ll);
    read(m);
    _rep(i, 1, m) {
        read(k); 
        _rep(j, 1, k) read(h[j]), dev[h[j]] = 1;
        build();
//        virt.debug();
        writesp(dp(1, 0), '\n');
    }
	return 0;
}

