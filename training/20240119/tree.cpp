#include<cstdio>
using namespace std;
const int N = 1e5;
int n,m,i,em,e[N * 2],ls[N + 2],nx[N * 2],dfc;
void insert(int x,int y) {
	e[++em]=y;
	nx[em]=ls[x];
	ls[x]=em;
}
int wson[N + 2],top[N + 2],dfn[N + 2],dep[N + 2],fa[N + 2],sz[N + 2];
void dfs(int x) {
	sz[x]=1;
	for(int i=ls[x]; i; i=nx[i])
		if(e[i]!=fa[x]) {
			dep[e[i]]=dep[x]+1;
			fa[e[i]]=x;
			dfs(e[i]);
			if(sz[e[i]]>sz[wson[x]])
				wson[x]=e[i];
			sz[x]+=sz[e[i]];
		}
}
void dfs2(int x,int tp) {
	dfn[x]=++dfc;
	top[x]=tp;
	if(wson[x]) dfs2(wson[x],tp);
	for(int i=ls[x]; i; i=nx[i])
		if(e[i]!=wson[x]&&e[i]!=fa[x])
			dfs2(e[i],e[i]);
}

int main() {
	// freopen("tree.in","r",stdin);
	// freopen("tree.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(i=1; i<n; ++i) {
		static int u,v;
		scanf("%d%d",&u,&v);
		insert(u,v);
		insert(v,u);
	}
	dep[1]=1;
	dfs(1);
	dfs2(1,1);
	for(i=1; i<=m; ++i) {
		static int t,u,v;
		scanf("%d",&t);
		if(t==1) {
			scanf("%d%d",&u,&v);
			// flip(u,v);
		} else {
			scanf("%d",&u);
			// printf("%d\n",ask(u,-1));
		}
	}
	return 0;
}