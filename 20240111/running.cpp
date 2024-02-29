#include<cstdio>
#include<vector>
#include<atcoder/all>
using namespace std;
const int N = 3e5, M = 3e5, LOG_N = 19;
int n,m,i,em,e[N * 2],ls[N + 2],nx[N * 2 + 2],w[N + 2],s[M + 2],t[M + 2],len[M + 2],l[M + 2],sum[N + 2],anc[N + 2][LOG_N];
int dep[N + 2],f[N + 2],g[N * 2 + 2],ans[N + 2];
vector<int> u[N + 2],r[N + 2];
void insert(int x,int y) {
	e[++em]=y;
	nx[em]=ls[x];
	ls[x]=em;
}
void dfs(int x) {
	for(int i=1; i<LOG_N; ++i)
		anc[x][i]=anc[anc[x][i-1]][i-1];
	for(int i=ls[x]; i; i=nx[i])
		if(e[i]!=anc[x][0]) {
			dep[e[i]]=dep[x]+1;
			anc[e[i]][0]=x;
			dfs(e[i]);
		}
}
int lca(int x,int y) {
	if(dep[x]>dep[y]) x^=y^=x^=y;
	for(int i=LOG_N-1; i>=0; --i)
		if(dep[anc[y][i]]>=dep[x])
			y=anc[y][i];
	if(x==y) return x;
	for(int i=LOG_N-1; i>=0; --i)
		if(anc[y][i]!=anc[x][i])
			y=anc[y][i],x=anc[x][i];
	return anc[x][0];
}
#define ff(x) ((x)<=n?f[x]:0)
#define gg(x) (g[(x)+n])
void cnt(int x) {
	int F=ff(w[x]+dep[x]),G=gg(w[x]-dep[x]);
	f[dep[x]]+=sum[x];
	for(int i=ls[x]; i; i=nx[i])
		if(e[i]!=anc[x][0])
			cnt(e[i]);
	for(int i : r[x])
		++gg(len[i]-dep[x]);
	ans[x]=ff(w[x]+dep[x])-F+gg(w[x]-dep[x])-G;
	for(int i : u[x]) {
		f[dep[s[i]]]--;
		--gg(len[i]-dep[t[i]]);
		if(w[x]+dep[x]==dep[s[i]])
			--ans[x];
	}
}
int main() {
	freopen("running.in","r",stdin);
	freopen("running.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(i=1; i<n; ++i) {
		int u,v;
		scanf("%d%d",&u,&v);
		insert(u,v);
		insert(v,u);
	}
	for(i=1; i<=n; ++i)
		scanf("%d",&w[i]);
	anc[1][0]=1;
	dep[1]=1;
	dfs(1);
	for(i=1; i<=m; ++i) {
		scanf("%d%d",&s[i],&t[i]);
		++sum[s[i]];
		l[i]=lca(s[i],t[i]);
		u[l[i]].push_back(i);
		len[i]=dep[s[i]]+dep[t[i]]-2*dep[l[i]];
		r[t[i]].push_back(i);
	}
	cnt(1);
	for(i=1; i<=n; ++i)
		printf("%d ",ans[i]);
	return 0;
}