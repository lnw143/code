#include <cstdio>
#include <algorithm>
using namespace std;
const int N = 2e5, inf = 1 << 30;
int n,q,t[N + 2];
char s[N + 2];
bool a[N + 2];
namespace segtree {
	const int S = N << 2;
	struct node {
		int mn,mx,rg;
	} s[S];
	int tag[S];
	node operator+(const node &x,const node &y) {
		return {min(x.mn,y.mn),max(x.mx,y.mx),max({x.rg,y.rg,y.mx-x.mn})};
	}
#define mid ((l+r)>>1)
#define ls (u<<1)
#define rs (ls|1)
#define li ls,l,mid
#define ri rs,mid+1,r
	void build(int u,int l,int r) {
		if(l==r) {
			s[u]={t[l],t[l],0};
			return ;
		}
		build(li);
		build(ri);
		s[u]=s[ls]+s[rs];
	}
	void modify(int u,int l,int r,int x,int y,int z) {
		if(r<x||y<l) return ;
		if(x<=l&&r<=y) {
			tag[u]+=z;
			s[u].mn+=z;
			s[u].mx+=z;
			return ;
		}
		modify(li,x,y,z);
		modify(ri,x,y,z);
		s[u]=s[ls]+s[rs];
		s[u].mn+=tag[u];
		s[u].mx+=tag[u];
	}
	node query(int u,int l,int r,int x,int y) {
		if(r<x||y<l) return {inf,-inf,-inf};
		if(x<=l&&r<=y) return s[u];
		auto res=query(li,x,y)+query(ri,x,y);
		res.mn+=tag[u];
		res.mx+=tag[u];
		return res;
	}
}
int main() {
	freopen("sessha.in","r",stdin);
	freopen("sessha.out","w",stdout);
	scanf("%d%s",&n,s+1);
	for(int i=1; i<=n; ++i)
		t[i]=t[i-1]+(s[i]=='('?1:-1),a[i]=(s[i]=='(');
	segtree::build(1,0,n);
	scanf("%d",&q);
	for(int i=1; i<=q; ++i) {
		int op;
		scanf("%d",&op);
		if(op==1) {
			int x;
			scanf("%d",&x);
			segtree::modify(1,0,n,x,n,a[x]?-2:2);
			a[x]^=1;
		} else if(op==2) {
			int l,r;
			scanf("%d%d",&l,&r);
			const int s_l=segtree::query(1,0,n,l-1,l-1).mn,
			mn=segtree::query(1,0,n,l-1,r).mn;
			printf("%d\n",s_l-mn);
		} else if(op==3) {
			int l,r;
			scanf("%d%d",&l,&r);
			const int s_l=segtree::query(1,0,n,l-1,l-1).mn,
			mn=segtree::query(1,0,n,l-1,r).mn,
			s_r=segtree::query(1,0,n,r,r).mn,
			rg=segtree::query(1,0,n,l-1,r).rg;
			printf("%d\n",s_l-mn+rg-(s_r-mn));
		}
	}
	return 0;
}