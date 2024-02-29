#include<cstdio>
#include<set>
using namespace std;
const int N(2e5);
int n,q,a[N + 2],l[N + 2],r[N + 2],p[N + 2];
namespace Segtree {
	const int S((N << 2) + 2);
	int tr[S];
	multiset<int> lzy[S];
#define ls (x<<1)
#define rs (ls|1)
#define li ls,l,mid
#define ri rs,mid+1,r
	void mktree(int x,int l,int r) {
		if(l==r) {
			tr[x]=a[l];
			return ;
		}
		int mid=(l+r)/2;
		mktree(li);
		mktree(ri);
		tr[x]=max(tr[ls],tr[rs]);
	}
	void push(int x,int l,int r,int L,int R,int u) {
		if(r<L||R<l) return ;
		if(L<=l&&r<=R) {
			lzy[x].insert(u);
			tr[x]=max(tr[x],u);
			return ;
		}
		int mid=(l+r)/2;
		push(li,L,R,u);
		push(ri,L,R,u);
		tr[x]=max(tr[ls],tr[rs]);
		if(!lzy[x].empty()) tr[x]=max(tr[x],*lzy[x].rbegin());
	}
	void pop(int x,int l,int r,int L,int R,int u) {
		if(r<L||R<l) return ;
		if(L<=l&&r<=R) {
			lzy[x].erase(u);
			if(l==r) tr[x]=a[l];
			else tr[x]=max(tr[ls],tr[rs]);
			if(!lzy[x].empty()) tr[x]=max(tr[x],*lzy[x].rbegin());
			return ;
		}
		int mid=(l+r)/2;
		pop(li,L,R,u);
		pop(ri,L,R,u);
		tr[x]=max(tr[ls],tr[rs]);
		if(!lzy[x].empty()) tr[x]=max(tr[x],*lzy[x].rbegin());
	}
	int query(int x,int l,int r,int u) {
		if(r<u||u<l) return 0;
		if(l==r) return tr[x];
		int mid=(l+r)/2;
		if(u<=mid) return lzy[x].empty()?query(li,u):max(query(li,u),*lzy[x].rbegin());
		return lzy[x].empty()?query(ri,u):max(query(ri,u),*lzy[x].rbegin());
	}
}
int main() {
	scanf("%d",&n);
	for(int i=1; i<=n; ++i)
		scanf("%d",&a[i]);
	Segtree::mktree(1,1,n);
	scanf("%d",&q);
	for(int i=1; i<=q; ++i) {
		int op,x;
		scanf("%d",&op);
		if(op==1) {
			scanf("%d%d%d",&l[i],&r[i],&p[i]);
			Segtree::push(1,1,n,l[i],r[i],p[i]);
		} else if(op==2) {
			scanf("%d",&x);
			Segtree::pop(1,1,n,l[x],r[x],p[x]);
		} else {
			scanf("%d",&x);
			printf("%d\n",Segtree::query(1,1,n,x));
		}
	}
	return 0;
}