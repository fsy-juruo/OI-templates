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
const int maxn = 3e5 + 5;
char s1[maxn], s2[maxn];
struct KMP {
	int lena, lenb;
	int nxt[maxn], f[maxn];
	void getNext() {
		nxt[1] = 0;
		for(int i = 2, j = 0; i <= lenb; i++) {
			while(j > 0 && s2[i] != s2[j + 1]) j = nxt[j];
			if(s2[i] == s2[j + 1]) j++;
			nxt[i] = j;
		}
	}
	void getF() {
		for(int i = 1, j = 0; i <= lena; i++) {
			while(j > 0 && s2[j + 1] != s1[i]) j = nxt[j];
			if(s2[j + 1] == s1[i]) j++;
			f[i] = j;
			if(j == lenb) {
				writesp(i - lenb + 1);
				j = nxt[j];
			}
		}
		_rep(i, 1, lenb) {
			writesp(nxt[i], ' ');
		}
	}
} kmp;
int main() {
	cin >> s1 + 1;
	cin >> s2 + 1;
	kmp.lena = strlen(s1 + 1);
	kmp.lenb = strlen(s2 + 1);
	kmp.getNext();
	kmp.getF();
	return 0;
}
