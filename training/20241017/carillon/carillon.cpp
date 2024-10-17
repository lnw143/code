#include <cstdio>
#include <algorithm>
using namespace std;
using ll = long long;
const int N = 2e7, P = 998244353;
namespace linear_sieve {
	int prm[N + 2],cnt;
	bool bz[N + 2];
	int phi[N + 2];
	void init() {
		phi[1]=1;
		for(int i=2; i<=N; ++i) {
			if(!bz[i]) {
				phi[i]=i-1;
				prm[++cnt]=i;
			}
			for(int j=1; j<=cnt&&prm[j]*i<=N; ++j) {
				bz[prm[j]*i]=true;
				if(i%prm[j]==0) {
					phi[i*prm[j]]=phi[i]*prm[j];
					break;
				}
				phi[i*prm[j]]=phi[i]*(prm[j]-1);
			}
		}
	}
}
int phm[N + 2],pinv[N + 2];
int inv[N + 2];
int g[N + 2],f[N + 2];
int sg[N + 2],sf[N + 2];
ll qpow(ll a,ll n) {
	ll x=1;
	for(; n; n>>=1,a=a*a%P) if(n&1) x=x*a%P;
	return x;
}
void init() {
	using linear_sieve::cnt;
	using linear_sieve::prm;
	using linear_sieve::phi;
	inv[1]=1;
	for(int i=2; i<=N; ++i) inv[i]=ll(P-P/i)*inv[P%i]%P;
	for(int i=1; i<=N; ++i) g[i]=(ll)i*pinv[i]%P,f[i]=(ll)inv[i]*phi[i]%P;
	for(int j=1; j<=cnt; ++j)
		for(int i=N/prm[j]; i>=1; --i) 
			g[i*prm[j]]=(ll)g[i*prm[j]]*f[i]%P,
			f[i*prm[j]]=(ll)f[i*prm[j]]*g[i]%P;
}
int main() {
	freopen("carillon.in","r",stdin);
	freopen("carillon.out","w",stdout);
	linear_sieve::init();
	using linear_sieve::phi;
	phm[0]=1;
	for(int i=1; i<=N; ++i) phm[i]=(ll)phm[i-1]*phi[i]%P;
	ll fac=qpow(phm[N],P-2);
	for(int i=N; i>=1; --i) {
		pinv[i]=fac*phm[i-1]%P;
		fac=fac*phi[i]%P;
	}
	init();
	sf[0]=sg[0]=1;
	for(int i=1; i<=N; ++i) 
		sf[i]=(ll)sf[i-1]*f[i]%P,
		sg[i]=(ll)sg[i-1]*g[i]%P;
	int T;
	scanf("%d",&T);
	while(T--) {
		int n,m;
		scanf("%d%d",&n,&m);
		if(n>m) swap(n,m);
		ll ans=1;
		for(int i=1; i<=n; ) {
			int j=min(n/(n/i),m/(m/i));
			ans=ans*qpow((ll)sg[j]*sf[i-1]%P,ll(n/i)*(m/i))%P;
			i=j+1;
		}
		printf("%lld\n",ans*qpow(phm[n],m)%P*qpow(phm[m],n)%P);
	}
	return 0;
}