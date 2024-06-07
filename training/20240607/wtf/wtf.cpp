#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
using ll = long long;
const int N = 3e3;
const ll inf = 1ll << 60;
int n,m,a[N + 2],g[N + 5][N + 2];
ll f[N + 5][N + 2];
void dfs(int x,int y) {
	if(!x) return ;
	dfs(x-1,g[x][y]);
	printf("%d ",y+1);
}
int main() {
	scanf("%d%d",&n,&m);
	m=n-m;
	for(int i=0; i<n; ++i) scanf("%d",&a[i]);
	memset(f,0x80,sizeof(f));
	for(int i=0; i<=n-2; ++i) f[1][i]=0;
	for(int i=1; i<=n; ++i) {
		const int o = (i-1)*m;
		ll k=-inf,t=-1;
		for(int j=0; j<=n-2; ++j) {
			if(a[(j+o)%n]+f[i][j]>k) {
				k=a[(j+o)%n]+f[i][j];
				t=j;
			}
			if(k-a[(j+o+1)%n]>f[i+1][j]) {
				f[i+1][j]=k-a[(j+o+1)%n];
				g[i+1][j]=t;
			}
		}
		k=-inf,t=-1;
		for(int j=n-2; j>=0; --j) {
			if(-a[(j+o+1)%n]+f[i][j]>k) {
				k=-a[(j+o+1)%n]+f[i][j];
				t=j;
			}
			if(k+a[(j+o)%n]>f[i+1][j]) {
				f[i+1][j]=k+a[(j+o)%n];
				g[i+1][j]=t;
			}
		}
	}
	ll ans=-inf,u=-1;
	for(int i=0; i<=n-2; ++i)
		if(f[n+1][i]>ans) {
			ans=f[n+1][i];
			u=i;
		}
	printf("%lld\n",ans);
	dfs(n+1,u);
	return 0;
}