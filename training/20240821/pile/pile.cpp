#include <cstdio>
#include <algorithm>
#define popcnt(x) __builtin_popcount(x)
using namespace std;
using ll = long long;
const int N = 1 << 13, P = 998244353;
int n,m,k,a[N + 2],sum,p[N + 2],f[N + 2];
int g[N + 2],prod[N + 2],inv[N + 2],ans;
ll qpow(ll a,ll n) {
	ll x=1;
	for(; n; n>>=1,a=a*a%P) if(n&1) x=x*a%P;
	return x;
}
void add(int x,int v) {
	for(int i=0; i<m; ++i)
		(f[i]+=(popcnt(i&x)&1)?-v:v)%=P;
}
int solve(int t) {
	for(int i=0; i<m; ++i)
		g[i]=(1-f[i])%P;
	prod[0]=g[0];
	for(int i=1; i<m; ++i)
		prod[i]=(ll)prod[i-1]*g[i]%P;
	inv[m-1]=qpow(prod[m-1],P-2);
	for(int i=m-2; i>=0; --i)
		inv[i]=(ll)g[i+1]*inv[i+1]%P;
	g[0]=inv[0];
	for(int i=1; i<m; ++i)
		g[i]=(ll)inv[i]*prod[i-1]%P;
	int sum=0;
	for(int i=0; i<m; ++i)
		(sum+=(popcnt(i&t)&1)?-g[i]:g[i])%=P;
	return (ll)sum*k%P;
}
int main() {
	freopen("pile.in","r",stdin);
	freopen("pile.out","w",stdout);
	scanf("%d",&n);
	m=1<<__lg(n)+1;
	k=qpow(m,P-2);
	for(int i=0; i<=n; ++i)
		scanf("%d",&a[i]),
		sum=(sum+a[i])%P;
	sum=qpow(sum,P-2);
	for(int i=0; i<=n; ++i)
		p[i]=(ll)a[i]*sum%P;
	for(int i=0; i<m; ++i)
		for(int j=0; j<m; ++j)
			(f[i]+=(popcnt(i&j)&1)?-p[j]:p[j])%=P;
	add(0,-p[0]);
	for(int i=1; i<m; ++i) {
		add(i,-p[i]);
		(ans+=solve(i))%=P;
		add(i,p[i]);
	}
	printf("%d",(ll)p[0]*((ans+P)%P)%P);
	return 0;
}