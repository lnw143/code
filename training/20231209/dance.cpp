#include<cstdio>
using namespace std;
const int N = 1e5 + 2;
using ll = long long;
int n,a[N * 2],i,j;
ll sum,s,ans;
ll max(ll x,ll y) {
	return x<y?y:x;
}
int main() {
	scanf("%d",&n);
	for(i=1; i<=n; ++i)
		scanf("%d",&a[i]),a[i+n]=a[i],sum+=a[i];
	s=a[1];
	for(i=j=1; i<=n; ++i) {
		while(s*2<sum)
			s+=a[++j];
		ans=max(ans,sum-s);
		ans=max(ans,s-a[j]);
		s-=a[i];
	}
	printf("%lld",ans);
	return 0;
}