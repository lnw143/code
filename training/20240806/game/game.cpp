#include <cstdio>
#include <queue>
#include <vector>
#include <utility>
using namespace std;
const int N = 1e5, M = 5e5;
int n,m,deg[N + 2],dep[N + 2];
vector<pair<int,bool>> e[N + 2];
char c[N + 2];
bool in_stk[N + 2],err;
void dfs(int u,int lim) {
	deg[u]=0;
	in_stk[u]=true;
	if(!c[u]) c[u]=dep[u]&1?'A':'B';
	for(auto [v,w] : e[u])
		if(deg[v]) {
			dep[v]=dep[u]+1;
			dfs(v,w?lim:dep[u]);
		} else if(in_stk[v]) {
			if(dep[v]<=lim||dep[v]%2==dep[u]%2)
				err=true;
		}
	in_stk[u]=false;
}
void help(int u) {
	for(auto [v,w] : e[u])
		if(!c[v]) {
			c[v]=c[u]=='A'?'B':'A';
			help(v);
		}
}
void solve(int u) {
	for(auto [v,w] : e[u]) {
		if(!c[v]) solve(v);
		c[u]=c[v]=='A'?'B':'A';
		break;
	}
	help(u);
}
int main() {
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1; i<=m; ++i) {
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		if(!z) swap(x,y);
		// printf("%d %d %d\n",x,y,z);
		e[x].emplace_back(y,z);
		++deg[y];
	}
	queue<int> Q;
	for(int i=1; i<=n; ++i)
		if(deg[i]==0) c[i]='C',Q.push(i);
		else if(e[i].size()==0) c[i]='D';
	while(Q.size()) {
		int u=Q.front();
		Q.pop();
		for(auto [v,w] : e[u])
			if(--deg[v]==0)
				Q.push(v);
	}
	for(int i=1; i<=n; ++i)
		if(deg[i]) {
			dep[i]=1;
			dfs(i,0);
		}
	if(err) return printf("NO"),0;
	for(int i=1; i<=n; ++i)
		if(!c[i])
			solve(i);
	printf("YES\n");
	for(int i=1; i<=n; ++i)
		putchar(c[i]);
	return 0;
}