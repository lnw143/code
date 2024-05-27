#include <cstdio>
#include <map>
#include <cmath>
using namespace std;
using ll = long long;
ll p,b,n,t;
map<ll,ll> mp;
ll qpow(ll a,ll b,ll p) {
	ll x=1;
	for(; b; b>>=1,a=a*a%p) if(b&1) x=x*a%p;
	return x;
}
int main() {
	scanf("%lld%lld%lld",&p,&b,&n);
	t=ceil(sqrt(p));
	for(ll i=0; i<=t; ++i)
		mp[n*qpow(b,i,p)%p]=i;
	for(ll i=0; i<=t; ++i)
		if(mp.count(qpow(b,i*t,p))) {
			printf("%lld",(i*t-mp[qpow(b,i*t,p)]+p-1)%(p-1));
			return 0;
		}
	printf("no solution");
	return 0;
}