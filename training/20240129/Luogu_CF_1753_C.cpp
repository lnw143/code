#include<cstdio>
using namespace std;
using ll = long long;
const int N = 2e5, P = 998244353;
int T,n,a[N + 2],i,k,x,inv[N + 2],ans;
int main() {
	scanf("%d",&T);
	inv[1]=1;
	for(i=2; i<=N; ++i)
		inv[i]=ll(P-P/i)*inv[P%i]%P;
	while(T--) {
		scanf("%d",&n);
		ans=k=x=0;
		for(i=1; i<=n; ++i) {
			scanf("%d",&a[i]);
			if(!a[i]) x+=a[++k];
		}
		for(i=1; i<=x; ++i)
			ans=(ans+(ll)n*(n-1)%P*inv[2]%P*inv[i]%P*inv[i]%P)%P;
		printf("%d\n",ans);
	}
	return 0;
}