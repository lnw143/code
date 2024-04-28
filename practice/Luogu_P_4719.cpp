#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
constexpr int N = 1e5, M = N << 2, inf = 1e9;
int n,m,a[N + 2];
int f[N + 2][2],g[N + 2][2];
vector<int> e[N + 2];
int fa[N + 2],sz[N + 2],wson[N + 2],dfc,dfn[N + 2],low[N + 2],rnk[N + 2],top[N + 2],dep[N + 2];
void dfs(int u,int p) {
	fa[u]=p;
	sz[u]=1;
	f[u][1]=a[u];
	for(auto v : e[u])
		if(v!=p) {
			dep[v]=dep[u]+1;
			dfs(v,u);
			f[u][1]+=f[v][0];
			f[u][0]+=max(f[v][1],f[v][0]);
			sz[u]+=sz[v];
			if(sz[v]>sz[wson[u]]) wson[u]=v;
		}
}
void dfs2(int u,int p,int tp) {
	dfn[u]=++dfc;
	rnk[dfc]=u;
	top[u]=tp;
	if(wson[u]) dfs2(wson[u],u,tp);
	low[u]=dfc;
	g[u][1]=a[u];
	for(auto v : e[u])
		if(v!=p&&v!=wson[u]) {
			dfs2(v,u,v);
			g[u][1]+=f[v][0];
			g[u][0]+=max(f[v][1],f[v][0]);
		}
}
struct matrix {
	int n,m,a[5][5];
	int* operator[](int x) { return a[x]; }
	const int* operator[](int x) const { return a[x]; }
};
matrix operator*(const matrix& a,const matrix& b) {
	matrix c;
	c.n=a.n,c.m=b.m;
	assert(a.m==b.n);
	for(int i=1; i<=c.n; ++i)
		for(int j=1; j<=c.m; ++j) {
			c[i][j]=0;
			for(int k=1; k<=a.m; ++k)
				c[i][j]=max(c[i][j],a[i][k]+b[k][j]);
		}
	return c;
}
matrix tr[M];
#define mid (l+r>>1)
#define ls (u<<1)
#define rs (ls|1)
#define li ls,l,mid
#define ri rs,mid+1,r
matrix mat2x2(int a,int b,int c,int d) {
	matrix x;
	x.n=x.m=2;
	x[1][1]=a,x[1][2]=b,x[2][1]=c,x[2][2]=d;
	return x;
}
const matrix INF = mat2x2(0,-inf,-inf,0);
void build(int u,int l,int r) {
	if(l==r) {
		tr[u]=mat2x2(g[rnk[l]][1],g[rnk[l]][0],g[rnk[l]][1],-inf);
		// g[u][1]+=f[v][0];
		// g[u][0]+=max(f[v][1],f[v][0]);
		return ;
	}
	build(li);
	build(ri);
	tr[u]=tr[ls]*tr[rs];
}
matrix query(int u,int l,int r,int x,int y) {
	if(r<x||y<l) return INF;
	if(x<=l&&r<=y) return tr[u];
	return query(li,x,y)*query(ri,x,y);
}
void update(int u,int l,int r,int x,int y) {
	if(r<dfn[x]||dfn[x]<l) return ;
	if(l==r) {
		tr[u][1][1]+=y-a[x];
		tr[u][2][1]+=y-a[x];
		a[x]=y;
		return ;
	}
	if(dfn[x]<=mid) update(li,x,y);
	else update(ri,x,y);
	tr[u]=tr[ls]*tr[rs];
}
void update(int u,int l,int r,int x,const matrix& now,const matrix& past) {
	if(r<dfn[x]||dfn[x]<l) return ;
	if(l==r) {
		tr[u][1][1]+=now[1][1]-past[1][1];
		tr[u][2][1]+=now[1][1]-past[1][1];
		tr[u][1][2]+=max(now[1][1],now[1][2])-max(past[1][1],past[1][2]);
		return ;
	}
	if(dfn[x]<=mid) update(li,x,now,past);
	else update(ri,x,now,past);
	tr[u]=tr[ls]*tr[rs];
}
matrix get_ans(int x) {
	matrix s;
	s.n=1,s.m=2;
	s[1][1]=0;
	s[1][2]=a[rnk[low[x]]];
	s=s*query(1,1,n,dfn[top[x]],low[x]);
	return s;
}
int solve(int x,const matrix& past) {
	auto now=get_ans(x);
	if(top[x]==1) return max(now[1][1],now[1][2]);
	auto pans=get_ans(fa[top[x]]);
	update(1,1,n,fa[top[x]],now,past);
	solve(fa[top[x]],pans);
}
int main() {
	scanf("%d%d",&n,&m);
	for(int i=1; i<=n; ++i) scanf("%d",&a[i]);
	for(int i=1; i<n; ++i) {
		int u,v;
		scanf("%d%d",&u,&v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dep[1]=1;
	dfs(1,1);
	dfs2(1,1,1);
	build(1,1,n);
	for(int i=1; i<=m; ++i) {
		int x,y;
		scanf("%d%d",&x,&y);
		auto pans=get_ans(x);
		update(1,1,n,x,y);
		printf("%d\n",solve(x,pans));
	}
	return 0;
}