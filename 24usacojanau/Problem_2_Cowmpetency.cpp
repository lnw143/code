#include<cstdio>
#include<algorithm>
using namespace std;
const int N = 100, C = 1e4, P = 1e9 + 7;
using ll = long long;
int n,q,c,i,j,a[N + 2],h[N + 2],f[N + 2][C + 2],g[N + 2][C + 2];
ll qpow(ll a,ll n) {
	ll x=1;
	for(; n; n>>=1,a=a*a%P)
		if(n&1) x=x*a%P;
	return x;
}
int main() {
	scanf("%d%d%d",&q,&n,&c);
	for(i=1; i<=n; ++i)
		scanf("%d%d",&a[i],&h[i]);
	stable_sort(h+1,h+n+1);
	n=unique(h+1,h+n+1)-h-1;
#define ad(x,y) x=((x)+(y))%P
	for(i=1; i<=c; ++i)
		f[1][i]=qpow(i-1,h[1]-1);
	for(i=2; i<=n; ++i) {
		int sum=0;
		for(j=1; j<=c; ++j) {
			ad(f[i][j],sum);
			ad(sum,f[i-1][j]*qpow(j,h[i]-h[i-1]-1));
			printf("%d %d %d\n",i,j,f[i][j]);
		}
	}
	int ans=0;
	for(i=1; i<=c; ++i)
		ad(ans,f[n][i]);
	printf("%d",ans*qpow(c,q-h[n])%P);
	return 0;
}