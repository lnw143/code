#include<cstdio>
#include<algorithm>
#define ls (x<<1)
#define rs (ls|1)
#define li ls,l,mid
#define ri rs,mid+1,r
using namespace std;
const int N = 1e5 + 2;
int n,i,j,a[N],nx[N],stk[N],tr[N * 4],tp,ans;
struct Node {
	int p,v;
	bool operator<(const Node t) const {
		return p<t.p;
	}
} w[N];
void cg(int x,int l,int r,int g) {
	if(r<g||g<l||l>r) return ;
	if(l==r) {
		tr[x]=g;
		return ;
	}
	int mid=(l+r)/2;
	if(g<=mid) cg(li,g);
	else cg(ri,g);
	tr[x]=max(tr[ls],tr[rs]);
	return ;
}
int qr(int x,int l,int r,int L,int R) {
	if(r<L||R<l||l>r) return 0;
	if(L<=l&&r<=R)
		return tr[x];
	int mid=(l+r)/2;
	return max(qr(li,L,R),qr(ri,L,R));
}
int main() {
	scanf("%d",&n);
	for(i=1; i<=n; ++i)
		scanf("%d",&a[i]);
	for(i=n; i>=1; --i) {
		while(tp&&a[stk[tp]]>a[i]) --tp;
		nx[i]=stk[tp]?stk[tp]-1:n;
		if(a[stk[tp]]==a[i]) stk[tp]=i;
		else stk[++tp]=i;
	}
	for(i=1,tp=0; i<=n; ++i) {
		while(tp&&a[stk[tp]]<a[i]) --tp;
		w[i].p=stk[tp]?stk[tp]+1:1;
		w[i].v=i;
		if(a[stk[tp]]==a[i]) stk[tp]=i;
		else stk[++tp]=i;
	}
	stable_sort(w+1,w+n+1);
	for(i=1; i<=n; ++i) {
		for(; w[j].p<=i&&j<=n; ++j)
			cg(1,1,n,w[j].v);
		ans=max(ans,qr(1,1,n,i+1,nx[i])-i+1);
	}
	printf("%d",ans);
	return 0;
}