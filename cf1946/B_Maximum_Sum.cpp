#include<cstdio>
#include<algorithm>
using namespace std;
using ll = long long;
const int N = 2e5, P = 1e9 + 7;
int T,n,k,a[N + 2];
int main() {
	scanf("%d",&T);
	while(T--) {
		scanf("%d%d",&n,&k);
		for(int i=1; i<=n; ++i)
			scanf("%d",&a[i]);
		ll mn=0,ans=0,sum=0;
		for(int i=1; i<=n; ++i) {
			sum+=a[i];
			mn=min(mn,sum);
			ans=max(ans,sum-mn);
		}
		sum-=ans;
		ans%=P;
		for(int i=1; i<=k; ++i)
			ans=ans*2%P;
		ans+=sum;
		printf("%lld\n",(ans%P+P)%P);
	}
	return 0;
}