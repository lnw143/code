#include <cstdio>
using namespace std;
using ll = long long;
const int N = 1e6, P = 998244353;
int n;
ll p[N + 2],f[N + 2],a[N + 2],b[N + 2];
ll qpow(ll a,ll n) {
	ll x=1;
	for(; n; n>>=1,a=a*a%P) if(n&1) x=x*a%P;
	return x;
}
int main() {
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	scanf("%d",&n);
	for(int i=0; i<n; ++i)  {
		int x,y;
		scanf("%d%d",&x,&y);
		p[i]=x*qpow(y,P-2)%P;
	}
	f[n]=0;
	a[n]=b[n]=0;
	for(int i=n-1; i>=1; --i) {
		a[i]=(1-p[i])*qpow(1-p[i]*a[i+1]%P,P-2)%P;
		b[i]=(p[i]*b[i+1]%P+1)*qpow(1-p[i]*a[i+1]%P,P-2)%P;
	}
	printf("%lld",((p[0]*b[1]%P+1)*qpow(p[0]*(1-a[1])%P,P-2)%P+P)%P);
	return 0;
}