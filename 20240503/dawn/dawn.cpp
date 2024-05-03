#include<cstdio>
#include<vector>
using namespace std;
using ll = long long;
const int N = 1e5, logN = 18, K = 1e2, P = 998244353;
int T,n,q,sz[N + 2][K + 2],dep[N + 2],anc[N + 2][logN];
ll f[N + 2][K + 2];
vector<int> e[N + 2];
void dfs(int u,int p) {
	sz[u][1]=1;
	anc[u][0]=p;
	for(int i=1; i<logN; ++i)
		anc[u][i]=anc[anc[u][i-1]][i-1];
	dep[u]=dep[p]+1;
	for(int i=1; i<=K; ++i)
		f[u][i]=0;
	for(auto v : e[u])
		if(v!=p) {
			dfs(v,u);
			sz[u][1]+=sz[v][1];
			for(int i=1; i<=K; ++i)
				(f[u][i]-=sz[v][i])%=P;
		}
	for(int i=2; i<=K; ++i)
		sz[u][i]=(ll)sz[u][i-1]*sz[u][1]%P;
	for(int i=1; i<=K; ++i)
		(f[u][i]+=sz[u][i])%=P;
}
ll qpow(ll a,ll n) {
	ll x=1;
	for(; n; n>>=1,a=a*a%P) if(n&1) x=x*a%P;
	return x;
}
int main() {
	freopen("dawn.in","r",stdin);
	freopen("dawn.out","w",stdout);
	scanf("%d",&T); 
	while(T--) {
		scanf("%d%d",&n,&q);
		for(int i=1; i<=n; ++i) e[i].clear();
		for(int i=1; i<n; ++i) {
			int x,y;
			scanf("%d%d",&x,&y);
			e[x].push_back(y);
			e[y].push_back(x);
		}
		dep[1]=0;
		dfs(1,1);
		for(int i=1; i<=q; ++i) {
			int k,x,y,t;
			scanf("%d%d%d",&k,&x,&y);
			if(dep[x]>dep[y]) x^=y^=x^=y;
			t=y;
			for(int i=logN-1; ~i; --i)
				if(dep[anc[t][i]]>dep[x])
					t=anc[t][i];
			if(anc[t][0]==x)
				printf("%lld\n",((f[x][k]+sz[t][k]-qpow(n-sz[x][1],k)-sz[x][k]+qpow(n-sz[t][1],k)%P)%P*f[y][k]%P+P)%P);
			else
				printf("%lld\n",((ll)f[x][k]*f[y][k]%P+P)%P);
		}
	}
	return 0;
}