#include <cstdio>
#include <map>
#include <cmath>
using namespace std;
using ll = long long;
int T,k;
ll qpow(ll a,ll b,ll p) {
	ll x=1;
	for(; b; b>>=1,a=a*a%p) if(b&1) x=x*a%p;
	return x;
}
int main() {
	scanf("%d%d",&T,&k);
	while(T--) {
		ll y,z,p;
		scanf("%lld%lld%lld",&y,&z,&p);
		y%=p;
		if(k==1)
			printf("%lld\n",qpow(y,z,p));
		else if(k==2) {
			z%=p;
			if(!y) printf("Orz, I cannot find x!\n");
			else printf("%lld\n",qpow(y,p-2,p)*z%p);
		} else {
			map<ll,ll> mp;
			ll t=ceil(sqrt(p));
			z%=p;
			if(y==0) {
				if(z==0) printf("1\n");
				else printf("Orz, I cannot find x!\n");
				continue;
			}
			for(ll i=0; i<=t; ++i)
				mp[z*qpow(y,i,p)%p]=i;
			bool ok=false;
			for(ll i=0; i<=t; ++i)
				if(mp.count(qpow(y,i*t,p))) {
					printf("%lld\n",(i*t-mp[qpow(y,i*t,p)]+p-1)%(p-1));
					ok=true;
					break;
				}
			if(!ok) printf("Orz, I cannot find x!\n");
		}
	}
	return 0;
}