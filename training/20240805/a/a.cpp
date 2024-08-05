#include <cstdio>
#include <algorithm>
using namespace std;
using ll = long long;
const int N = 1e6;
int n,x,y;
ll ans,s[N + 2];
ll S(ll l,ll r) {
	return (r-l+1)*(l+r)/2;
}
int main() {
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	scanf("%d%d%d",&n,&x,&y);
	for(int i=1; i<=n; ++i)
		for(int j=1; i*j<=n; ++j)
			if(__gcd(i,j)==1)
				s[i*j]+=abs(i*x-j*y);
	for(int i=1; i<=n; ++i) s[i]+=s[i-1];
	for(int i=1; i<=n; i=n/(n/i)+1)
		ans+=S(i,n/(n/i))*s[n/i];
	printf("%lld",ans);
	return 0;
}