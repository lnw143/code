#include<cstdio>
#include<vector>
using namespace std;
const int N = 1e5;
int n,m,c[N + 2],ans[N + 2];
vector<int> e[N + 2];
int sz[N + 2],dfn[N + 2],low[N + 2],pos[N + 2],dfc,wson[N + 2];
int tot[N + 2],sum;
void add(int c,int x) {
	if(tot[c]==0) ++sum;
	tot[c]+=x;
	if(tot[c]==0) --sum;
}
void cnt(int u,int fa) {
	pos[dfn[u]=++dfc]=u;
	sz[u]=1;
	wson[u]=0;
	for(auto v : e[u])
		if(v!=fa) {
			cnt(v,u);
			sz[u]+=sz[v];
			if(!wson[u]||sz[v]>wson[u])
				wson[u]=v;
		}
	low[u]=dfc;
}
void dfs(int u,int fa,bool keep) {
	for(auto v : e[u])
		if(v!=fa&&v!=wson[u])
			dfs(v,u,false);
	if(wson[u]) dfs(wson[u],u,true);
	for(auto v : e[u])
		if(v!=fa&&v!=wson[u])
			for(int i=dfn[v]; i<=low[v]; ++i)
				add(c[pos[i]],1);
	add(c[u],1);
	ans[u]=sum;
	if(!keep) 
		for(int i=dfn[u]; i<=low[u]; ++i)
			add(c[pos[i]],-1);
}
int main() {
	scanf("%d",&n);
	for(int i=1; i<n; ++i) {
		int x,y;
		scanf("%d%d",&x,&y);
		e[x].emplace_back(y);
		e[y].emplace_back(x);
	}
	for(int i=1; i<=n; ++i)
		scanf("%d",&c[i]);
	cnt(1,-1);
	dfs(1,-1,false);
	scanf("%d",&m);
	for(int i=1; i<=m; ++i) {
		int x;
		scanf("%d",&x);
		printf("%d\n",ans[x]);
	}
	return 0;
}