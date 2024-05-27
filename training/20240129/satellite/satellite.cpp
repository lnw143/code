#include<cstdio>
using namespace std;
using ll = long long;
const int N = 2e3;
int n,q,w,h,P,a,b,i,j;
ll abs(ll x) {
	return x<0?-x:x;
}
ll qpow(ll a,ll n) {
	ll x=1;
	for(; n; n>>=1) {
		if(n&1) x=x*a%P;
		a=a*a%P;
	}
	return x;
}
struct Node {
	int h,x,y;
	void read() {
		scanf("%d%d%d",&h,&x,&y);
	}
	ll dis(int x_,int y_) {
		return h*qpow(a,abs(x-x_))%P*qpow(b,abs(y-y_));
	}
} s[N + 2];
int main() {
	freopen("satellite.in","r",stdin);
	freopen("satellite.out","w",stdout);
	scanf("%d%d%d%d%d%d%d",&n,&q,&w,&h,&P,&a,&b);
	for(i=1; i<=n; ++i)
		s[i].read();
	for(i=1; i<=q; ++i) {
		int x,y;
		scanf("%d%d",&x,&y);
		ll ans=0;
		for(j=1; j<=n; ++j)
			ans=(ans+s[j].dis(x,y))%P;
		printf("%lld\n",ans);
	}
	return 0;
}