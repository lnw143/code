#include <cstdio>
#include <vector>
#include <algorithm>
#define popcnt __builtin_popcountll
using namespace std;
using ll = long long;
const int N = 5e3, P = 998244353;
int n,m;
ll a[N + 2];
ll f[N + 2][N + 2];
int main() {
	freopen("dif.in","r",stdin);
	freopen("dif.out","w",stdout);
	scanf("%*d%d%d",&n,&m);
	for(int i=1; i<=n; ++i) scanf("%lld",&a[i]);
	sort(a+1,a+n+1,[](ll x,ll y) { return x%m<y%m; });
	f[0][0]=1;
	for(int i=1; i<=n; ++i)
		for(int j=0; j<i; ++j) {
			(f[i][j]+=f[i-1][j]*((a[i]/m)%P)%P)%=P;
			if(j<a[i]%m) (f[i][j+1]+=f[i-1][j]*(a[i]%m-j)%P)%=P;
		}
	ll fac=1,ans=0;
	for(int i=n; i>=0; --i) {
		if(i<n) fac=fac*(m-i)%P;
		(ans+=f[n][i]*fac%P)%=P;
	}
	printf("%lld",ans);
	return 0;
}