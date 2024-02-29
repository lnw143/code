#include<cstdio>
#include<algorithm>
using namespace std;
const int N = 5e5;
int n,d,i,ans,a[N + 2],f[N + 2];
namespace Segtree {
	int tr[(N << 2) + 2];
#define ls (x<<1)
#define rs (ls|1)
#define li ls,l,mid
#define ri rs,mid+1,r
	void modify(int x,int l,int r,int g,int f) {
		if(r<g||g<l) return ;
		if(l==r) {
			tr[x]=max(tr[x],f);
			return ;
		}
		int mid=(l+r)/2;
		if(g<=mid) modify(li,g,f);
		else modify(ri,g,f);
		tr[x]=max(tr[ls],tr[rs]);
	}
	int query(int x,int l,int r,int L,int R) {
		if(r<L||R<l) return 0;
		if(L<=l&&r<=R) return tr[x];
		int mid=(l+r)/2;
		return max(query(li,L,R),query(ri,L,R));
	}
}
int main() {
	scanf("%d%d",&n,&d);
	for(i=1; i<=n; ++i)
		scanf("%d",&a[i]);
	using namespace Segtree;
	for(i=1; i<=n; ++i) {
		f[i]=query(1,1,5e5,a[i]-d,a[i]+d)+1;
		modify(1,1,5e5,a[i],f[i]);
		ans=max(ans,f[i]);
	}
	printf("%d",ans);
	return 0;
}