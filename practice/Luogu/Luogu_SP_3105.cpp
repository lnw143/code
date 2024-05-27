#include <cstdio>
#include <cmath>
#include <map>
using namespace std;
using ll = long long;
ll qpow(ll a,ll b,ll p) {
	ll x=1;
	for(; b; b>>=1,a=a*a%p) if(b&1) x=x*a%p;
	return x;
}
void solve(ll x,ll y,ll p) {
	map<ll,ll> mp;
	ll t=ceil(sqrt(p));
	for(ll i=0; i<=t; ++i)
		mp[y*qpow(x,i,p)%p]=i;
	for(ll i=0; i<=t; ++i)
		if(mp.count(qpow(x,i*t,p))) {
			printf("%lld\n",(i*t-mp[qpow(x,i*t,p)]+p-1)%(p-1));
			return ;
		}
	printf("No Solution\n");
}
int main() {
	ll a,b,c;
	while(scanf("%lld%lld%lld",&a,&b,&c),a||b||c) solve(a,c,b);
	return 0;
}