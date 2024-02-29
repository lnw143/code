#include<cstdio>
using ll = long long;
int T,n;
ll solve(int n) {
	ll ans=0;
	for(ll i=1; i<=n; i=n/(n/i)+1)
		ans+=(n/(n/i)-i+1)*(n/i);
	return ans;
}
int main() {
	scanf("%d",&T);
	while(T--) {
		scanf("%d",&n);
		printf("%lld\n",solve(n));
	}
	return 0;
}