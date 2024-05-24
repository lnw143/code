#include <cstdio>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

// fast input
inline char gc() {
	static char buf[1<<16],*l,*r;
	return l==r&&(r=(l=buf)+fread(buf,1,1<<16,stdin),l==r)?-1:*l++;
}
template <class T> void read(T &x) {
	x=0;
	char c=gc();
	while(c<'0'||c>'9') c=gc();
	for(; c>='0'&&c<='9'; c=gc()) x=(x<<1)+(x<<3)+(c^48);
}
template <class T,class ...Args> void read(T &x,Args &...args) {
	read(x);read(args...);
}

using ll = long long;
const int N = 3e5, logN = 20;
int id,n,T,q,fa[N + 2],w[N + 2];
pair<ll,int> ord[N + 2];

// dsu
int par[N + 2];
int find(int u) {
	return u==par[u]?u:par[u]=find(par[u]);
}

// tree dfn
vector<int> e[N + 2];
int dfc,dfn[N + 2],low[N + 2],v[N + 2];
void dfs(int u) {
	dfn[u]=++dfc;
	for(auto v : e[u])
		dfs(v);
	low[u]=dfc;
}

// persistent segtree
namespace segtree {
	const int M = N << 6;
	int tot,ls[M],rs[M],rt[N + 2];
	ll val[M];
#define mid (l+r>>1)
	inline void pushup(int u) {
		val[u]=val[ls[u]]+val[rs[u]];
	}
	int build(int l,int r) {
		int u=++tot;
		val[u]=0;
		if(l==r) return u;
		ls[u]=build(l,mid);
		rs[u]=build(mid+1,r);
		return u;
	}
	int modify(int u,int l,int r,int x,ll y) {
		int v=++tot;
		ls[v]=ls[u],rs[v]=rs[u];
		if(l==r) {
			val[v]=val[u]+y;
			return v;
		}
		if(x<=mid) ls[v]=modify(ls[v],l,mid,x,y);
		else rs[v]=modify(rs[v],mid+1,r,x,y);
		pushup(v);
		return v;
	}
	ll query(int u,int l,int r,int x,int y) {
		if(r<x||y<l) return 0;
		if(x<=l&&r<=y) return val[u];
		return query(ls[u],l,mid,x,y)+query(rs[u],mid+1,r,x,y);
	}
#undef mid
}

int main() {
	freopen("fire.in","r",stdin);
	freopen("fire.out","w",stdout);
	read(id,n,T);
	for(int i=2; i<=n; ++i)
		read(fa[i],w[i]),e[fa[i]].push_back(i);
	dfs(1);
	for(int i=1; i<=n; ++i) par[i]=i;
	using namespace segtree;
	rt[0]=build(1,n);
	for(int i=1; i<n; ++i)
		ord[i]=make_pair(w[i+1],i+1);
	sort(ord+1,ord+n);
	for(int i=1; i<n; ++i) {
		int u=ord[i].second;
		ll sum=query(rt[i-1],1,n,dfn[u],low[u])+w[u];
		rt[i]=modify(rt[i-1],1,n,dfn[fa[u]],sum);
		if(find(fa[u])!=1) rt[i]=modify(rt[i],1,n,dfn[fa[find(fa[u])]],-sum);
		par[u]=find(fa[u]);
	}
	read(q);
	int last=0;
	for(int i=1; i<=q; ++i) {
		int u;
		ll k;
		read(u,k);
		if(T) u^=last,k^=last;
		int p=upper_bound(ord+1,ord+n,make_pair(k,n+1))-ord-1;
		ll ans=query(rt[p],1,n,dfn[u],low[u]);
		printf("%lld\n",ans);
		last=ans&((1<<20)-1);
	}
	return 0;
}