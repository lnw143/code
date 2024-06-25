#include <cstdio>
#include <algorithm>
using namespace std;
using ll = long long;
const int N = 1 << 21, P = 998244353, G = 3, Gi = 332748118;
int n,a[N + 2],b[N + 2],c[N + 2],r[N + 2];
ll qpow(ll a,ll n) {
	ll x=1;
	for(; n; n>>=1,a=a*a%P) if(n&1) x=x*a%P;
	return x;
}
void NTT(const int n,int *a,const int t) {
	for(int i=0; i<n; ++i)
		if(i<r[i])
			swap(a[i],a[r[i]]);
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
}
void poly_inv(const int *a,int *b,const int n) {
	if(n==1) {
		b[0]=qpow(a[0],P-2);
		return ;
	}
	poly_inv(a,b,(n+1)>>1);
	int m=1,s=0;
	while(m<(n<<1)) m<<=1,++s;
	for(int i=0; i<m; ++i)
		r[i]=(r[i>>1]>>1)|((i&1)<<(s-1));
	for(int i=0; i<m; ++i) c[i]=i<n?a[i]:0;
	NTT(m,b,1);
	NTT(m,c,1);
	for(int i=0; i<m; ++i) b[i]=(2ll*b[i]%P-(ll)c[i]*b[i]%P*b[i]%P+P)%P;
	NTT(m,b,-1);
	for(int i=0; i<m; ++i) b[i]=i<n?b[i]*qpow(m,P-2)%P:0;
}
int main() {
	scanf("%d",&n);
	for(int i=0; i<n; ++i)	
		scanf("%d",&a[i]);
	b[0]=qpow(a[0],P-2);
	poly_inv(a,b,n);
	for(int i=0; i<n; ++i)
		printf("%d ",b[i]);
	return 0;
}