#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;
const int N = 2e5;
const ll inf = 1ll << 60;
int n,m,a[N + 2],v[N + 2];
ll s[N + 2],ans[N + 2];
vector<int> num;
namespace psegtree {
	const int S = N << 6;
	int tot,sum[S],ls[S],rs[S],rt[N + 2];
	ll val[S];
#define mid (l+r>>1)
	int build(int l,int r) {
		int u=++tot;
		sum[u]=val[u]=0;
		if(l<r) {
			ls[u]=build(l,mid);
			rs[u]=build(mid+1,r);
		}
		return u;
	}
	int modify(int u,int l,int r,int x) {
		int v=++tot;
		sum[v]=sum[u],val[v]=val[u];
		ls[v]=ls[u],rs[v]=rs[u];
		if(l==r) {
			++sum[v];
			val[v]+=num[x];
			return v;
		}
		if(x<=mid) ls[v]=modify(ls[v],l,mid,x);
		else rs[v]=modify(rs[v],mid+1,r,x);
		sum[v]=sum[ls[v]]+sum[rs[v]];
		val[v]=val[ls[v]]+val[rs[v]];
		return v;
	}
	ll query(int u,int l,int r,int k) {
		if(sum[u]<=k) return val[u];
		if(l==r) return k*num[l];
		if(sum[rs[u]]<=k) return query(ls[u],l,mid,k-sum[rs[u]])+val[rs[u]];
		return query(rs[u],mid+1,r,k);
	}
#undef mid
}
void solve(int l,int r,int x,int y) {
	if(l>r) return ;
	int mid=(l+r)/2;
	int p=-1;
	ans[mid]=-inf;
	for(int i=x; i<=y; ++i) {
		ll res=s[i]+2*psegtree::query(psegtree::rt[i],1,m,mid);
		if(res>ans[mid]) ans[mid]=res,p=i;
	}
	solve(l,mid-1,x,p);
	solve(mid+1,r,p,y);
}
int main() {
	freopen("flip.in","r",stdin);
	freopen("flip.out","w",stdout);
	scanf("%d",&n);
	for(int i=1; i<=n; ++i) scanf("%d",&a[i]);
	for(int i=1; i<=n; ++i) s[i]=s[i-1]+a[i];
	for(int i=1; i<=n; ++i) {
		v[i]=max(0,-a[i]);
		num.push_back(v[i]);
	}
	sort(num.begin(),num.end());
	num.erase(unique(num.begin(),num.end()),num.end());
	for(int i=1; i<=n; ++i)
		v[i]=lower_bound(num.begin(),num.end(),v[i])-num.begin()+1;
	m=num.size();
	num.insert(num.begin(),0);
	{
		using namespace psegtree;
		rt[0]=build(1,m);
		for(int i=1; i<=n; ++i) rt[i]=modify(rt[i-1],1,m,v[i]);
	}
	solve(0,n,0,n);
	for(int i=0; i<=n; ++i)
		printf("%lld ",ans[i]);
	return 0;
}