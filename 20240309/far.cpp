#include<cstdio>
using namespace std;
using ll = long long;
const int N(4e2);
int n,p,f[N + 2][N + 2];
ll qpow(ll a,ll n) {
	ll x=1;
	for(; n; n>>=1,a=a*a%p) if(n&1) x=x*a%p;
	return x;
}
int main() {
	freopen("far.in","r",stdin);
	freopen("far.out","w",stdout);
	scanf("%d%d",&n,&p);
	f[0][0]=0;
	for(int i=0; i<=n; ++i)
		for(int j=0; j<=i; ++j)
			for(int k=1; i+k<=n; ++k)
				f[i+k][k]=(f[i+k][k]+(f[i][j]+n-i-k)*qpow(qpow(2,j)-1,k)%p*qpow(2,k*(k-1)/2)%p);
	ll ans=0;
	for(int i=1; i<=n; ++i)
		ans=(ans+f[n][i])%p;
	printf("%lld",ans*qpow(n-1,p-2)%p);
	return 0;
}