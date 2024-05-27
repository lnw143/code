#include<cstdio>
#include<random>
#include<algorithm>
using namespace std;
using ll = long long;
const int N = 5e5, M = 1e6, P = 1e9 + 7;
mt19937 rnd(random_device{}());
int n,m,tot,i,f[N + 2][2],pw2[M + 2],ans;
int u[M + 2],v[M + 2],em,e[M * 2 + 2],ls[N + 2],nx[M * 2 + 2];
int dfn[N + 2],low[N + 2],dfc;
int stk[N + 2],scc[N + 2],cnt[N + 2],ent[N + 2],tp;
void insert(int x,int y) {
	e[++em]=y;
	nx[em]=ls[x];
	ls[x]=em;
}
int dfs(int x,int fa) {
	low[x]=dfn[x]=++dfc;
	int sz=1;
	stk[++tp]=x;
	for(int i=ls[x]; i; i=nx[i])
		if(!dfn[e[i]]) {
			sz+=dfs(e[i],x);
			low[x]=min(low[x],low[e[i]]);
		} else if(e[i]!=fa)
			low[x]=min(low[x],dfn[e[i]]);
	if(low[x]>dfn[fa]) {
		++tot;
		do
			scc[stk[tp]]=tot,++cnt[tot];
		while(stk[tp--]!=x);
	}
	return sz;
}
int treedp(int x,int fa) {
	f[x][0]=pw2[ent[x]];
	f[x][1]=pw2[ent[x]]*ll(pw2[cnt[x]]-1)%P;
	int sz=ent[x];
	for(int i=ls[x]; i; i=nx[i])
		if(e[i]!=fa) {
			sz+=treedp(e[i],x)+1;
			f[x][1]=((ll)f[x][0]*f[e[i]][1]%P+f[x][1]*ll((2ll*f[e[i]][0]%P+f[e[i]][1])%P)%P)%P;
			f[x][0]=(ll)f[x][0]*2ll%P*f[e[i]][0]%P;
		}
	ans=(ans+(ll)pw2[m-sz-(x>1)]*f[x][1]%P)%P;
	return sz;
}
int main() {
	freopen("barrack.in","r",stdin);
	freopen("barrack.out","w",stdout);
	scanf("%d%d",&n,&m);
	pw2[0]=1;
	for(i=1; i<=n||i<=m; ++i)
		pw2[i]=pw2[i-1]*2ll%P;
	for(i=1; i<=m; ++i) {
		scanf("%d%d",&u[i],&v[i]);
		insert(u[i],v[i]);
		insert(v[i],u[i]);
	}
	dfs(1,-1);
	em=0;
	for(i=1; i<=tot; ++i) ls[i]=0;
	for(i=1; i<=m; ++i)
		if(scc[u[i]]==scc[v[i]])
			++ent[scc[u[i]]];
		else {
			insert(scc[u[i]],scc[v[i]]);
			insert(scc[v[i]],scc[u[i]]);
		}
	treedp(1,-1);
	printf("%d",ans);
	return 0;
}