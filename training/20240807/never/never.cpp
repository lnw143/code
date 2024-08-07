#include <cstdio>
using namespace std;
using ll = long long;
using ull = unsigned long long;
int T;
ll mul(ll a,ll b,ll p) {
	return (ll(1ull*a*b-ull(1.0l*a/p*b)*p)+p)%p;
}
int main() {
	freopen("never.in","r",stdin);
	freopen("never.out","w",stdout);
	scanf("%d",&T);
	while(T--) {
		ll n,s,t,x,y;
		scanf("%lld%lld%lld%lld%lld",&n,&s,&t,&x,&y);
		if(s<t&&n<=(t-s)/y) {
			printf("%lld\n",s+n*y);
			continue;
		}
		if(s>=t&&n<=(s-t)/x) {
			printf("%lld\n",s-n*x);
			continue;
		}
		printf("%lld\n",((s-(t-x)+mul(n,y,x+y))%(x+y)+x+y)%(x+y)+t-x);
	}
	return 0;
}