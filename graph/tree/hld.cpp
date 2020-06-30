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
const int maxN = 1e5 + 10, maxM = 1e5 + 10;
// initialization
int w[maxN];
int n, m, r, P;
struct Edge {
    int from, to, nxt;
} edge[maxM << 1];
int head[maxN], sz = 0;
void add_edge(int u, int v) {
    edge[++sz].from = u; edge[sz].to = v; edge[sz].nxt = head[u]; head[u] = sz;
}
// hld dfs part
int dep[maxN], siz[maxN], fa[maxN], hson[maxN];
int dfn[maxN], tp[maxN], rank[maxN], wrank[maxN], timer = 0;
void dfs1(int u, int f, int d) {
    dep[u] = d; siz[u] = 1; hson[u] = 0; fa[u] = f;
    int max_size = -1;
    for(int i = head[u]; i; i = edge[i].nxt) {
        int v = edge[i].to;
        if(v == f) continue;
        dfs1(v, u, d + 1); 
        siz[u] += siz[v];
        if(siz[v] > max_size) hson[u] = v, max_size = siz[v];
    }
}
void dfs2(int u, int top) {
    dfn[u] = ++timer; tp[u] = top; rank[timer] = u; wrank[timer] = w[u];
    if(!hson[u]) return;
    dfs2(hson[u], top);
    for(int i = head[u]; i; i = edge[i].nxt) {
        int v = edge[i].to;
        if(v == fa[u] || v == hson[u]) continue;
        dfs2(v, v);
    }
}
// segment tree part
struct node {int val, tag;};
struct SegmentTree {
    node tree[maxN << 2];
    void push_up(int o) {tree[o].val = tree[o << 1].val + tree[o << 1 | 1].val;}
    void push_down(int o, int l, int r) {
        if(tree[o].tag) {
            int mid = (l + r) >> 1; 
            tree[o << 1].val = (tree[o << 1].val + 1ll * tree[o].tag * (mid - l + 1) % P) % P;
            tree[o << 1 | 1].val = (tree[o << 1 | 1].val + 1ll * tree[o].tag * (r - mid) % P) % P;
            tree[o << 1].tag = (tree[o << 1].tag + tree[o].tag) % P;
            tree[o << 1 | 1].tag = (tree[o << 1 | 1].tag + tree[o].tag) % P;
            tree[o].tag = 0;
        }
    }
    void build(int o, int l, int r) {
        if(l == r) {tree[o].val = wrank[l] % P; return;}
        int mid = (l + r) >> 1;
        build(o << 1, l, mid); build(o << 1 | 1, mid + 1, r); push_up(o); return;
    }
    void modify(int o, int l, int r, int lx, int rx, int delta) {
        if(r < lx || rx < l) return;
        if(lx <= l && r <= rx) {
            tree[o].val = (tree[o].val + 1ll * delta * (r - l + 1) % P) % P;
            tree[o].tag = (tree[o].tag + delta) % P; return;
        }
        push_down(o, l, r);
        int mid = (l + r) >> 1;
        modify(o << 1, l, mid, lx, rx, delta); modify(o << 1 | 1, mid + 1, r, lx, rx, delta); push_up(o); return;
    }
    int query(int o, int l, int r, int lx, int rx) {
        if(r < lx || rx < l) return 0;
        if(lx <= l && r <= rx) return tree[o].val;
        push_down(o, l, r);
        int mid = (l + r) >> 1;
        return (query(o << 1, l, mid, lx, rx) + query(o << 1 | 1, mid + 1, r, lx, rx)) % P;
    }
} sgt;
// hld query part
struct HLD {
    void subtree_upd(int u, int k) {sgt.modify(1, 1, n, dfn[u], dfn[u] + siz[u] - 1, k);}
    int subtree_query(int u) {return sgt.query(1, 1, n, dfn[u], dfn[u] + siz[u] - 1);}
    void path_upd(int u, int v, int k) {
        while(tp[u] != tp[v]) {
            if(dep[tp[u]] < dep[tp[v]]) std::swap(u, v);
            sgt.modify(1, 1, n, dfn[tp[u]], dfn[u], k);
            u = fa[tp[u]];
        }
        if(dep[u] > dep[v]) std::swap(u, v);
        sgt.modify(1, 1, n, dfn[u], dfn[v], k);
    }
    int path_query(int u, int v) {
        int ans = 0;
        while(tp[u] != tp[v]) {
            if(dep[tp[u]] < dep[tp[v]]) std::swap(u, v);
            ans = (ans + sgt.query(1, 1, n, dfn[tp[u]], dfn[u])) % P;
            u = fa[tp[u]];
        }
        if(dep[u] > dep[v]) std::swap(u, v);
        return (ans + sgt.query(1, 1, n, dfn[u], dfn[v])) % P;
    }
} hld;
int main() {
//	freopen(".in", "r", stdin);
//	freopen(".out", "w", stdout);
    read(n, m, r, P);
    _rep(i, 1, n) read(w[i]);
    _rep(i, 1, n - 1) {
        int u, v; read(u, v);
        add_edge(u, v); add_edge(v, u);
    }
    dfs1(r, 0, 0); dfs2(r, r);
    sgt.build(1, 1, n);
    _rep(i, 1, m) {
        int opt, a, b, c; read(opt, a);
        if(opt == 1) {
            read(b, c); hld.path_upd(a, b, c);
        } else if(opt == 2) {
            read(b); writesp(hld.path_query(a, b), '\n');
        } else if(opt == 3) {
            read(b); hld.subtree_upd(a, b);
        } else {
            writesp(hld.subtree_query(a), '\n');
        }
    }
	return 0;
}
