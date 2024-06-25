// Problem URL : https://uoj.ac/problem/34, https://qoj.ac/problem/618

#include <cstdio>
#include <algorithm>
using namespace std;
using ll = long long;
const int N = 1 << 21, P = 998244353, G = 3, Gi = 332748118;
int n,m,a[N + 2],b[N + 2],r[N + 2];
ll qpow(ll a,ll n) {
	ll x=1;
	for(; n; n>>=1,a=a*a%P) if(n&1) x=x*a%P;
	return x;
}
void NTT(const int n,int *a,const int type) {
	for(int i=0; i<n; ++i)
		if(i<r[i]) swap(a[i],a[r[i]]);
	for(int i=1; i<n; i<<=1) {
		const ll omg_n = qpow(type>0?G:Gi,(P-1)/(i<<1));
		for(int j=0; j<n; j+=(i<<1)) {
			ll omg=1;
			for(int k=0; k<i; ++k,(omg*=omg_n)%=P) {
				const ll u=a[j+k],v=omg*a[j+k+i]%P;
				a[j+k]=(u+v)%P;
				a[j+k+i]=(u-v+P)%P;
			}
		}
	}
/*
	if(n==1) return ;
	const int m = n >> 1;
	int a0[m],a1[m];
	for(int i=0; i<m; ++i)
		a0[i]=a[i<<1],
		a1[i]=a[(i<<1)|1];
	NTT(m,a0,type);
	NTT(m,a1,type);
	const ll omg_n = qpow(type>0?G:Gi,(P-1)/n);
	ll omg=1;
	for(int i=0; i<m; ++i,omg=omg*omg_n%P) {
		const ll u=a0[i],v=omg*a1[i]%P;
		a[i]=(u+v)%P;
		a[i+m]=(u-v+P)%P;
	}
*/
}
int main() {
	scanf("%d%d",&n,&m);
	for(int i=0; i<=n; ++i) scanf("%d",&a[i]);
	for(int i=0; i<=m; ++i) scanf("%d",&b[i]);
	int k=1,s=0;
	while(k<=n+m) k<<=1,++s;
	for(int i=0; i<k; ++i)
		r[i]=(r[i>>1]>>1)|((i&1)<<(s-1));
	NTT(k,a,1);
	NTT(k,b,1);
	for(int i=0; i<k; ++i)	
		a[i]=(ll)a[i]*b[i]%P;
	NTT(k,a,-1);
	for(int i=0; i<=n+m; ++i)
		printf("%lld ",a[i]*qpow(k,P-2)%P);
	return 0;
}