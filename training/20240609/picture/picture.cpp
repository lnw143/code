#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
char sss;
const int N = 1e5, M = 2e5;
int n,m,q,x[M + 2],y[M + 2];
bool t[M + 2];
vector<int> e[N + 2];
int fa[N + 2];
int find(int u) {
	return fa[u]==u?u:fa[u]=find(fa[u]);
}
namespace segtree {
	const int S = N << 2;
	int s[S],t[S + 2];
#define mid (l+r>>1)
#define ls (u<<1)
#define rs (ls|1)
#define li ls,l,mid
#define ri rs,mid+1,r
	void build(int u,int l,int r) {
		if(l==r) {
			s[u]=1;
			return ;
		}
		build(li);
		build(ri);
		s[u]=s[ls]+s[rs];
	}
	void modify(int u,int l,int r,int x,int y) {
		if(r<x||y<l) return ;
		if(x<=l&&r<=y) {
			t[u]=1;
			s[u]=0;
			return ;
		}
		modify(li,x,y);
		modify(ri,x,y);
		s[u]=t[u]?0:s[ls]+s[rs];
		return ;
	}
	int query(int u,int l,int r,int x,int y) {
		if(r<x||y<l||t[u]) return 0;
		if(x<=l&&r<=y) return s[u];
		return query(li,x,y)+query(ri,x,y);
	}
#undef mid
#undef ls
#undef rs
#undef li
#undef ri
}
namespace treecut {
	int pa[N + 2],dep[N + 2],wson[N + 2],size[N + 2],dfc,dfn[N + 2],top[N + 2];
	void dfs1(int u,int p) {
		size[u]=1;
		for(auto v : e[u])
			if(v!=p) {
				pa[v]=u;
				dep[v]=dep[u]+1;
				dfs1(v,u);
				size[u]+=size[v];
				if(size[v]>size[wson[u]]) wson[u]=v;
			}
		return ;
	}
	void dfs2(int u,int Top) {
		top[u]=Top;
		dfn[u]=++dfc;
		if(wson[u]) dfs2(wson[u],Top);
		for(auto v : e[u])
			if(!dfn[v])
				dfs2(v,v);
	}
#define all 1,1,dfc
	using segtree::build;
	using segtree::query;
	using segtree::modify;
	void init() {
		dfs1(1,1);
		dfs2(1,1);
		segtree::build(all);
	}
}
int ans;
void link(int u,int v) {
	using namespace treecut;
	while(top[u]!=top[v]) {
		if(dep[top[u]]<dep[top[v]]) swap(u,v);
		ans-=query(all,dfn[top[u]],dfn[u]);
		modify(all,dfn[top[u]],dfn[u]);
		u=pa[top[u]];
	}
	if(u!=v) {
		if(dep[u]<dep[v]) swap(u,v);
		ans-=query(all,dfn[v]+1,dfn[u]);
		modify(all,dfn[v]+1,dfn[u]);
	}
}
char ttt;
int main() {
	fprintf(stderr,"%lldkb\n",(&ttt-&sss)>>10);
	scanf("%d%d",&n,&m);
	for(int i=1; i<=m; ++i) scanf("%d%d",&x[i],&y[i]);
	for(int i=1; i<=n; ++i) fa[i]=i;
	for(int i=1; i<=m; ++i) {
		if(find(x[i])==find(y[i])) {
			t[i]=true;
			continue;
		}
		e[x[i]].push_back(y[i]);
		e[y[i]].push_back(x[i]);
		fa[find(x[i])]=find(y[i]);
	}
	treecut::init();
	ans=n-1;
	for(int i=1; i<=m; ++i)
		if(t[i])
			link(x[i],y[i]);
	scanf("%d",&q);
	for(int i=1; i<=q; ++i) {
		int u,v;
		scanf("%d%d",&u,&v);
		link(u,v);
		printf("%d\n",ans);
	}
	return 0;
}