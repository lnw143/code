#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
using ll = long long;
const int N = 2e4, logN = 16, V = 60;
int n,q,anc[logN][N + 2],dep[N + 2];
ll a[N + 2];
vector<int> e[N + 2];
struct LinearBasis {
	ll d[V + 2];
	ll get_max() const {
		ll res=0;
		for(int i=V; i>=0; --i)
			if(!((res>>i)&1))
				res^=d[i];
		return res;
	}
	void insert(ll x) {
		for(int i=V; i>=0; --i)
			if((x>>i)&1) {
				if(d[i]) x^=d[i];
				else return d[i]=x,void();
			}
	}
} f[logN][N + 2];
LinearBasis merge(const LinearBasis& x,const LinearBasis& y) {
	LinearBasis z=x;
	for(int i=0; i<=V; ++i)
		if(y.d[i])
			z.insert(y.d[i]);
	return z;
}
void dfs(int u,int p) {
	dep[u]=dep[p]+1;
	anc[0][u]=p;
	f[0][u].insert(a[u]);
	for(int i=1; i<logN; ++i)
		anc[i][u]=anc[i-1][anc[i-1][u]],
		f[i][u]=merge(f[i-1][u],f[i-1][anc[i-1][u]]);
	for(auto v : e[u])
		if(v!=p)
			dfs(v,u);
}
LinearBasis query(int u,int v) {
	if(dep[u]<dep[v]) swap(u,v);
	LinearBasis res;
	memset(res.d,0,sizeof(res.d));
	for(int i=logN-1; i>=0; --i)
		if(dep[anc[i][u]]>=dep[v])
			res=merge(res,f[i][u]),
			u=anc[i][u];
	if(u==v) return res.insert(a[u]),res;
	for(int i=logN-1; i>=0; --i)
		if(anc[i][u]!=anc[i][v])
			res=merge(res,f[i][u]),
			res=merge(res,f[i][v]),
			u=anc[i][u],
			v=anc[i][v];
	return merge(merge(res,f[1][u]),f[1][v]);
}
int main() {
	scanf("%d%d",&n,&q);
	for(int i=1; i<=n; ++i)
		scanf("%lld",&a[i]);
	for(int i=1; i<n; ++i) {
		int u,v;
		scanf("%d%d",&u,&v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs(1,1);
	for(int i=1; i<=q; ++i) {
		int u,v;
		scanf("%d%d",&u,&v);
		printf("%lld\n",query(u,v).get_max());
	}
	return 0;
}