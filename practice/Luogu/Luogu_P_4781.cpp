#include <cstdio>
using namespace std;
using ll = long long;
const int N = 2e3, P = 998244353;
int n,k,x[N + 2],y[N + 2];
ll qpow(ll a,ll n) {
	ll x=1;
	for(; n; n>>=1,a=a*a%P) if(n&1) x=x*a%P;
	return x;
}
int main() {
	scanf("%d%d",&n,&k);
	for(int i=1; i<=n; ++i)
		scanf("%d%d",&x[i],&y[i]);
	ll sum=0;
	for(int i=1; i<=n; ++i) {
		ll prod=y[i];
		for(int j=1; j<=n; ++j)
			if(i!=j)
				prod=prod*(k-x[j])%P*qpow(x[i]-x[j],P-2)%P;
		sum=(sum+prod)%P;
	}
	printf("%lld",(sum%P+P)%P);
	return 0;
}