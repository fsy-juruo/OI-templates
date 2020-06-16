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
	int from, to, nxt, flow;
} edge[maxM << 1];
int head[maxN], sz = 1;
void add_edge(int u, int v, int w) {
	edge[++sz].from = u; edge[sz].to = v; edge[sz].flow = w; edge[sz].nxt = head[u]; head[u] = sz;
}
int vis[maxN], flows[maxN], pre[maxN];
bool edmond_karp(int s) {
    memset(vis, 0, sizeof(vis));
    queue<int> q; q.push(s); vis[s] = 1; flows[s] = (1 << 30);
    while(!q.empty()) {
        int u = q.front(); q.pop();
        for(int i = head[u]; i; i = edge[i].nxt) {
            if(!edge[i].flow) continue;
            int v = edge[i].to;
            if(vis[v]) continue;
            flows[v] = min(flows[u], edge[i].flow); 
            pre[v] = i; 
            q.push(v); vis[v] = 1;
            if(v == t) return true;
        }
    }
    return false;
}
void modify() {
    int x = t;
    while(x != s) {
        int i = pre[x];
        edge[i].flow -= flows[t];
        edge[i ^ 1].flow += flows[t];
        x = edge[i].from;
    }
}
int main() {
	read(n, m, s, t);
	_rep(i, 1, m) {
        int u, v, w; read(u, v, w);
        add_edge(u, v, w); add_edge(v, u, 0);
    }
    int ans = 0;
    while(edmond_karp(s)) ans += flows[t], modify();
    writesp(ans, '\n');
	return 0;
}
