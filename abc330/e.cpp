#include<cstdio>
#define ls (x<<1)
#define rs (ls|1)
#define li ls,l,mid
#define ri rs,mid+1,r
using namespace std;
const int N = 2e5 + 2;
int n,q,a[N],s[N],tr[N * 4],x,y,i;
void cg(int x,int l,int r,int h,int f) {
	if(r<h||h<l) return ;
	if(l==r) {
		s[h]+=f;
		tr[x]=s[h]?-1:h;
		return ;
	}
	int mid=(l+r)/2;
	if(h<=mid) cg(li,h,f);
	else cg(ri,h,f);
	tr[x]=~tr[ls]?tr[ls]:tr[rs];
	return ;
}
void mk(int x,int l,int r) {
	tr[x]=l;
	if(l==r) return ;
	int mid=(l+r)/2;
	mk(li);
	mk(ri);
	return ;
}
int main() {
	scanf("%d%d",&n,&q);
	mk(1,0,n);
	for(i=1; i<=n; ++i) {
		scanf("%d",&a[i]);
		if(a[i]<=n) cg(1,0,n,a[i],1);
	}
	for(i=1; i<=q; ++i) {
		scanf("%d%d",&x,&y);
		if(a[x]<=n) cg(1,0,n,a[x],-1);
		if(y<=n) cg(1,0,n,y,1);
		a[x]=y;
		printf("%d\n",tr[1]);
	}
	return 0;
}