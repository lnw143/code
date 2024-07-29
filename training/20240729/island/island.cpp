#include <cstdio>
#include <algorithm>
using namespace std;
const int N = 1e5;
int n,m,a[N + 2];
namespace segtree {
	int s[N << 2],t[N << 2];
#define mid (l+r>>1)
#define ls (u<<1)
#define rs (ls|1)
#define li ls,l,mid
#define ri rs,mid+1,r
	void build(int u,int l,int r) {
		s[u]=r;
		if(l==r) return ;
		build(li);
		build(ri);
	}
	void modify(int u,int l,int r,int x,int y,int f) {
		if(r<x||y<l) return ;
		if(x<=l&&r<=y) {
			t[u]+=f;
			s[u]=t[u]?0:l==r?r:max(s[ls],s[rs]);
			return ;
		}
		modify(li,x,y,f);
		modify(ri,x,y,f);
		s[u]=t[u]?0:max(s[ls],s[rs]);
	}
	int query(int u,int l,int r,int x,int y) {
		if(r<x||y<l||t[u]) return 0;
		if(x<=l&&r<=y) return s[u];
		return max(query(li,x,y),query(ri,x,y));
	}
#undef mid
#undef ls
#undef rs
#undef li
#undef ri
}
int main() {
	freopen("island.in","r",stdin);
	freopen("island.out","w",stdout);
	scanf("%d%d",&n,&m);
	segtree::build(1,1,n);
	for(int i=1; i<=n; ++i) {
		scanf("%d",&a[i]);
		a[i]=min(a[i],i);
		segtree::modify(1,1,n,a[i]+1,i,1);
	}
	for(int i=1; i<=m; ++i) {
		int op;
		scanf("%d",&op);
		if(op==1) {
			int x,y;
			scanf("%d%d",&x,&y);
			y=min(y,x);
			segtree::modify(1,1,n,a[x]+1,x,-1);
			segtree::modify(1,1,n,y+1,x,1);
			a[x]=y;
		} else {
			int x;
			scanf("%d",&x);
			printf("%d\n",segtree::query(1,1,n,1,x));
		}
	}
	return 0;
}