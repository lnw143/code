#include <cstdio>
#include <vector>
using namespace std;
using ll = long long;
const int N = 2e5;
int n,a[N + 2],p[N + 2],s[N + 2],t[N + 2];
ll ans;
vector<int> e[N + 2];
namespace segtree {
	int sum[N << 2];
	ll val[N << 2],tag[N << 2];
#define mid (l+r>>1)
#define ls (u<<1)
#define rs (ls|1)
#define li ls,l,mid
#define ri rs,mid+1,r
	void pushdown(int u,int l,int r) {
		if(l<r) {
			tag[ls]+=tag[u];
			val[ls]+=tag[u]*sum[ls];
			tag[rs]+=tag[u];
			val[rs]+=tag[u]*sum[rs];
			tag[u]=0;
		}
	}
	void modify(int u,int l,int r,int x) {
		if(r<x||x<l) return ;
		pushdown(u,l,r);
		if(l==r) {
			++sum[u];
			val[u]=sum[u]*tag[u];
			return ;
		}
		if(x<=mid) modify(li,x);
		else modify(ri,x);
		sum[u]=sum[ls]+sum[rs];
		val[u]=val[ls]+val[rs];
	}
	void modify(int u,int l,int r,int x,int y,int f) {
		if(r<x||y<l) return ;
		pushdown(u,l,r);
		if(x<=l&&r<=y) {
			tag[u]+=f;
			val[u]+=f*sum[u];
			pushdown(u,l,r);
			return ;
		}
		modify(li,x,y,f);
		modify(ri,x,y,f);
		val[u]=val[ls]+val[rs];
		sum[u]=sum[ls]+sum[rs];
	}
	ll query(int u,int l,int r,int x,int y) {
		if(r<x||y<l) return 0;
		pushdown(u,l,r);
		if(x<=l&&r<=y) return val[u];
		return query(li,x,y)+query(ri,x,y);
	}
#undef mid
#undef ls
#undef rs
#undef li
#undef ri
}
int main() {
	scanf("%d",&n);
	for(int i=1; i<=n; ++i) scanf("%d",&a[i]);
	for(int i=1; i<=n; ++i) s[i]=p[a[i]],p[a[i]]=i;
	for(int i=1; i<=n; ++i) p[i]=n+1;
	for(int i=n; i>=1; --i) t[i]=p[a[i]],p[a[i]]=i;
	for(int i=1; i<=n; ++i) e[s[i]].push_back(i);
	for(int i=1; i<=n; ++i) p[i]=1;
	for(int i=1; i<=n; ++i)
		if(p[a[i]]) {
			p[a[i]]=0;
			segtree::modify(1,1,n,i+1,t[i]-1,1);
		}
	for(int i=1; i<=n; ++i) {
		for(auto j : e[i-1]) segtree::modify(1,1,n,j);
		segtree::modify(1,1,n,i,t[i]-1,-1);
		if(t[i]<=n) segtree::modify(1,1,n,t[i]+1,t[t[i]]-1,1);
		ans+=segtree::query(1,1,n,i+2,t[i]-1);
	}
	printf("%lld",ans);
	return 0;
}