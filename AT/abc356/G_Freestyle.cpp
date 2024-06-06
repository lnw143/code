#include <cstdio>
#include <algorithm>
using namespace std;
#define fir first
#define sec second
using ll = long long;
using pl = pair<ll,ll>;
using cpl = const pl&;
const int N = 2e5, Q = 2e5;
const double eps = 1e-12;
int n,q,e=1;
pl a[N + 2],v[N + 2];
pl slope(cpl a,cpl b) {
	return {a.sec-b.sec,a.fir-b.fir};
}
pl slcmp(cpl a,cpl b) {
	return a.fir*b.sec-a.sec*b.fir;
}
void solve(ll c,ll d) {
	int l=1,r=m;
	while(l<=r) {
		int mid=(l+r)/2;
		if(v[mid].y*d<=v[mid].x*c) l=mid+1;
		else r=mid-1;
	}
	if(l==1) printf("-1\n");
	else if(l>m) printf("%.18lf\n",1.0*d/v[m].x);
	else {
		int u=l-1;
		if(v[u].x==v[u+1].x) printf("%.18lf\n",1.0*c/d*v[u].x);
		
	}
}
int stk[N + 2],tp;
void make_convex() {
	stk[tp=1]=1;
	for(int i=1; i<=n; ++i) {
		while(tp>1&&slcmp(slope(a[stk[tp-1]],a[stk[tp]]),slope(a[stk[tp]],a[i]))<=0) --tp;
		stk[++tp]=i;
	}
}
int main() {
	scanf("%d",&n);
	for(int i=1; i<=n; ++i) scanf("%lld%lld",&a[i].sec,&a[i].fir);
	sort(a+1,a+n+1);
	make_convex();
	
	scanf("%d",&q);
	for(int i=1; i<=q; ++i) {
		int c,d;
		scanf("%d%d",&c,&d);
		solve(c,d);
	}
	return 0;
}