#include<cstdio>
using namespace std;
using ll = long long;
constexpr int N = 1 << 22, P = 998244353, G = 3, Gi = 332748118;
int n,m,k;
ll a[N],b[N],c[N];
ll qpow(ll a,ll n) {
	ll x=1;
	for(; n; a=a*a%P,n>>=1) if(n&1) x=x*a%P;
	return x;
}
void NTT(ll *a,int n,int g) {
	if(n==1) return ;
	const int m = n>>1;
	ll a0[m],a1[m];
	for(int i=0; i<m; ++i)
		a0[i]=a[i*2],a1[i]=a[i*2+1];
	NTT(a0,m,g);
	NTT(a1,m,g);
	const ll wn = qpow(g,(P-1)/n);
	ll w=1;
	for(int i=0; i<m; ++i,w=w*wn%P) {
		const ll u=a0[i],v=w*a1[i]%P;
		a[i]=(u+v)%P;
		a[i+m]=(u-v)%P;
	}
}
int main() {
	scanf("%d%d",&n,&m);
	for(int i=0; i<=n; ++i)
		scanf("%lld",&a[i]);
	for(int i=0; i<=m; ++i)
		scanf("%lld",&b[i]);
	k=1;
	while(k<=n+m) k<<=1;
	NTT(a,k,G);
	NTT(b,k,G);
	for(int i=0; i<k; ++i)
		a[i]=a[i]*b[i]%P;
	NTT(a,k,Gi);
	ll inv=qpow(k,P-2);
	for(int i=0; i<=n+m; ++i)
		printf("%lld ",(a[i]*inv%P+P)%P);
	return 0;
}