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
struct node {
    int ch[2], fa, siz, cnt, val;
};
const int maxN = 1e5;
struct SplayTree {
    node tree[maxN];
    int Siz, root;
    void maintain(int x) {tree[x].siz = tree[tree[x].ch[0]].siz + tree[tree[x].ch[1]].siz + tree[x].cnt;}
    int dir(int x) {return (x == tree[tree[x].fa].ch[1]);} 
	void clear(int x) {tree[x].siz = tree[x].ch[0] = tree[x].ch[1] = tree[x].fa = tree[x].cnt = tree[x].val = 0;}
	void rotate(int x) {
		int y = tree[x].fa, alpha = tree[y].fa;
		int d = dir(x), d2 = dir(y);
		tree[y].ch[d] = tree[x].ch[d ^ 1]; tree[tree[x].ch[d ^ 1]].fa = y;
		tree[x].ch[d ^ 1] = y; tree[y].fa = x;
		tree[x].fa = alpha;
		if(alpha) tree[alpha].ch[y == tree[alpha].ch[1]] = x; 
		maintain(y); maintain(x);
	} 
	void splay(int x) {
		for(int f = tree[x].fa; f = tree[x].fa, f; rotate(x)) {
			if(tree[f].fa) rotate(dir(f) == dir(x) ? f : x);
		}
		root = x;
	}
	void insert(int k) {
		if(!root) {tree[++Siz].val = k; tree[Siz].cnt++; root = Siz; maintain(Siz); return;}
		int pos = root, f = 0;
		while(1) {
			if(k == tree[pos].val) {tree[pos].cnt++; maintain(pos); maintain(f); splay(pos); break;}
			f = pos; pos = tree[pos].ch[tree[pos].val < k];
			if(!pos) {tree[++Siz].val = k; tree[Siz].cnt++; tree[Siz].fa = f; tree[f].ch[tree[f].val < k] = Siz; maintain(Siz); maintain(f); splay(Siz); break;}
		}
	}
	int get_extrema(int ki, int is_pos) {
		int pos = root;
		while(tree[pos].ch[ki]) pos = tree[pos].ch[ki];
		splay(pos);
		return (is_pos ? pos : tree[pos].val);
	}
	int pred(int is_pos = 0) {
		int pos = tree[root].ch[0];
		while(tree[pos].ch[1]) pos = tree[pos].ch[1];
		splay(pos); return (is_pos ? pos : tree[pos].val);
	}
	int succ(int is_pos = 0) {
		int pos = tree[root].ch[1];
		while(tree[pos].ch[0]) pos = tree[pos].ch[0];
		splay(pos); return (is_pos ? pos : tree[pos].val);
	}
	int kth(int k) {
		int pos = root;
		while(1) {
			if(tree[pos].ch[0] && tree[tree[pos].ch[0]].siz >= k) pos = tree[pos].ch[0];
			else {
				k -= tree[pos].cnt + tree[tree[pos].ch[0]].siz;
				if(k <= 0) {splay(pos); return tree[pos].val;}
				pos = tree[pos].ch[1];
			}
		}
	}
	int rank(int x) {
		int ans = 0, pos = root;
		while(1) {
		//	cout << ans << " " << pos << " " << tree[pos].val << " " << x << endl;
			if(tree[pos].val > x) {
				pos = tree[pos].ch[0];
			} else {
				ans += tree[tree[pos].ch[0]].siz;
				if(x == tree[pos].val) {splay(pos); return ans + 1;}
				ans += tree[pos].cnt; pos = tree[pos].ch[1];
			}
		}
	}
	void remove(int k) {
	//	cout << 1 << endl;
		int q = rank(k);
		if(tree[root].cnt > 1) {tree[root].cnt--; maintain(root); return;}
		if(!tree[root].ch[0] && !tree[root].ch[1]) {clear(root); root = 0; return;}
		if((!tree[root].ch[0]) || (!tree[root].ch[1])) {int pos = root; root = tree[root].ch[!tree[root].ch[0]]; tree[root].fa = 0; clear(pos); return;}
		int pos = root, r = pred(1);
		splay(r); tree[tree[pos].ch[1]].fa = r; tree[r].ch[1] = tree[pos].ch[1]; clear(pos); maintain(root);
	}
	void debug() {
		cout << "Root vertex: " << root << endl;
		_rep(i, 1, Siz) {
			cout << i << " " << tree[i].ch[0] << " " << tree[i].ch[1] << " " << tree[i].fa << " " << tree[i].siz << " " << tree[i].cnt << " " << tree[i].val << endl;
		}
		cout << "--------\n";
	}
} BST;
int main() {
	int n; read(n);
	while(n--) {
		int opt, k; read(opt, k);
	//	writesp(opt, '\n');
		if(opt == 1) {BST.insert(k);}
		if(opt == 2) {BST.remove(k);}
		if(opt == 3) {writesp(BST.rank(k), '\n');}
		if(opt == 4) {writesp(BST.kth(k), '\n');}
		if(opt == 5) {BST.insert(k); int m = BST.pred(); writesp(m, '\n'); BST.remove(k);}
		if(opt == 6) {BST.insert(k); int m = BST.succ(); writesp(m, '\n'); BST.remove(k);}
	//	BST.debug();
	}
	return 0;
}
