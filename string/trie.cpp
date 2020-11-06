#include<bits/stdc++.h>
#define _rep(i, x, y) for(int i = x; i <= y; i++)
using namespace std;
const int sigma_size = 26;
const int max_len = 50;
int ch[max_len][sigma_size];
bool _exist[max_len];
int _pass[max_len];
int tot = 1;
void _insert(char *s){
	int len = strlen(s); 
	int u = 1;
	_rep(i, 0, len - 1) {
		int c = s[i] - 'a';
		if(!ch[u][c]) ch[u][c] = ++tot;
		u = ch[u][c];
		_pass[u] += 1;
	}
	_exist[u] = true;
}
bool find_prefix(char *s, int opt = 0){
	int len = strlen(s);
	int u = 1;
	_rep(i, 0, len - 1) {
		int c = s[i] - 'a';
		if(!ch[u][c]) return false;
		u = ch[u][c];
	}
	if(opt == 0) return true;
	if(opt == 1) return _exist[u];
}
int count_prefix_of_trie(char *s) {
	int len = strlen(s);
	int u = 1;
	_rep(i, 0, len - 1) {
		int c = s[i] - 'a';
		if(!ch[u][c]) return 0;
		u = ch[u][c];
	}
	return _pass[u];
}
int count_prefix_of_mine(char *s){
	int len = strlen(s);
	int u = 1;
	int ans = 0;
	_rep(i, 0, len - 1) {
		int c = s[i] - 'a';
		if(!ch[u][c]) return ans;
		u = ch[u][c];
		ans += _exist[u];
	}
	return ans;
}
int main(){
	int Q;
	scanf("%d", &Q);
	
	while(Q--) {
		int opt; scanf("%d", &opt);
		char s[110]; scanf("%s", s);
		if(opt == 1) {
			_insert(s);
		} else if(opt == 2) {
			if(find_prefix(s) == true) printf("Yes!\n");
			else printf("No!\n");
		} else if(opt == 3) {
			if(find_prefix(s, 1) == true) printf("Yes!\n");
			else printf("No!\n");
		} else if(opt == 4) {
			printf("Ans = %d\n", count_prefix_of_trie(s));
		} else if(opt == 5) {
			printf("Ans = %d\n", count_prefix_of_mine(s));
		}
	}
	return 0;
}
