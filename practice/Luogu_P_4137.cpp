#include<cstdio>
#include<algorithm>
using namespace std;
const int N(2e5);
int n,m,a,rt[N + 2];
namespace segtree {
	const int S(N << 5);
	int tot,tr[S],ls[S],rs[S];
#define mid ((l+r)>>1)
	int maketree(int l,int r) {
		int x=++tot;
		if(l==r) return x;
		ls[x]=maketree(l,mid);
		rs[x]=maketree(mid+1,r);
		return x;
	}
	int modify(int u,int l,int r,int x,int f) {
		int v=++tot;
		if(l==r) return tr[v]=f,v;
		ls[v]=ls[u];
		rs[v]=rs[u];
		if(x<=mid) ls[v]=modify(ls[v],l,mid,x,f);
		else rs[v]=modify(rs[v],mid+1,r,x,f);
		tr[v]=min(tr[ls[v]],tr[rs[v]]);
		return v;
	}
	int query(int x,int l,int r,int L) {
		if(tr[x]>=L) return -1;
		if(l==r) return l;
		int t=query(ls[x],l,mid,L);
		if(~t) return t;
		return query(rs[x],mid+1,r,L);
	}
}
int main() {
	using namespace segtree;
	scanf("%d%d",&n,&m);
	rt[0]=maketree(0,n);
	for(int i=1; i<=n; ++i) {
		scanf("%d",&a);
		a=min(a,n);
		rt[i]=modify(rt[i-1],0,n,a,i);
	}
	for(int i=1; i<=m; ++i) {
		int l,r;
		scanf("%d%d",&l,&r);
		printf("%d\n",query(rt[r],0,n,l));
	}
	return 0;
}