#include<cstdio>
using namespace std;
using ll = long long;
const int N = 10;
int n;
ll a[N + 2],b[N + 2],m=1;
ll exgcd(ll a,ll b,ll &x,ll &y) {
	if(!b) {
		x=1,y=0;
		return a;
	}
	ll d=exgcd(b,a%b,y,x);
	y-=a/b*x;
	return d;
}
ll inv(ll a,ll p) {
	ll x,y;
	exgcd(a,p,x,y);
	return (x%p+p)%p;
}
ll mul(ll a,ll b,ll p) {
	ll x=0;
	for(; b; b>>=1,a=(a<<1)%p) if(b&1) x=(x+a)%p;
	return x;
}
int main() {
	scanf("%d",&n);
	for(int i=1; i<=n; ++i) scanf("%lld",&a[i]);
	for(int i=1; i<=n; ++i) scanf("%lld",&b[i]),m*=b[i];
	ll ans=0;
	for(int i=1; i<=n; ++i) {
		ll t=m/b[i];
		ans=(ans+mul(a[i],mul(t,inv(t,b[i]),m),m))%m;
	}
	printf("%lld",ans);
	return 0;
}