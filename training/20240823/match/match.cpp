#include <cstdio>
#include <vector>
#include <utility>
using namespace std;
using llu = long long unsigned;
const int N = 2.5e5;
namespace segtree {
	const int S = N << 2;
	llu s[S],suma[S],sumb[S],sumab[S];
	int taga[S],tagb[S],tagab[S];
#define mid (l+r>>1)
#define ls (u<<1)
#define rs (ls|1)
#define li ls,l,mid
#define ri rs,mid+1,r
	void pushdown(int u,int l,int r) {
		if(l<r) {
			if(tagab[u]) {
				tagab[ls]+=tagab[u];
				tagab[rs]+=tagab[u];
				s[ls]+=sumab[ls]*tagab[u];
				s[rs]+=sumab[rs]*tagab[u];
			}
			if(taga[u]) {
				taga[ls]=taga[rs]=taga[u];
				suma[ls]=llu(mid-l+1)*taga[u];
				sumab[ls]=(llu)taga[u]*sumb[ls];
				suma[rs]=llu(r-mid)*taga[u];
				sumab[rs]=(llu)taga[u]*sumb[rs];
			}
			if(tagb[u]) {
				tagb[ls]=tagb[rs]=tagb[u];
				sumb[ls]=llu(mid-l+1)*tagb[u];
				sumab[ls]=(llu)tagb[u]*suma[ls];
				sumb[rs]=llu(r-mid)*tagb[u];
				sumab[rs]=(llu)tagb[u]*suma[rs];
			}
		}
		taga[u]=tagb[u]=tagab[u]=0;
	}
	void pushup(int u) {
		s[u]=s[ls]+s[rs];
		suma[u]=suma[ls]+suma[rs];
		sumb[u]=sumb[ls]+sumb[rs];
		sumab[u]=sumab[ls]+sumab[rs];
	}
	void coverA(int u,int l,int r,int x,int y,int k) {
		pushdown(u,l,r);
		if(x<=l&&r<=y) {
			taga[u]=k;
			suma[u]=(llu)k*(r-l+1);
			sumab[u]=(llu)k*sumb[u];
			pushdown(u,l,r);
			return ;
		}
		if(x<=mid) coverA(li,x,y,k);
		if(mid<y) coverA(ri,x,y,k);
		pushup(u);
	}
	void coverB(int u,int l,int r,int x,int y,int k) {
		pushdown(u,l,r);
		if(x<=l&&r<=y) {
			tagb[u]=k;
			sumb[u]=(llu)k*(r-l+1);
			sumab[u]=(llu)k*suma[u];
			pushdown(u,l,r);
			return ;
		}
		if(x<=mid) coverB(li,x,y,k);
		if(mid<y) coverB(ri,x,y,k);
		pushup(u);
	}
	void add(int u,int l,int r,int x,int y) {
		pushdown(u,l,r);
		if(x<=l&&r<=y) {
			++tagab[u];
			s[u]+=sumab[u];
			pushdown(u,l,r);
			return ;
		}
		if(x<=mid) add(li,x,y);
		if(mid<y) add(ri,x,y);
		pushup(u);
	}
	llu query(int u,int l,int r,int x,int y) {
		pushdown(u,l,r);
		if(x<=l&&r<=y) return s[u];
		if(y<=mid) return query(li,x,y);
		if(mid<x) return query(ri,x,y);
		return query(li,x,y)+query(ri,x,y);
	}
}
int n,q,a[N + 2],b[N + 2],stk[N + 2];
int prea[N + 2],preb[N + 2];
vector<pair<int,int>> que[N + 2];
llu ans[N + 2];
int main() {
	freopen("match.in","r",stdin);
	freopen("match.out","w",stdout);
	scanf("%*d%d",&n);
	for(int i=1; i<=n; ++i) scanf("%d",&a[i]);
	for(int i=1; i<=n; ++i) scanf("%d",&b[i]);
	for(int i=1,tp=0; i<=n; ++i) {
		while(tp&&a[stk[tp]]<a[i]) --tp;
		prea[i]=stk[tp];
		stk[++tp]=i;
	}
	for(int i=1,tp=0; i<=n; ++i) {
		while(tp&&b[stk[tp]]<b[i]) --tp;
		preb[i]=stk[tp];
		stk[++tp]=i;
	}
	scanf("%d",&q);
	for(int i=1; i<=q; ++i) {
		int l,r;
		scanf("%d%d",&l,&r);
		que[r].emplace_back(l,i);
	}
	for(int i=1; i<=n; ++i) {
		segtree::coverA(1,1,n,prea[i]+1,i,a[i]);
		segtree::coverB(1,1,n,preb[i]+1,i,b[i]);
		segtree::add(1,1,n,1,i);
		for(auto [j,id] : que[i])
			ans[id]=segtree::query(1,1,n,j,i);
	}
	for(int i=1; i<=q; ++i)
		printf("%llu\n",ans[i]);
	return 0;
}