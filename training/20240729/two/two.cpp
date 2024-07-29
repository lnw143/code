#include <cstdio>
using namespace std;
using ll = long long;
const int N = 3e2;
int n,P;
ll f[N + 2],g[N + 2][N + 2],pow2[N * (N + 1) + 2];
int main() {
	freopen("two.in","r",stdin);
	freopen("two.out","w",stdout);
	scanf("%d%d",&n,&P);
	pow2[0]=1;
	for(int i=1; i<=n*(n+1)/2; ++i)
		pow2[i]=pow2[i-1]*2%P;
	g[0][0]=1;
	for(int i=0; i<=n; ++i)
		for(int j=1; j<=i; ++j)
			for(int k=1; k<=i; ++k)
				(g[i][j]+=g[i-k][j-1]*pow2[(k-1)*(k-2)/2]%P)%=P;
	f[1]=2;
	for(int i=2; i<=n; ++i) {
		ll sum=0;
		for(int j=1; j<i; ++j)
			(sum+=f[j]*g[i][j]%P)%=P;
		f[i]=(pow2[i*(i+1)/2]-sum+P)%P;
	}
	printf("%lld",f[n]);
	return 0;
}