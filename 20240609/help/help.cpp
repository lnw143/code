#include <cstdio>
#include <algorithm>
using namespace std;
const int P = 998244353;
using ll = long long;
ll gcd(ll x,ll y) {
	return y?gcd(y,x%y):x;
}
ll qpow(ll a,ll n) {
	ll x=1;
	for(; n; n>>=1,a=a*a%P) if(n&1) x=x*a%P;
	return x;
}
const int N = 1e5;
int n,m,T,t[N + 2],s[N + 2],f[N + 2];
ll ans=1;
int solve(int x,int y) {
	
}
int main() {
	scanf("%d%d",&n,&m);
	if(n>m) swap(n,m);
	for(int i=1; i<=n; ++i) t[i]=solve(n/i,m/i);
	for(int i=1; i<=n; ++i) s[i]=(s[i-1]+t[i])%P;
	for(int i=1; i<=n; ++i)	{
		scanf("%d",&f[i]);
		(ans*=qpow(f[i],t[i]))%=P;
	}
	printf("%lld\n",ans);
	scanf("%d",&T);
	while(T--) {
		int l,r,u;
		scanf("%d%d%d",&l,&r,&u);
		printf("%lld\n",(ans*=qpow(u,s[r]-s[l-1])%P)%=P);
	}
	return 0;
}