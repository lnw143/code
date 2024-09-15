#include <cstdio>
#include <vector>
using namespace std;
const int N = 3e2;
using ll = long long;
int n,m,c[N + 2],w[N + 2];
ll d[N + 2][N + 2],f[N + 2][N + 2],g[N + 2][N + 2];
void solve() {
	scanf("%d%d",&n,&m);
	for(int i=1; i<=n; ++i) scanf("%d",&c[i]);
	for(int i=1; i<=n; ++i) scanf("%d",&w[i]);
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=n; ++j)
			d[i][j]=g[i][j]=f[i][j]=i==j?w[i]:1ll<<60;
	for(int i=1; i<=m; ++i) {
		int u,v;
		scanf("%d%d",&u,&v);
		d[u][v]=d[v][u]=w[u]+w[v];
	}
	for(int k=1; k<=n; ++k)
		for(int i=1; i<=n; ++i)
			for(int j=1; j<=n; ++j)
				d[i][j]=min(d[i][j],d[i][k]+d[k][j]-w[k]);
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=n; ++j)
			for(int k=1; k<=n; ++k)
				if(d[j][k]==w[j]+w[k]) {
					if(c[j]==c[k]) g[i][k]=min(g[i][k],d[i][j]+w[k]);
					else f[i][k]=min(f[i][k],d[i][j]+w[k]);
				}
	for(int k=1; k<=n; ++k)
		for(int i=1; i<=n; ++i)
			for(int j=1; j<=n; ++j)
				f[i][j]=min(f[i][j],max(f[i][k],f[k][j]));
	for(int k=1; k<=n; ++k)
		for(int i=1; i<=n; ++i)
			for(int j=1; j<=n; ++j)
				g[i][j]=min(g[i][j],max(f[i][k],g[k][j]));
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=n; ++j)
			printf("%lld%c",min(f[i][j],g[i][j])," \n"[j==n]);
}
int main() {
	freopen("graph.in","r",stdin);
	freopen("graph.out","w",stdout);
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}