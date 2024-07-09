#include <cstdio>
#include <map>
using namespace std;
using ll = long long;
const int N = 1e5;
int n,q;
ll a[N + 2],s[N + 2];
inline ll mul(ll a,ll b,ll p) {
	return (ll(1ull*a*b-1ull*ll(1.0l*a/p*b)*p)+p)%p;
}
ll qpow(ll a,ll n,ll p) {
	a%=p;
	ll x=1;
	for(; n; n>>=1,a=mul(a,a,p)) if(n&1) x=mul(x,a,p);
	return x;
}
bool miller_rabin(ll n) {
	if(n<3) return n==2;
	if(n%2==0) return false;
	ll s=n-1,t=0;
	while(s%2==0) s/=2,++t;
	for(int i=0; i<8; ++i) {
		ll x=qpow(randint(2,n-1));
	}
}
int main() {
	freopen("sleeping.in","r",stdin);
	freopen("sleeping.out","w",stdout);
	scanf("%d",&n);
	for(int i=1; i<=n; ++i)
		scanf("%lld",&a[i]),s[i]=s[i-1]+a[i];
	scanf("%d",&q);
	for(int i=1; i<=q; ++i) {
		ll x;
		scanf("%lld",&x);
		if(s[n]%x!=0) {
			printf("-1\n");
			continue;
		}
		printf("%lld\n",n+s[n]/x);
	}
	return 0;
}