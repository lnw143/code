#include<cstdio>
#include<algorithm>
#define ls (x<<1)
#define rs (ls|1)
#define li ls,l,mid
#define ri rs,mid+1,r
using namespace std;
const int N = 2e5 + 2;
struct Apple {
	int x,y;
	void read() {
		scanf("%d%d",&x,&y);
	}
	bool operator<(const Apple t) const {
		if(t.x!=x) return x<t.x;
		return y<t.y;
	}
} a[N];
int n,d,w,i,j,tr[N * 4],lzy[N * 4],ans;
void cg(int x,int l,int r,int h,int f) {
	if(r<h||h<l) return ;
	if(l==r) {
		tr[x]+=f;
		return ;
	}
	int mid=(l+r)/2;
	if(h<=mid) cg(li,h,f);
	else cg(ri,h,f);
	tr[x]=tr[ls]+tr[rs];
}
int ask(int x,int l,int r,int L,int R) {
	if(r<L||R<l) return 0;
	if(L<=l&&r<=R) return tr[x];
	int mid=(l+r)/2;
	return ask(li,L,R)+ask(ri,L,R);
}
int main() {
	scanf("%d%d%d",&n,&d,&w);
	for(i=1; i<=n; ++i)
		a[i].read();
	stable_sort(a+1,a+n+1);
	for(i=1; i<=n; ++i) {
		while(j<n&&a[j+1].x<a[i].x+d) {
			++j;
			cg(1,1,2e5,a[j].y,1);
		}
		for(j=max(a[i].y-w+1,1); j<=a[i].y; ++j)
			ans=max(ans,ask(1,1,2e5,j,j+w-1));
		cg(1,1,2e5,a[i].y,-1);
	}
	printf("%d",ans);
	return 0;
}