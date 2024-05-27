#include<cstdio>
#include<vector>
#include<utility>
using namespace std;
using ll = long long;
constexpr int N = 1e5, P = 999911659;
ll n,g,ans,fac[N + 2];
vector<pair<ll,ll>> eq;
ll exgcd(ll a,ll b,ll &x,ll &y) {
	if(!b) {
		x=1,y=0;
		return a;
	}
	ll d=exgcd(b,a%b,y,x);
	y-=a/b*x;
	return d;
}
ll qpow(ll a,ll n,ll p) {
	ll x=1;
	for(; n; a=a*a%p,n>>=1) if(n&1) x=x*a%p;
	return x;
}
ll C(ll n,ll m,ll p) {
	return n<m?0:fac[n]*qpow(fac[m]*fac[n-m]%p,p-2,p)%p;
}
ll Lucas(ll n,ll m,ll p) {
	return !m?1:Lucas(n/p,m/p,p)*C(n%p,m%p,p)%p;
}
ll CRT(const vector<pair<ll,ll>>& eq) {
	auto [m,a]=eq[0];
	for(int i=1; i<eq.size(); ++i) {
		auto [u,v]=eq[i];
		ll x,y,d=exgcd(m,u,x,y);
		m=m/d*u;
		a=((v+y*u%m*(a-v)%m)%m+m)%m;
	}
	return a;
}
void init(ll p) {
	fac[0]=1;
	for(ll i=1; i<p; ++i)
		fac[i]=fac[i-1]*i%p;
}
int main() {
	scanf("%lld%lld",&n,&g);
	for(auto p : {2, 3, 4679, 35617}) {
		init(p);
		ll ans=0;
		for(ll i=1; i*i<=n; ++i)
			if(n%i==0) {
				(ans+=Lucas(n,i,p))%=p;
				if(i*i!=n) (ans+=Lucas(n,n/i,p))%=p;
			}
		eq.emplace_back(p,ans);
	}
	printf("%lld",qpow(g,CRT(eq)+P-1,P));
	return 0;
}