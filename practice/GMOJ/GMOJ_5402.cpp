#include <cstdio>
#include <algorithm>
using namespace std;
const int N = 2e5, inf = 1 << 30;
int n,p[N + 2],c[N + 2];
int f[N + 2];
namespace rsegtree {
	const int S = N << 2;
	int maxn[S + 2],minn[S + 2];
#define mid (l+r>>1)
#define ls (u<<1)
#define rs (ls|1)
#define li ls,l,mid
#define ri rs,mid+1,r
	int calc(int u,int l,int r,int x) {
		if(l==r) return maxn[u]>x?minn[u]:inf;
		if(x<maxn[rs]) return min(minn[u],calc(ri,x));
		return calc(li,x);
	}
	void pushup(int u,int l,int r) {
		maxn[u]=max(maxn[ls],maxn[rs]);
		minn[u]=calc(li,maxn[rs]);
	}
	void build(int u,int l,int r) {
		maxn[u]=-inf,minn[u]=inf;
		if(l==r) return ;
		build(li);
		build(ri);
	}
	void modf(int u,int l,int r,int x,int y) {
		if(l==r) {
			minn[u]=f[y];
			maxn[u]=y;
			return ;
		}
		if(x<=mid) modf(li,x,y);
		else modf(ri,x,y);
		pushup(u,l,r);
	}
	struct result {
		int minn,maxn;
	} ;
	result query(int u,int l,int r,int x,int y,int suf_max) {
		if(r<x||y<l) return {inf,-inf};
		if(x<=l&&r<=y) return {calc(u,l,r,suf_max),maxn[u]};
		if(y<=mid) return query(li,x,y,suf_max);
		if(mid<x) return query(ri,x,y,suf_max);
		result res=query(ri,x,y,suf_max);
		result res2=query(li,x,y,max(suf_max,res.maxn));
		return {min(res.minn,res2.minn),max(res.maxn,res2.maxn)};
	}
}
int main() {
	freopen("knows.in","r",stdin);
	freopen("knows.out","w",stdout);
	scanf("%d",&n);
	for(int i=1; i<=n; ++i) scanf("%d",&p[i]);
	for(int i=1; i<=n; ++i) scanf("%d",&c[i]);
	rsegtree::build(1,0,n);
	rsegtree::modf(1,0,n,0,0);
	for(int i=1; i<=n; ++i) {
		f[i]=rsegtree::query(1,0,n,0,p[i]-1,-inf).minn+c[i];
		rsegtree::modf(1,0,n,p[i],i);
	}
	int ans=inf;
	for(int i=n,maxn=0; i>=1; --i)
		if(p[i]>maxn) {
			maxn=p[i];
			ans=min(ans,f[i]);
		}
	printf("%d",ans);
	return 0;
}