#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
using ll = long long;
const int N(80);
const ll inf(0x3f3f3f3f3f3f3f3f);
int n,p[N + 2][N + 2],r[N + 2][N + 2],d[N + 2][N + 2];
ll f[N + 2][N + 2][N + 2][N + 2],g[N + 2][N + 2][N + 2][N + 2];
int cmp(int x,int y,int u,int v) {
	return p[x][y]>p[u][v];
}
int main() {
	scanf("%d",&n);
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=n; ++j)
			scanf("%d",&p[i][j]);
	for(int i=1; i<=n; ++i)
		for(int j=1; j<n; ++j)
			scanf("%d",&r[i][j]);
	for(int i=1; i<n; ++i)
		for(int j=1; j<=n; ++j)
			scanf("%d",&d[i][j]);
	memset(f,0x3f,sizeof(f));
	f[1][1][1][1]=0;
	g[1][1][1][1]=0;
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=n; ++j)
			for(int u=1; u<=i; ++u)
				for(int v=1; v<=j; ++v) if(f[i][j][u][v]<inf) {
					if(i<n) {
						ll now=f[i][j][u][v];
						ll need=max(0ll,d[i][j]-g[i][j][u][v]);
						need=need/p[u][v]+!!(need%p[u][v]);
						ll &to=cmp(u,v,i+1,j)?f[i+1][j][u][v]:f[i+1][j][i+1][j],
							&to2=cmp(u,v,i+1,j)?g[i+1][j][u][v]:g[i+1][j][i+1][j];
						if(now+need+1<to||now+need+1==to&&g[i][j][u][v]-d[i][j]+need*p[u][v]>to2) {
							to=now+need+1;
							to2=g[i][j][u][v]-d[i][j]+need*p[u][v];
						}
					}
					if(j<n) {
						ll now=f[i][j][u][v];
						ll need=max(0ll,r[i][j]-g[i][j][u][v]);
						need=need/p[u][v]+!!(need%p[u][v]);
						ll &to=cmp(u,v,i,j+1)?f[i][j+1][u][v]:f[i][j+1][i][j+1],
							&to2=cmp(u,v,i,j+1)?g[i][j+1][u][v]:g[i][j+1][i][j+1];
						if(now+need+1<to||now+need+1==to&&g[i][j][u][v]-r[i][j]+need*p[u][v]>to2) {
							to=now+need+1;
							to2=g[i][j][u][v]-r[i][j]+need*p[u][v];
						}
					}
				}
	ll ans=inf;
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=n; ++j)
			ans=min(ans,f[n][n][i][j]);
	printf("%lld",ans);
	return 0;
}