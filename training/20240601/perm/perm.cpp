#include <cstdio>
using namespace std;
const int N = 1e5, N_ = 1e3, P = 1e9 + 7;
using ll = long long;
int n,m,a[N + 2],ans,p[N + 2];
ll f[N_ + 2][N_ + 2];

ll qpow(ll a,ll n) {
	ll x=1;
	for(; n; n>>=1,a=a*a%P) if(n&1) x=x*a%P;
	return x;
}

// persistent segtree
namespace segtree {
	const int S = N << 6;
	int t[S],ls[S],rs[S],tot,rt[N + 2];
#define mid (l+r>>1)
	int build(int l,int r) {
		int u=++tot;
		t[u]=0;
		if(l<r) {
			ls[u]=build(l,mid);
			rs[u]=build(mid+1,r);
		}
		return u;
	}
	void pushup(int u) {
		t[u]=t[ls[u]]+t[rs[u]];
	}
	int modify(int u,int l,int r,int x,int y) {
		int v=++tot;
		ls[v]=ls[u],rs[v]=rs[u];
		if(l==r) {
			t[v]=t[u]+y;
			return v;
		}
		if(x<=mid) ls[v]=modify(ls[v],l,mid,x,y);
		else rs[v]=modify(rs[v],mid+1,r,x,y);
		pushup(v);
		return v;
	}
	int query(int u,int v,int l,int r,int x,int y) {
		if(r<x||y<l) return 0;
		if(x<=l&&r<=y) return t[v]-t[u];
		return query(ls[u],ls[v],l,mid,x,y)+query(rs[u],rs[v],mid+1,r,x,y);
	}
}

int ask(int x,int y) {
	if(x==0) return 0;
	using namespace segtree;
	return query(rt[x],rt[y-1],1,n,1,a[x]-1);
}

int main() {
	freopen("perm.in","r",stdin);
	freopen("perm.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1; i<=n; ++i)
		scanf("%d",&a[i]),p[a[i]]=i;
	using namespace segtree;
	rt[0]=build(1,n);
	for(int i=1; i<=n; ++i)
		rt[i]=modify(rt[i-1],1,n,a[i],1);
	f[0][0]=1;
	for(int i=1; i<=n; ++i) {
		for(int j=1; j<=n; ++j)
			for(int k=0; k<j; ++k)
				if(p[k]<p[j])
					(f[p[j]][i]+=f[p[k]][i-1]*qpow(2,ask(p[k],p[j]))%P)%=P;
	}
	ll ans=0;
	for(int i=1; i<=n; ++i) {
		ll sum=0;
		for(int j=1; j<=n; ++j)
			(sum+=f[j][i])%=P;
		(ans+=sum*qpow(i,m)%P)%=P;
	}
	printf("%lld",ans);
	return 0;
}