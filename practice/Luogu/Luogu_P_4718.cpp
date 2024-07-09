#include <cstdio>
#include <random>
#include <chrono>
#include <algorithm>
#include <cmath>
using namespace std;
using ll = long long;
int T;
ll n,maxf;
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
ll randint(ll l,ll r) {
	return uniform_int_distribution<ll>(l,r)(rnd);
}
ll mul(ll a,ll b,ll p) {
	ll c=1.0l*a/p*b;
	return (ll(1ull*a*b-1ull*c*p)+p)%p;
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
		ll x=randint(2,n-1),u=qpow(x,s,n);
		if(u==1) continue;
		{
			int j;
			for(j=0; j<t; ++j) {
				if(u==n-1) break;
				u=mul(u,u,n);
			}
			if(j==t) return false;
		}
	}
	return true;
}
ll gcd(ll a,ll b) {
	return !b?a:gcd(b,a%b);
}
ll pollard_rho(ll n) {
	const ll c = randint(1,n-1);
	const auto f = [&](ll x) -> ll {
		return (mul(x,x,n)+c)%n;
	};
	ll s=0,t=0,v=1;
	for(int j=1; ; j<<=1,t=s,v=1) {
		for(int i=1; i<=j; ++i) {
			s=f(s);
			v=mul(v,abs(s-t),n);
			if(!v) return n;
			if(i%127==0) {
				ll d=gcd(v,n);
				if(d>1) return d;
			}
		}
		ll d=gcd(v,n);
		if(d>1) return d;
	}
	return n;
}
void split(ll x) {
	if(x<=maxf||x<2||miller_rabin(x)) {
		maxf=max(maxf,x);
		return ;
	}
	ll d=x;
	while(d==x) d=pollard_rho(x);
	while(x%d==0) x/=d;
	split(x);
	split(d);
}
int main() {
	scanf("%d",&T);
	while(T--) {
		scanf("%lld",&n);
		maxf=0;
		split(n);
		if(maxf==n) printf("Prime\n");
		else printf("%lld\n",maxf);
	}
	return 0;
}