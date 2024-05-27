#include<cstdio>
using namespace std;
using ll = long long;
int T;
ll a,b,s;
ll gcd(ll x,ll y) {
	ll r=x%y;
	while(r) {
		x=y,y=r;
		r=x%y;
	}
	return y;
}
int main() {
	scanf("%d",&T);
	while(T--) {
		scanf("%lld%lld",&a,&b);
		s=gcd(a,b);
		a/=s;
		b/=s;
		printf("%lld\n",(a==1?b:a)*b*s);
	}
	return 0;
}