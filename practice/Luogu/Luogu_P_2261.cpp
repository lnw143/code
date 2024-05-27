#include<cstdio>
using namespace std;
using ll = long long;
ll n,k,ans;
ll sum(ll l,ll r) {
	return (r+l)*(r-l+1)/2;
}
int main() {
	scanf("%lld%lld",&n,&k);
	for(ll i=1; i<=k; i=k/(k/i)+1)
		ans+=(k/i)*sum(i,k/(k/i));
	for(ll i=n+1; i<=k; i=k/(k/i)+1)
		ans-=(k/i)*sum(i,k/(k/i));
	printf("%lld",k*n-ans);
	return 0;
}