#include<cstdio>
#include<algorithm>
using namespace std;
using ll = long long;
ll d,i,ans=1e18;
ll ABS(ll x) {
	return x<0?-x:x;
}
ll work(ll x) {
	ll l=1,r=x,md=0;
	while(l<=r) {
		md=(l+r)/2;
		if(md*md>x) r=md-1;
		else l=md+1;
	}
	return min(ABS(l*l-x),ABS((l-1)*(l-1)-x));
}
int main() {
	scanf("%lld",&d);
	ans=d;
	for(i=1; i*i<=d; ++i)
		ans=min(ans,work(d-i*i));
	printf("%lld",ans);
	return 0;
}