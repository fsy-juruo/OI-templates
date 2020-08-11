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
	for(; !isdigit(c); c = getchar()) {
		if(c == '-') f = -f;
	}
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
inline void writesp(T x, char sp = ' ') {
	write(x); putchar(sp);
}
const int maxN = 1e4 + 10, maxM = 1e5 + 10;
int n, m, s, t;
struct Edge {
	int from, to, nxt;
    LL flow;
} edge[maxM << 1];
int head[maxN], sz = 1;
void add_edge(int u, int v, int w) {
	edge[++sz].from = u; edge[sz].to = v; edge[sz].flow = w; edge[sz].nxt = head[u]; head[u] = sz;
}
int dep[maxN];
queue<int> q;
bool bfs() {
    memset(dep, 0, sizeof(dep));
    while(!q.empty()) q.pop();
    q.push(s); dep[s] = 1;
    while(!q.empty()) {
        int u = q.front(); q.pop();
        for(int i = head[u]; i; i = edge[i].nxt) {
            int v = edge[i].to;
            if(edge[i].flow && (!dep[v])) {
                q.push(v);
                dep[v] = dep[u] + 1;
                if(v == t) return true;
            }
        }
    }
    return false;
}
LL dfs(int x, int flow) { // dinic 
    if(x == t) return flow;
    LL r = flow; int k;
    for(int i = head[x]; i && r; i = edge[i].nxt) {
        int v = edge[i].to;
        if(dep[v] == dep[x] + 1 && edge[i].flow) {
            k = dfs(v, min(r, edge[i].flow)); // question
            if(!k) dep[v] = 0;
            edge[i].flow -= k; edge[i ^ 1].flow += k;
            r -= k;
        }
    }
    return flow - r; 
}
int main() {
	read(n, m, s, t);
	_rep(i, 1, m) {
        int u, v, w; read(u, v, w);
        add_edge(u, v, w); add_edge(v, u, 0);
    }
    LL ans = 0, f = 0;
    while(bfs()) {
        while(f = dfs(s, (1 << 30))) ans += f;
    }
    writesp(ans, '\n');
	return 0;
}
