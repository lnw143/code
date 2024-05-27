#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
const int N = 2e5 + 2, D = 450, P = 998244353;
using ll = long long;
int n,m,k,d,i,j,h;
ll a[N],l[N],r[N],x[N],ans[N],q[N],p[D],ss[D],u,v;
ll qpow(ll x,ll n) {
	ll r=1;
	do {
		if(n&1) r=r*x%P;
		x=x*x%P;
	} while(n>>=1);
	return r;
}
int main() {
	scanf("%d%d",&n,&m);
	k=sqrt(n);
	d=(n+k-1)/k;
	for(i=1; i<=n; ++i)
		scanf("%lld",&a[i]),q[i]=1;
	for(i=1; i<=d; ++i)
		p[i]=1;
	for(i=1; i<=m; ++i)
		scanf("%lld%lld%lld",&l[i],&r[i],&x[i]);
	for(i=m; i>=1; --i) {
		u=qpow(r[i]-l[i]+1,P-2);
		v=(1-u+P)%P;
		for(j=1; j<=d; ++j)
			if(l[i]<=(j-1)*k+1&&min(j*k,n)<=r[i]) {
				(ss[j]+=p[j]*u%P*x[i]%P)%=P;
				(p[j]*=v)%=P;
			} else for(h=max(l[i],(j-1)*k+1ll); h<=j*k&&h<=n&&h<=r[i]; ++h) {
					ans[h]+=p[j]*u%P*q[h]%P*x[i]%P;
					(q[h]*=v)%=P;
				}
	}
	for(i=1; i<=d; ++i)
		for(j=(i-1)*k+1; j<=n&&j<=i*k; ++j)
			printf("%d ",(ans[j]+a[j]*p[i]%P*q[j]%P+ss[i])%P);
	return 0;
}