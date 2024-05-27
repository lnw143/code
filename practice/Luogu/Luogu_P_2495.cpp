#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
using ll = long long;
const int N(2.5e5), LOG_N(19);
int n,m,anc[N + 2][LOG_N],mn[N + 2][LOG_N],dep[N + 2];
int dfc,dfn[N + 2];
bool bz[N + 2];
template<int M>
struct Tree {
	int em,e[M + 2],ls[N + 2],nx[M + 2],cs[M + 2];
	void insert(int x,int y,int z) {
		e[++em]=y;
		cs[em]=z;
		nx[em]=ls[x];
		ls[x]=em;
	}
	void dfs(int u) {
		dfn[u]=++dfc;
		for(int i=1; i<LOG_N; ++i)
			anc[u][i]=anc[anc[u][i-1]][i-1],mn[u][i]=min(mn[u][i-1],mn[anc[u][i-1]][i-1]);
		for(int i=ls[u]; i; i=nx[i])
			if(e[i]!=anc[u][0]) {
				anc[e[i]][0]=u;
				mn[e[i]][0]=cs[i];
				dep[e[i]]=dep[u]+1;
				dfs(e[i]);
			}
	}
};
Tree<N * 2> g;
Tree<N> vir;
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
int minw(int x,int y) {
	int minn=1e9;
	for(int i=LOG_N-1; i>=0; --i)
		if(dep[anc[x][i]]>=dep[y])
			minn=min(minn,mn[x][i]),x=anc[x][i];
	return minn;
}
ll dp(int u) {
	ll f=0;
	for(int i=vir.ls[u]; i; i=vir.nx[i])
		if(bz[vir.e[i]]) f+=vir.cs[i];
		else f+=min((ll)vir.cs[i],dp(vir.e[i]));
	return f;
}
void solve() {
	static int k,h[N + 2],tp,stk[N + 2];
	scanf("%d",&k);
	for(int i=1; i<=k; ++i)
		scanf("%d",&h[i]),bz[h[i]]=true;
	stable_sort(h+1,h+k+1,[](int x,int y) { return dfn[x]<dfn[y]; });
	stk[tp=1]=1;
	vir.ls[1]=0;
	vir.em=0;
	for(int i=1; i<=k; ++i)
		if(h[i]!=1) {
			int l=lca(stk[tp],h[i]);
			if(l!=stk[tp]) {
				while(tp>1&&dfn[stk[tp-1]]>dfn[l]) {
					vir.insert(stk[tp-1],stk[tp],minw(stk[tp],stk[tp-1]));
					--tp;
				}
				if(l!=stk[tp-1]) {
					vir.ls[l]=0;
					vir.insert(l,stk[tp],minw(stk[tp],l));
					stk[tp]=l;
				} else {
					vir.insert(l,stk[tp],minw(stk[tp],l));
					--tp;
				}
			}
			vir.ls[h[i]]=0;
			stk[++tp]=h[i];
		}
	while(tp>1) {
		vir.insert(stk[tp-1],stk[tp],minw(stk[tp],stk[tp-1]));
		--tp;
	}
	printf("%lld\n",dp(1));
	for(int i=1; i<=k; ++i)
		bz[h[i]]=false;
}
int main() {
	scanf("%d",&n);
	for(int i=1; i<n; ++i) {
		static int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		g.insert(u,v,w);
		g.insert(v,u,w);
	}
	anc[1][0]=1;
	memset(mn,0x7f,sizeof(mn));
	g.dfs(1);
	scanf("%d",&m);
	for(int i=1; i<=m; ++i)
		solve();
	return 0;
}