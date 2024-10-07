#include <cstdio>
using namespace std;
using ll = long long;
ll phi(ll n) {
	ll res=n;
	for(ll i=2; i*i<=n; ++i)
		if(n%i==0) {
			res-=res/i;
			while(n%i==0) n/=i;
		}
	if(n>1) res-=res/n;
	return res;
}
ll qpow(ll a,ll n,ll p) {
	ll x=1;
	for(; n; n>>=1,a=a*a%p) if(n&1) x=x*a%p;
	return x;
}
ll solve(ll p) {
	if(p==1) return 0;
	int q=phi(p);
	return qpow(2,solve(q)+q,p);
}
int main() {
	int T;
	scanf("%d",&T);
	while(T--) {
		int n;
		scanf("%d",&n);
		printf("%lld\n",solve(n));
	}
	return 0;
}