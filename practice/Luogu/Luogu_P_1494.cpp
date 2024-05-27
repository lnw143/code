#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
using ll = long long;
const int N = 5e4, M = 5e4;
int n,m,B,c[N + 2],cnt[N + 2];
ll now;
struct query { int l,r,id; } q[M + 2];
struct frac { ll q,p; } ans[M + 2];
bool operator<(const query& x,const query& y) {
	if(x.l/B!=y.l/B) return x.l<y.l;
	return ((x.l/B)&1)?x.r<y.r:x.r>y.r;
}
void upd(int x,int sgn) {
	now-=cnt[c[x]]*(cnt[c[x]]-1ll)/2;
	cnt[c[x]]+=sgn;
	now+=cnt[c[x]]*(cnt[c[x]]-1ll)/2;
}
ll gcd(ll x,ll y) {
	return y?gcd(y,x%y):x;
}
int main() {
	scanf("%d%d",&n,&m);
	B=sqrt(n);
	for(int i=1; i<=n; ++i)
		scanf("%d",&c[i]);
	for(int i=1; i<=m; ++i)
		scanf("%d%d",&q[i].l,&q[i].r),q[i].id=i;
	sort(q+1,q+m+1);
	int l=1,r=0;
	for(int i=1; i<=m; ++i) {
		auto [u,v,id]=q[i];
		if(u==v) {
			ans[id]=frac{0,1};
			continue;
		}
		while(l<u) upd(l++,-1);
		while(u<l) upd(--l,1);
		while(r<v) upd(++r,1);
		while(v<r) upd(r--,-1);
		ans[id]=frac{now,(v-u)*(v-u+1ll)/2};
	}
	for(int i=1; i<=m; ++i) {
		auto [p,q]=ans[i];
		const ll k=gcd(p,q);
		printf("%lld/%lld\n",p/k,q/k);
	}
	return 0;
}