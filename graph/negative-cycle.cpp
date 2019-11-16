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
template <typename T>
inline void writesp(T x, char sp = '\n') {
	write(x); putchar(sp);
}
const int maxn = 1e5 + 5, maxm = 2e5 + 5;
int n, m, T, sz = 0;
struct Edge {
	int to, nxt, val;
} edge[maxm << 1];
int head[maxn];
int dis[maxn], vis[maxn], cnt[maxn];
void add_edge(int u, int v, int w) {
	edge[++sz].to = v; edge[sz].val = w; edge[sz].nxt = head[u]; head[u] = sz;
}
struct node {
	int id, dis;
};
bool spfa() {
	queue<node> q;
	q.push((node){1, 0});
	cnt[1] = 0;
	dis[1] = 0;
	vis[1] = 1;
	while(!q.empty()) {
		node u = q.front();
		q.pop();
		int v = u.id, d = u.dis;
		vis[v] = 0;
		for(int i = head[v]; i; i = edge[i].nxt) {
			if(dis[edge[i].to] > dis[v] + edge[i].val) {
				cnt[edge[i].to] = cnt[v] + 1;
				if(cnt[edge[i].to] >= n) return true;
				dis[edge[i].to] = dis[v] + edge[i].val; 
				if(!vis[edge[i].to]) {q.push((node){edge[i].to, dis[edge[i].to]}); vis[edge[i].to] = 1;}
			}
		}
	}
	return false;
}
int main() {
	read(T);
	while(T--) {
		memset(head, 0, sizeof(head));
		memset(vis, 0, sizeof(vis));
		memset(cnt, 0, sizeof(cnt));
		read(n); read(m);
		_rep(i, 1, n) dis[i] = 0x7f7f7f7f;
		_rep(i, 1, m) {
			int x, y, w;
			read(x); read(y); read(w);
			add_edge(x, y, w);
			if(w >= 0) add_edge(y, x, w);
		}
		puts(spfa() ? "YE5" : "N0");
	}
	
	return 0;
}

