#include<cstdio>
#include<algorithm>
using namespace std;
const int N = 2e5, M = N << 5;
using ll = long long;
int n,q,i,a[N + 2],b[N + 2],v[N + 2];
ll ans;
int find_pos(int x) {
	int l=1,r=n,mid;
	while(l<=r) {
		mid=(l+r)/2;
		if(b[mid]<=x) l=mid+1;
		else r=mid-1;
	}
	return l-1;
}
namespace Segtree {
	int tot,rt[N + 2];
	struct Node {
		int ls,rs;
		ll val;
	} tr[M + 2];
#define ls(x) tr[x].ls
#define rs(x) tr[x].rs
#define li(x) ls(x),l,mid
#define ri(x) rs(x),mid+1,r
	int mktree(int x,int l,int r) {
		if(l<r) {
			int mid=(l+r)/2;
			ls(x)=mktree(li(x));
			rs(x)=mktree(ri(x));
		}
		return ++tot;
	}
	int modify(int x,int l,int r,int g) {
		int y=++tot;
		tr[y]=tr[x];
		if(l==r) {
			tr[y].val+=b[g];
			return y;
		}
		int mid=(l+r)/2;
		if(g<=mid) ls(y)=modify(li(x),g);
		else rs(y)=modify(ri(x),g);
		tr[y].val=tr[ls(y)].val+tr[rs(y)].val;
		return y;
	}
	ll query(int x,int y,int l,int r,int g) {
		if(g<l) return 0;
		if(r<=g) return tr[y].val-tr[x].val;
		int mid=(l+r)/2;
		return query(ls(x),ls(y),l,mid,g)+query(rs(x),rs(y),mid+1,r,g);
	}
}
int main() {
	scanf("%d",&n);
	for(i=1; i<=n; ++i)
		scanf("%d",&a[i]),b[i]=a[i];
	stable_sort(b+1,b+n+1);
	using namespace Segtree;
	rt[0]=mktree(1,1,n);
	for(i=1; i<=n; ++i) {
		v[i]=find_pos(a[i]);
		rt[i]=modify(rt[i-1],1,n,v[i]);
	}
	scanf("%d",&q);
	for(i=1; i<=q; ++i) {
		static ll l,r,x;
		scanf("%lld%lld%lld",&l,&r,&x);
		l^=ans,r^=ans,x^=ans;
		x=find_pos(x);
		ans=query(rt[l-1],rt[r],1,n,x);
		printf("%lld\n",ans);
	}
	return 0;
}