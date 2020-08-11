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
const int maxN = 1e6 + 10;
const int Sigma = 27;
char s[maxN];
struct ac_automaton {
	int nxt[maxN][Sigma], cnt;
	int fail[maxN], exist[maxN];
	void insert(char *s) {
		int len = strlen(s), p = 0;
		_rep(i, 0, len - 1) {
			int c = s[i] - 'a';
			if(!nxt[p][c]) nxt[p][c] = ++cnt;
			p = nxt[p][c];
		}
		exist[p]++;
	}
	void getFail() {
		std::queue<int> q;
		_rep(i, 0, 25) {
			if(nxt[0][i]) q.push(nxt[0][i]);
		}
		while(!q.empty()) {
			int u = q.front(); q.pop();
			_rep(i, 0, 25) {
				if(nxt[u][i]) {
					fail[nxt[u][i]] = nxt[fail[u]][i], q.push(nxt[u][i]);
				} else {
					nxt[u][i] = nxt[fail[u]][i];
				}
			}
		}
	}
	int query(char *s) {
		int u = 0, ans = 0, len = strlen(s);
		_rep(i, 0, len - 1) {
			u = nxt[u][s[i] - 'a'];
			for(int j = u; j && exist[j] != -1; j = fail[j]) {
				ans += exist[j]; exist[j] = -1;
			}
		}
		return ans;
	}
} ac;
int main() {
	int n; read(n);
	_rep(i, 1, n) {
		scanf("%s", s);
		ac.insert(s);
	}
	ac.getFail();
	scanf("%s", s);
	writesp(ac.query(s), '\n');
	return 0;
}
