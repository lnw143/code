#include<cstdio>
using namespace std;
using ll = long long;
ll b,l,r,i,md;
ll qpow(ll a,ll n) {
	ll x=1;
	do {
		if(n&1) x*=a;
		a=a*a;
	} while(n>>=1);
	return x;
}
int main() {
	scanf("%lld",&b);
	for(i=1; i<=20; ++i)
		if(qpow(i,i)==b) {
			printf("%lld",i);
			return 0;
		}
	printf("-1");
	return 0;
}