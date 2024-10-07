#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
const int N = 1e5, logN = 20;
int n,m,anc[logN][N + 2],dep[N + 2];
int ans[N + 2];
vector<int> e[N + 2],f[N + 2],g[N + 2];
void dfs(int u,int p) {
	dep[u]=dep[p]+1;
	anc[0][u]=p;
	for(int i=1; i<logN; ++i)
		anc[i][u]=anc[i-1][anc[i-1][u]];
	for(auto v : e[u])
		if(v!=p)
			dfs(v,u);
}
int lca(int u,int v) {
	if(dep[u]<dep[v]) swap(u,v);
	for(int i=logN-1; i>=0; --i)
		if(dep[anc[i][u]]>=dep[v])
			u=anc[i][u];
	if(u==v) return u;
	for(int i=logN-1; i>=0; --i)
		if(anc[i][u]!=anc[i][v])
			u=anc[i][u],
			v=anc[i][v];
	return anc[0][u];
}
namespace dsegtree {
	const int S = N << 5;
	int tot,ls[S + 2],rs[S + 2];
	struct node {
		int maxv,sum;
	} s[S + 2];
	bool operator<(const node& x,const node& y) {
		if(x.sum!=y.sum) return x.sum<y.sum;
		return x.maxv>y.maxv;
	}
#define mid (l+r>>1)
	void modf(int &u,int l,int r,int x,int k) {
		if(!u) u=++tot;
		if(l==r) {
			s[u].maxv=x;
			s[u].sum+=k;
			return ;
		}
		if(x<=mid) modf(ls[u],l,mid,x,k);
		else modf(rs[u],mid+1,r,x,k);
		s[u]=max(s[ls[u]],s[rs[u]]);
	}
	int merge(int u,int v,int l,int r) {
		if(!u||!v) return u|v;
		if(l==r) {
			s[u].sum+=s[v].sum;
			return u;
		}
		ls[u]=merge(ls[u],ls[v],l,mid);
		rs[u]=merge(rs[u],rs[v],mid+1,r);
		s[u]=max(s[ls[u]],s[rs[u]]);
		return u;
	}
}
int solve(int u) {
	int rt=0;
	for(auto v : e[u])
		if(v!=anc[0][u])
			rt=dsegtree::merge(rt,solve(v),1,N);
	for(auto i : f[u]) dsegtree::modf(rt,1,N,i,1);
	for(auto i : g[u]) dsegtree::modf(rt,1,N,i,-1);
	ans[u]=dsegtree::s[rt].sum?dsegtree::s[rt].maxv:0;
	return rt;
}
int main() {
	scanf("%d%d",&n,&m);
	for(int i=1; i<n; ++i) {
		int u,v;
		scanf("%d%d",&u,&v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs(1,1);
	for(int i=1; i<=m; ++i) {
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		int l=lca(x,y);
		f[x].push_back(z);
		f[y].push_back(z);
		g[l].push_back(z);
		if(l!=1) g[anc[0][l]].push_back(z);
	}
	solve(1);
	for(int i=1; i<=n; ++i) printf("%d\n",ans[i]);
	return 0;
}