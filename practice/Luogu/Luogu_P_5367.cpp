#include<cstdio>
using namespace std;
using ll = long long;
const int N = 1e6, P = 998244353;
int n,a[N + 2];
ll fac[N + 2];
namespace fenwick {
	int t[N + 2];
	void add(int x) {
		while(x<=n) {
			++t[x];
			x+=x&-x;
		}
	}
	int ask(int x) {
		int r=0;
		while(x>0) {
			r+=t[x];
			x&=x-1;
		}
		return r;
	}
}
int main() {
	scanf("%d",&n);
	for(int i=1; i<=n; ++i)
		scanf("%d",&a[i]);
	fac[0]=1;
	for(int i=1; i<=n; ++i)
		fac[i]=fac[i-1]*i%P;
	ll ans=1;
	for(int i=n; i>=1; --i) {
		using namespace fenwick;
		(ans+=fac[n-i]*ask(a[i])%P)%=P;
		add(a[i]);
	}
	printf("%lld",ans);
	return 0;
}