#include <cstdio>
using namespace std;
using ll = long long;
const int N = 2e5, M = 1 << 16, P = 998244353, Pi2 = (P + 1) / 2;
int n,k;
ll a[N + 2];
ll qpow(ll a,ll n) {
	ll x=1;
	for(; n; n>>=1,a=a*a%P) if(n&1) x=x*a%P;
	return x;
}
void fwt(ll *a,int n,int type) {
	for(int i=1; i<(1<<n); i<<=1)
		for(int j=0; j<(1<<n); j+=i<<1)
			for(int k=0; k<i; ++k) {
				ll u=a[j+k],v=a[j+k+i];
				a[j+k]=(u+v)%P;
				a[j+k+i]=(u-v)%P;
				if(type==-1) {
					(a[j+k]*=Pi2)%=P;
					(a[j+k+i]*=Pi2)%=P;
				}
			}
}
int main() {
	scanf("%d%d",&n,&k);
	for(int i=1; i<=k; ++i) {
		int x;
		scanf("%d",&x);
		a[x]=1;
	}
	fwt(a,16,1);
	for(int i=0; i<M; ++i)
		if(a[i]==1) a[i]=n;
		else a[i]=(1-qpow(a[i],n+1))*qpow(1-a[i],P-2)%P-1;
	fwt(a,16,-1);
	ll ans=0;
	for(int i=1; i<M; ++i)
		(ans+=a[i])%=P;
	printf("%lld",(ans+P)%P);
	return 0;
}