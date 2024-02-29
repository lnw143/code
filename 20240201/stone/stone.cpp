#include<cstdio>
#include<vector>
using namespace std;
const int N = 3e5, LOG_N = 20, Q = 3e5;
int n,q,i,j,k,l,fa[N + 2],f[N + 2],g[N + 2],dep[N + 2],anc[N + 2][LOG_N];
vector<int> e[N + 2],p[Q + 2];
void dfs(int x) {
	g[x]=1<<30;
	dep[x]=dep[fa[x]]+1;
	anc[x][0]=fa[x];
	for(int i=1; i<LOG_N; ++i)
		anc[x][i]=anc[anc[x][i-1]][i-1];
	for(int v : e[x])
		dfs(v);
}
int lca(int x,int y) {
	if(dep[x]>dep[y]) swap(x,y);
	for(int i=LOG_N-1; i>=0; --i)
		if(dep[anc[y][i]]>=dep[x])
			y=anc[y][i];
	if(x==y) return x;
	for(int i=LOG_N-1; i>=0; --i)
		if(anc[x][i]!=anc[y][i])
			x=anc[x][i],y=anc[y][i];
	return anc[x][0];
}
int dis(int x,int y) {
	return dep[x]+dep[y]-2*dep[lca(x,y)];
}
int main() {
	freopen("stone.in","r",stdin);
	freopen("stone.out","w",stdout);
	scanf("%d",&n);
	for(i=2; i<=n; ++i) {
		scanf("%d",&fa[i]);
		e[fa[i]].push_back(i);
	}
	fa[1]=1;
	dfs(1);
	scanf("%d",&q);
	for(i=1; i<=q; ++i) {
		scanf("%d",&l);
		for(j=1; j<=l; ++j) {
			static int x;
			scanf("%d",&x);
			for(k=1; k<=n; ++k)
				f[k]=max(f[k],dis(x,k));
		}
		for(j=1; j<=n; ++j) {
			g[j]=min(g[j],f[j]);
			f[j]=0;
		}
	}
	for(i=1; i<=n; ++i)
		printf("%d\n",g[i]);
	return 0;
}