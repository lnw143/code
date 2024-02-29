#include<cstdio>
using namespace std;
const int N = 1e5 + 2;
using ll = long long;
int n,a[N * 2],i,j;
ll s,ans,sum[N * 2];
ll f(ll x) {
	return x*2>s?s-x:x;
}
ll max(ll x,ll y) {
	return x<y?y:x;
}
int main() {
	scanf("%d",&n);
	for(i=1; i<=n; ++i)
		scanf("%d",&a[i]),a[i+n]=a[i],s+=a[i];
	for(i=1; i<=2*n; ++i)
		sum[i]=sum[i-1]+a[i];
	for(i=1; i<=n; ++i)
		for(j=i+1; j<=i+n; ++j)
			ans=max(ans,f(sum[j]-sum[i]));
	printf("%lld",ans);
	return 0;
}