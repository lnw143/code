#include <cstdio>
#include <algorithm>
using namespace std;
using ll = long long;
const int N = 5e3, P = 1e9 + 7;
int n;
ll m,a[N + 2],ans;
ll qpow(ll a,ll n) {
	ll x=1;
	for(; n; n>>=1,a=a*a%P) if(n&1) x=x*a%P;
	return x;
}
ll le(ll a,ll b) {
	ll c=min(a,b);
	return ((b-c)*a+c*(c+1)/2)%P*qpow(a*b%P,P-2);
}
int main() {
	scanf("%d",&n);
	for(int i=1; i<=n; ++i) scanf("%lld",&a[i]);
	sort(a+1,a+n+1);
	m=a[n];
	for(int i=1; i<=m; ++i) {
		
	}
	printf("%lld\n",ans);
	return 0;
}