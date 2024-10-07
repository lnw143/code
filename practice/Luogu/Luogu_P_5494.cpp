#include <cstdio>
using namespace std;
using ll = long long;
const int N = 2e5;
int n,m,cnt=1,a[N + 2],rt[N + 2];
ll s[N + 2];
namespace dsegtree {
	const int S = N << 5;
	int tot,ls[S + 2],rs[S + 2];
	ll sum[S + 2];
#define mid (l+r>>1)
	int build(int l,int r) {
		if(s[r]-s[l-1]==0) return 0;
		int u=++tot;
		if(l==r) {
			sum[u]=a[l];
			return u;
		}
		ls[u]=build(l,mid);
		rs[u]=build(mid+1,r);
		sum[u]=sum[ls[u]]+sum[rs[u]];
		return u;
	}
	int merge(int u,int v,int l,int r) {
		if(!u||!v) return u|v;
		if(l==r) {
			sum[u]+=sum[v];
			return u;
		}
		ls[u]=merge(ls[u],ls[v],l,mid);
		rs[u]=merge(rs[u],rs[v],mid+1,r);
		sum[u]=sum[ls[u]]+sum[rs[u]];
		return u;
	}
	void split(int &u,int &v,int l,int r,int x,int y) {
		if(r<x||y<l||!u) return ;
		if(x<=l&&r<=y) return v=u,u=0,void();
		if(!v) v=++tot;
		split(ls[u],ls[v],l,mid,x,y);
		split(rs[u],rs[v],mid+1,r,x,y);
		sum[u]=sum[ls[u]]+sum[rs[u]];
		sum[v]=sum[ls[v]]+sum[rs[v]];
	}
	void modf(int &u,int l,int r,int x,ll k) {
		if(!u) u=++tot;
		if(l==r) {
			sum[u]+=k;
			return ;
		}
		if(x<=mid) modf(ls[u],l,mid,x,k);
		else modf(rs[u],mid+1,r,x,k);
		sum[u]=sum[ls[u]]+sum[rs[u]];
	}
	ll qry(int u,int l,int r,int x,int y) {
		if(!u||r<x||y<l) return 0;
		if(x<=l&&r<=y) return sum[u];
		if(y<=mid) return qry(ls[u],l,mid,x,y);
		if(mid<x) return qry(rs[u],mid+1,r,x,y);
		return qry(ls[u],l,mid,x,y)+qry(rs[u],mid+1,r,x,y);
	}
	int rnk(int u,int l,int r,ll k) {
		if(!u||sum[u]<k) return -1;
		if(l==r) return l;
		return k<=sum[ls[u]]?rnk(ls[u],l,mid,k):rnk(rs[u],mid+1,r,k-sum[ls[u]]);
	}
}
int main() {
	scanf("%d%d",&n,&m);
	for(int i=1; i<=n; ++i)
		scanf("%d",&a[i]),s[i]=s[i-1]+a[i];
	rt[1]=dsegtree::build(1,n);
	for(int i=1; i<=m; ++i) {
		int op;
		scanf("%d",&op);
		if(op==0) {
			int x,l,r;
			scanf("%d%d%d",&x,&l,&r);
			dsegtree::split(rt[x],rt[++cnt],1,n,l,r);
		} else if(op==1) {
			int x,y;
			scanf("%d%d",&x,&y);
			rt[x]=dsegtree::merge(rt[x],rt[y],1,n);
		} else if(op==2) {
			int x,k,q;
			scanf("%d%d%d",&x,&k,&q);
			dsegtree::modf(rt[x],1,n,q,k);
		} else if(op==3) {
			int x,l,r;
			scanf("%d%d%d",&x,&l,&r);
			printf("%lld\n",dsegtree::qry(rt[x],1,n,l,r));
		} else {
			int x;
			ll k;
			scanf("%d%lld",&x,&k);
			printf("%d\n",dsegtree::rnk(rt[x],1,n,k));
		}
	}
	return 0;
}