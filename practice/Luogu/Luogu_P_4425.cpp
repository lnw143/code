#include <cstdio>
#include <algorithm>
using namespace std;
const int N = 1e5, M = 1e5, inf = 1 << 30;
int n,m,p,t[N + 2];
namespace rsegtree {
	const int S = N << 2;
	int maxn[S + 2],minn[S + 2];
#define mid (l+r>>1)
#define ls (u<<1)
#define rs (ls|1)
#define li ls,l,mid
#define ri rs,mid+1,r
	int calc(int u,int l,int r,int x) {
		if(l==r) return x<=maxn[u]?x+l:inf;
		if(maxn[rs]>=x) return min(minn[u],calc(ri,x));
		return calc(li,x);
	}
	void pushup(int u,int l,int r) {
		maxn[u]=max(maxn[ls],maxn[rs]);
		minn[u]=calc(li,maxn[rs]);
	}
	void build(int u,int l,int r) {
		if(l==r) return maxn[u]=t[l]-l,void();
		build(li);
		build(ri);
		pushup(u,l,r);
	}
	void modf(int u,int l,int r,int x,int y) {
		if(l==r) return maxn[u]=y-l,void();
		if(x<=mid) modf(li,x,y);
		else modf(ri,x,y);
		pushup(u,l,r);
	}
}
int get_ans() {
	return rsegtree::calc(1,1,n,rsegtree::maxn[1]-n)+n;
}
int main() {
	scanf("%d%d%d",&n,&m,&p);
	for(int i=1; i<=n; ++i) scanf("%d",&t[i]);
	rsegtree::build(1,1,n);
	int last_ans=get_ans();
	printf("%d\n",last_ans);
	for(int i=1; i<=m; ++i) {
		int x,y;
		scanf("%d%d",&x,&y);
		if(p) x^=last_ans,y^=last_ans;
		rsegtree::modf(1,1,n,x,y);
		printf("%d\n",last_ans=get_ans());
	}
	return 0;
}