#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
const int N = 1e5, P1 = 39989, P2 = 1e9;
const double eps = 1e-12;
int n,lstans,cnt;
// li-chao segtree
struct line {
	double k,b;
	double f(int x) {
		return k*x+b;
	}
} a[N + 2];
namespace segtree {
	const int M = 4e4;
	int tr[M << 2];
#define mid ((l+r)>>1)
#define ls (u<<1)
#define rs (ls|1)
#define li ls,l,mid
#define ri rs,mid+1,r
	bool cmp(int u,int v,int x) {
		if(!u||!v) return u;
		double p=a[u].f(x),q=a[v].f(x);
		if(abs(p-q)<eps) return u<v;
		return p>q;
	}
	void update(int u,int l,int r,int x) {
		int &y=tr[u];
		if(cmp(x,y,mid)) swap(x,y);
		if(cmp(x,y,l)) update(li,x);
		else if(cmp(x,y,r)) update(ri,x);
	}
	void modify(int u,int l,int r,int x,int y,int id) {
		if(r<x||y<l) return ;
		if(x<=l&&r<=y) {
			update(u,l,r,id);
			return ;
		}
		modify(li,x,y,id);
		modify(ri,x,y,id);
		return ;
	}
	int query(int u,int l,int r,int x) {
		if(l==r) return tr[u];
		int val=x<=mid?query(li,x):query(ri,x);
		if(cmp(tr[u],val,x)) val=tr[u];
		return val;
	}
}
int main() {
	scanf("%d",&n);
	for(int i=1; i<=n; ++i) {
		int op;
		scanf("%d",&op);
		if(op==0) {
			int x;
			scanf("%d",&x);
			x=(x+lstans-1)%P1+1;
			printf("%d\n",lstans=segtree::query(1,1,4e4,x));
		} else {
			int x0,y0,x1,y1;
			scanf("%d%d%d%d",&x0,&y0,&x1,&y1);
			x0=(x0+lstans-1)%P1+1;
			y0=(y0+lstans-1)%P2+1;
			x1=(x1+lstans-1)%P1+1;
			y1=(y1+lstans-1)%P2+1;
			if(x0>x1) swap(x0,x1),swap(y0,y1);
			if(x0==x1)
				a[++cnt]={0,max(y0,y1)};
			else {
				double k=double(y0-y1)/(x0-x1),b=y0-k*x0;
				a[++cnt]={k,b};
			}
			segtree::modify(1,1,4e4,x0,x1,cnt);
		}
	}
	return 0;
}