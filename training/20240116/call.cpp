#include<cstdio>
#include<vector>
using namespace std;
using ll = long long;
const int N = 1e5, P = 998244353;
int n,m,i,j,q,tot,a[N + 2],b[N + 2],t[N + 2],p[N + 2],deg[N + 2],d[N + 2];
ll f[N + 2],mul[N + 2],v[N + 2];
struct Graph {
	vector<int> e[N + 2];
	void insert(int x,int y) {
		e[x].push_back(y);
	}
	void topu() {
		int h=1,t=0;
		for(int i=0; i<=m; ++i)
			for(int u : e[i])
				++deg[u];
		for(int i=0; i<=m; ++i)
			if(deg[i]==0)
				d[++t]=i;
		while(h<=t) {
			int u=d[h++];
			for(int v : e[u])
				if(--deg[v]==0)
					d[++t]=v;
		}
		tot=t;
	}
} G;
ll qpow(ll a,ll n) {
	ll x=1;
	for(; n; n>>=1) {
		if(n&1) x=x*a%P;
		a=a*a%P;
	}
	return x;
}
int main() {
	freopen("call.in","r",stdin);
	freopen("call.out","w",stdout);
	scanf("%d",&n);
	for(i=1; i<=n; ++i)
		scanf("%d",&a[i]);
	scanf("%d",&m);
	for(i=1; i<=m; ++i) {
		scanf("%d",&t[i]);
		mul[i]=1;
		if(t[i]==1)
			scanf("%d%lld",&p[i],&v[i]);
		else if(t[i]==2)
			scanf("%lld",&v[i]),mul[i]=v[i];
		else {
			scanf("%d",&p[i]);
			G.e[i].reserve(p[i]);
			for(j=1; j<=p[i]; ++j) {
				int u;
				scanf("%d",&u);
				G.insert(i,u);
			}
		}
	}
	scanf("%d",&q);
	for(i=1; i<=q; ++i) {
		int f;
		scanf("%d",&f);
		G.insert(0,f);
	}
	G.topu();
#define mu(x,y) (x*=y)%=P
#define ad(x,y) (x+=y)%=P
	mul[0]=f[0]=1;
	for(i=tot; i>=1; --i)
		for(int v : G.e[d[i]])
			mu(mul[d[i]],mul[v]);
	for(i=1; i<=tot; ++i) {
		if(t[d[i]]==1)
			ad(b[p[d[i]]],v[d[i]]*f[d[i]]%P);
		ll s=1;
		for(auto v=G.e[d[i]].rbegin(); v!=G.e[d[i]].rend(); ++v) {
			ad(f[*v],s*f[d[i]]%P);
			mu(s,mul[*v]);
		}
	}
	for(i=1; i<=n; ++i)
		printf("%lld ",(a[i]*mul[0]%P+b[i])%P);
	return 0;
}