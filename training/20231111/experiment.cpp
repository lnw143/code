#include<cstdio>
#define ls (x<<1)
#define rs (ls|1)
#define li ls,l,mid
#define ri rs,mid+1,r
using namespace std;
using ll = long long;
const int N = 1e5 + 2;
int n,m,i,lzy[N * 4];
char ch;
ll tr[N * 4],mx[N * 4],l,r;
template<typename T>T min(T a,T b) {
	return a<b?a:b;
}
template<typename T>T max(T a,T b) {
	return a<b?b:a;
}
void downlzy(int x) {
	if(lzy[x]) {
		tr[ls]<<=lzy[x];
		tr[rs]<<=lzy[x];
		mx[ls]<<=lzy[x];
		mx[rs]<<=lzy[x];
		lzy[ls]+=lzy[x];
		lzy[rs]+=lzy[x];
		lzy[x]=0;
	}
}
void mk(int x,int l,int r) {
	if(l==r) {
		tr[x]=1;
		mx[x]=1;
		return ;
	}
	int mid=(l+r)/2;
	mk(li);
	mk(ri);
	tr[x]=tr[ls]+tr[rs];
	mx[x]=max(mx[ls],mx[rs]);
	return ;
}
void cg(int x,int l,int r,ll L,ll R) {
	if(R<1||tr[x]<L) return ;
	if(L<=1&&tr[x]<=R) {
		++lzy[x];
		tr[x]<<=1;
		mx[x]<<=1;
		return ;
	}
	if(l==r) {
		tr[x]+=min(R,tr[x])-max(L,1ll)+1;
		mx[x]=tr[x];
		return ;
	}
	downlzy(x);
	int mid=(l+r)/2,ss=tr[ls];
	cg(li,L,R);
	cg(ri,L-ss,R-ss);
	tr[x]=tr[ls]+tr[rs];
	mx[x]=max(mx[ls],mx[rs]);
	return ;
}
ll ask(int x,int l,int r,ll L,ll R) {
	if(R<1||tr[x]<L) return 0;
	if(L<=1&&tr[x]<=R)
		return mx[x];
	if(l==r)
		return min(R,tr[x])-max(L,1ll)+1;
	downlzy(x);
	int mid=(l+r)/2,ss=tr[ls];
	return max(ask(li,L,R),ask(ri,L-ss,R-ss));
}
int main() {
	freopen("experiment.in","r",stdin);
	freopen("experiment.out","w",stdout);
	scanf("%d%d",&n,&m);
	mk(1,1,n);
	for(i=1; i<=m; ++i) {
		scanf(" %c%lld%lld",&ch,&l,&r);
		if(ch=='Q')
			printf("%lld\n",ask(1,1,n,l,r));
		else
			cg(1,1,n,l,r);
	}
	return 0;
}