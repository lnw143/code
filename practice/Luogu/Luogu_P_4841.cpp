#include <cstdio>
#include <algorithm>
using namespace std;
const int N = 1 << 21, P = 1004535809, G = 3, Gi = 334845270, Phi = P - 1;
using ll = long long;
int n;
ll f[N + 2],g[N + 2],h[N + 2];
ll qpow(ll a,ll n) {
	ll x=1;
	for(; n; n>>=1,a=a*a%P) if(n&1) x=x*a%P;
	return x;
}
namespace comb {
	const int N = 1.3e5;
	ll fac[N + 5],inv[N + 5],ifac[N + 5];
	void init(const int n) {
		fac[0]=fac[1]=inv[1]=ifac[0]=ifac[1]=1;
		for(int i=2; i<=n; ++i) {
			fac[i]=fac[i-1]*i%P;
			inv[i]=(P-P/i)*inv[P%i]%P;
			ifac[i]=ifac[i-1]*inv[i]%P;
		}
	}
}
namespace poly {
	int n,rev[N + 2];
	ll c[N + 2];
	void init(int m) {
		int s=0;
		n=1;
		while(n<m) n<<=1,++s;
		for(int i=0; i<n; ++i) rev[i]=(rev[i>>1]>>1)|((i&1)<<(s-1));
	}
	void NTT(int n,ll *a,int t) {
		for(int i=0; i<n; ++i)
			if(i<rev[i])
				swap(a[i],a[rev[i]]);
		for(int i=1; i<n; i<<=1) {
			const ll omg_n = qpow(t>0?G:Gi,(P-1)/(i<<1));
			for(int j=0; j<n; j+=(i<<1)) {
				ll omg=1;
				for(int k=0; k<i; ++k,(omg*=omg_n)%=P) {
					const ll u=a[j+k],v=omg*a[j+k+i]%P;
					a[j+k]=(u+v)%P;
					a[j+k+i]=(u-v+P)%P;
				}
			}
		}
		if(t<0) for(int i=0; i<n; ++i) (a[i]*=qpow(n,P-2))%=P;
	}
	void inv(const int m,const ll *a,ll *b) {
		if(m==1) {
			b[0]=qpow(a[0],P-2);
			return ;
		}
		inv((m+1)>>1,a,b);
		init(m<<1);
		for(int i=0; i<m; ++i) c[i]=a[i];
		for(int i=m; i<n; ++i) c[i]=0;
		NTT(n,c,1);
		NTT(n,b,1);
		for(int i=0; i<n; ++i)
			b[i]=(2*b[i]%P-c[i]*b[i]%P*b[i]%P+P)%P;
		NTT(n,b,-1);
		for(int i=m; i<n; ++i) b[i]=0;
	}
}
int main() {
	scanf("%d",&n);
	comb::init(n);
	int k=1,s=0;
	while(k<=n) k<<=1,++s;
	for(int i=1; i<=n; ++i) f[i]=qpow(2,i*(i-1ll)/2%Phi)*comb::ifac[i-1]%P;
	for(int i=0; i<=n; ++i) g[i]=qpow(2,i*(i-1ll)/2%Phi)*comb::ifac[i]%P;
	poly::inv(n+1,g,h);
	poly::init(n+1);
	const int m = poly::n;
	poly::NTT(m,f,1);
	poly::NTT(m,h,1);
	for(int i=0; i<m; ++i) g[i]=f[i]*h[i]%P;
	poly::NTT(m,g,-1);
	printf("%lld",g[n]*comb::fac[n-1]%P);
	return 0;
}