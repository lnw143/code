#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
const int P = 1e9 + 7, inv6 = (P+1)/6;
using ll = long long;
using ld = long double;
ll l,r;
ll calc(ll x) {
	ll sum1=x*(x+1)/2%P;
	ll sum2=x*(x+1)%P*(2*x+1)%P*inv6%P;
	return ((x+sum1*(r-l+1)%P-sum2)%P+P)%P;
}
ll calc(ll L,ll R) {
	return (calc(R)-calc(L-1)+P)%P;
}
int main() {
	freopen("piano.in","r",stdin);
	freopen("piano.out","w",stdout);
	int T;
	scanf("%d",&T);
	while(T--) {
		scanf("%lld%lld",&l,&r);
		// x^2 + (l-r)x + l <= 0
		ll delta=(l-r)*(l-r)-4*l,ans=0;
		if(delta<0)
			ans=calc(1,r-l+1);
		else {
			ll L=ceill((r-l-sqrtl(delta))/2),R=floorl((r-l+sqrtl(delta))/2)+1;
			R=min(R,r-l+1);
			L=max(L,1ll);
			ans=((calc(1,L-1)+calc(R+1,r-l+1)+1-(2*l+L-1)*L/2%P+(2*r-R+1)*R/2%P)%P+P)%P;
		}
		printf("%lld\n",ans);
	}
	return 0;
}