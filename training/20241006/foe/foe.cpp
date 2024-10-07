#include <cstdio>
using namespace std;
using ll = long long;
using LL = __int128;
ll qpow(ll a,ll n,ll p) {
	ll x=1;
	for(; n; n>>=1,a=a*a%p) if(n&1) x=x*a%p;
	return x;
}
int phi(int n) {
	int res=n;
	for(int i=2; i*i<=n; ++i)
		if(n%i==0) {
			res-=res/i;
			while(n%i==0) n/=i;
		}
	if(n>1)
		res-=res/n;
	return res;
}
int gcd(int x,int y) {
	return !y?x:gcd(y,x%y);
}
LL exgcd(LL a,LL b,LL &x,LL &y) {
	if(!b) {
		x=1,y=0;
		return a;
	}
	LL d=exgcd(b,a%b,y,x);
	y-=a/b*x;
	return d;
}
LL excrt(LL a,LL n,LL b,LL m) {
	LL x,y;
	LL d=exgcd(n,m,x,y);
	if((a-b)%d!=0) return -1;
	LL l=n/d*m;
	LL res=(b-a)/d*x%l*n%l+a;
	return (res%l+l)%l;
}
ll calc(ll a,ll p) {
	if(p==1) return 0;
	ll q=phi(p);
	return qpow(a,calc(a,q)+q,p);
}
void solve() {
	ll a,n;
	scanf("%lld%lld",&a,&n);
	ll m=phi(n);
	ll x=calc(a,m),y=qpow(a,x+m,n);
	printf("%lld\n",(ll)excrt(x,m,y,n)+n/gcd(n,m)*m);
}
int main() {
	freopen("foe.in","r",stdin);
	freopen("foe.out","w",stdout);
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}