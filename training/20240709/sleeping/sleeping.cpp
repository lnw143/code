#include <cstdio>
#include <functional>
#include <algorithm>
#include <random>
#include <chrono>
#include <map>
using namespace std;
using ll = long long;
const int N = 1e5;
int n,q;
ll a[N + 2],s[N + 2];
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
inline ll randint(ll l,ll r) {
	return uniform_int_distribution<ll>(l,r)(rnd);
}
inline ll mul(ll a,ll b,ll p) {
	return (ll(1ull*a*b-1ull*ll(1.0l*a/p*b)*p)+p)%p;
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
		ll x=qpow(randint(2,n-1),s,n);
		if(x==1) continue;
		{
			int j;
			for(j=0; j<t; ++j) {
				if(x==n-1) break;
				x=mul(x,x,n);
			}
			if(j==t) return false;
		}
	}
	return true;
}
ll gcd(ll a,ll b) {
	return b?gcd(b,a%b):a;
}
ll pollard_rho(ll n) {
	const ll c=randint(1,n-1);
	const auto f = [&](ll x) {
		return (mul(x,x,n)+c)%n;
	};
	ll s=0,t=0,v=1;
	for(int j=1; ; j<<=1,v=1,t=s) {
		for(int i=1; i<=j; ++i) {
			s=f(s);
			v=mul(v,abs(s-t),n);
			if(v==0) return n;
			if(i%127==0) {
				ll d=gcd(v,n);
				if(1<d) return d;
			}
		}
		ll d=gcd(v,n);
		if(1<d) return d;
	}
}
map<ll,int> factor,ans;
void split(ll x) {
	if(x<2) return ;
	if(miller_rabin(x)) {
		++factor[x];
		return ;
	}
	ll d=x;
	while(d==x) d=pollard_rho(x);
	split(x/d);
	split(d);
}
vector<ll> fac;
void dfs(map<ll,int>::iterator x,ll s) {
	if(x==factor.end()) {
		fac.push_back(s);
		return ;
	}
	auto y=x;
	++y;
	for(int i=0; i<=x->second; ++i,s*=x->first)
		dfs(y,s);
}
int main() {
	freopen("sleeping.in","r",stdin);
	freopen("sleeping.out","w",stdout);
	scanf("%d",&n);
	for(int i=1; i<=n; ++i)
		scanf("%lld",&a[i]),s[i]=s[i-1]+a[i];
	split(s[n]);
	for(int i=1; i<=n; ++i)
		++ans[gcd(s[i],s[n])];
	dfs(factor.begin(),1);
	sort(fac.begin(),fac.end(),greater<ll>());
	for(auto [p,t] : factor)
		for(auto i : fac)
			if(i%p==0)
				ans[i/p]+=ans[i];
	scanf("%d",&q);
	for(int i=1; i<=q; ++i) {
		ll x;
		scanf("%lld",&x);
		if(s[n]%x!=0) {
			printf("-1\n");
			continue;
		}
		printf("%lld\n",n+s[n]/x-ans[x]*2);
	}
	return 0;
}