#include <cstdio>
#include <algorithm>
using namespace std;
using ll = long long;
const int N = 2.5e5;
int n,q,p[N + 2],L[N + 2],R[N + 2],ord[N + 2];
int stk[N + 2],s[N + 2],pre[N + 2];
ll sum[N + 2],sum2[N + 2],Ans[N + 2];
namespace segtree {
	const int S = N << 2;
	struct node {
		ll sum,val;
		node operator*(ll x) {
			return {sum*x,val*x};
		}
	} s[S],t[S];
	node operator+(const node& x,const node& y) {
		return {x.sum+y.sum,x.val+y.val};
	}
	node& operator+=(node& x,const node& y) {
		return x.sum+=y.sum,x.val+=y.val,x;
	}
#define mid (l+r>>1)
#define ls (u<<1)
#define rs (ls|1)
#define li ls,l,mid
#define ri rs,mid+1,r
	void pushdown(int u,int l,int r) {
		if(l<r) {
			t[ls]+=t[u];
			s[ls]+=t[u]*(mid-l+1);
			t[rs]+=t[u];
			s[rs]+=t[u]*(r-mid);
		}
		t[u]={0,0};
	}
	void modify(int u,int l,int r,int x,int y,ll k) {
		if(r<x||y<l) return ;
		pushdown(u,l,r);
		if(x<=l&&r<=y) {
			t[u]+=node{1,k};
			s[u]+=node{1,k}*(r-l+1);
			return ;
		}
		modify(li,x,y,k);
		modify(ri,x,y,k);
		s[u]=s[ls]+s[rs];
	}
	node query(int u,int l,int r,int x,int y) {
		if(r<x||y<l) return {0,0};
		pushdown(u,l,r);
		if(x<=l&&r<=y)
			return s[u];
		return query(li,x,y)+query(ri,x,y);
	}
}
int main() {
	freopen("tal.in","r",stdin);
	freopen("tal.out","w",stdout);
	scanf("%d%d%*d",&n,&q);
	for(int i=1; i<=n; ++i) scanf("%d",&p[i]);
	for(int i=1; i<=q; ++i) scanf("%d%d",&L[i],&R[i]),ord[i]=i;
	sort(ord+1,ord+q+1,[](int x,int y) { return R[x]<R[y]; });
	for(int i=n,tp=0; i>=1; --i) {
		while(tp>0&&p[stk[tp]]<p[i]) --tp;
		s[i]=tp>0?s[stk[tp]]+1:1;
		stk[++tp]=i;
	}
	for(int i=1; i<=n; ++i) sum[i]=sum[i-1]+s[i],sum2[i]=sum2[i-1]+ll(i)*s[i];
	for(int i=1,tp=0; i<=n; ++i) {
		while(tp>0&&p[stk[tp]]<p[i]) --tp;
		pre[i]=stk[tp];
		stk[++tp]=i;
	}
	for(int i=1,cur=0; i<=q; ++i) {
		ll &ans=Ans[ord[i]];
		const int& l=L[ord[i]],r=R[ord[i]];
		for(int j=cur+1; j<=r; ++j)
			segtree::modify(1,1,n,pre[j]+1,j,j);
		cur=r;
		ans=sum2[r]-sum2[l-1]-l*(sum[r]-sum[l-1]);
		segtree::node res=segtree::query(1,1,n,l,r);
		ans+=r*res.sum-res.val;
		ans=ans*2+sum[r]-sum[l-1];
	}
	for(int i=1; i<=q; ++i)
		printf("%lld\n",Ans[i]);
	return 0;
}