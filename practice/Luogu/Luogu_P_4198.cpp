#include <cstdio>
#include <algorithm>
using namespace std;
using ll = long long;
const int N = 1e5;
int n,m;
namespace rsegtree {
	const int S = N << 2;
	struct frac {
		ll p,q;
		frac(ll p=0,ll q=1):p(p),q(q) {}
	} maxn[S + 2];
	bool operator<(const frac& x,const frac& y) {
		return x.p*y.q<y.p*x.q;
	}
	int cnt[S + 2];
#define mid (l+r>>1)
#define ls (u<<1)
#define rs (ls|1)
#define li ls,l,mid
#define ri rs,mid+1,r
	int calc(int u,int l,int r,const frac& x) {
		if(l==r) return x<maxn[u];
		if(x<maxn[ls]) return calc(li,x)+cnt[u];
		return calc(ri,x);
	}
	void pushup(int u,int l,int r) {
		maxn[u]=max(maxn[ls],maxn[rs]);
		cnt[u]=calc(ri,maxn[ls]);
	}
	void modf(int u,int l,int r,int x,int y) {
		if(l==r) {
			maxn[u]={y,x};
			return ;
		}
		if(x<=mid) modf(li,x,y);
		else modf(ri,x,y);
		pushup(u,l,r);
	}
}
int main() {
	scanf("%d%d",&n,&m);
	for(int i=1; i<=m; ++i) {
		int x,y;
		scanf("%d%d",&x,&y);
		rsegtree::modf(1,1,n,x,y);
		printf("%d\n",rsegtree::calc(1,1,n,{0,1}));
	}
	return 0;
}