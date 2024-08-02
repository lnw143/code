#include <cstdio>
#include <algorithm>
using namespace std;
using ll = long long;
const int N = 2e5, P = 998244353;
int n,q,a[N + 2],ans;
ll pow2[N + 2],ps[N + 2];
namespace segtree {
	ll sum[N << 2];
	int minn[N << 2],maxn[N << 2];
#define mid (l+r>>1)
#define ls (u<<1)
#define rs (ls|1)
#define li ls,l,mid
#define ri rs,mid+1,r
	void build(int u,int l,int r) {
		if(l==r) {
			sum[u]=minn[u]=maxn[u]=a[l];
			return ;
		}
		build(li);
		build(ri);
		sum[u]=sum[ls]+sum[rs];
		minn[u]=min(minn[ls],minn[rs]);
		maxn[u]=max(maxn[ls],maxn[rs]);
	}
	void modify(int u,int l,int r,int x,int y) {
		if(l==r) {
			sum[u]=minn[u]=maxn[u]=y;
			return ;
		}
		if(x<=mid) modify(li,x,y);
		else modify(ri,x,y);
		sum[u]=sum[ls]+sum[rs];
		minn[u]=min(minn[ls],minn[rs]);
		maxn[u]=max(maxn[ls],maxn[rs]);
	}
	void solve(int u,int l,int r,ll &ans,ll &rest) {
		if(minn[u]>rest) {
			(ans+=ps[r]-ps[l-1]+P)%=P;
			return ;
		}
		if(sum[u]<=rest) {
			rest-=sum[u];
			return ;
		}
		if(l==r) {
			(ans+=pow2[l])%=P;
			return ;
		}
		solve(ri,ans,rest);
		solve(li,ans,rest);
		return ;
	}
}
void printAns() {
	using namespace segtree;
	ll ans=0,rest=sum[1]-maxn[1];
	solve(1,1,n,ans,rest);
	printf("%lld\n",ans);
}
int main() {
	freopen("imperishable.in","r",stdin);
	freopen("imperishable.out","w",stdout);
	scanf("%*d%d",&n);
	for(int i=1; i<=n; ++i) scanf("%d",&a[i]);
	pow2[0]=ps[0]=1;
	for(int i=1; i<=n; ++i) pow2[i]=pow2[i-1]*2%P,ps[i]=(ps[i-1]+pow2[i])%P;
	segtree::build(1,1,n);
	scanf("%d",&q);
	printAns();
	for(int i=1; i<=q; ++i) {
		int x,y;
		scanf("%d%d",&x,&y);
		segtree::modify(1,1,n,x,y);
		printAns();
	}
	return 0;
}