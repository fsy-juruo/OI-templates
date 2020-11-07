#include <bits/stdc++.h>

const int maxN = 1e5 + 10, maxLog = 31 + 10, Sigma = 3;
int trie[maxN * 32][Sigma], tot = 0;

void insert_trie(int x) {
    int ch = 0;
    for(int i = 30; i >= 0; i--) {
        int u = x >> i & 1;
        if(!trie[ch][u]) trie[ch][u] = ++tot;
        ch = trie[ch][u];
    }
}

int query(int x) {
    int ch = 0, Num = 0;
    for(int i = 30; i >= 0; i--) {
    	int u = x >> i & 1;
    	if(!trie[ch][!u]) {
    		Num = (Num << 1) + u; 
    		ch = trie[ch][u];
		} else {
			Num = (Num << 1) + !u;
			ch = trie[ch][!u];
		}
	}
	return (Num ^ x);
}

int main() {
    int n, maxans = 0; scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
    	int x; scanf("%d", &x);
		insert_trie(x);
		maxans = std::max(maxans, query(x));
	}
	printf("%d\n", maxans);
    return 0;
}
