#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N = 12, M = N * N, S = 1 << N;
int n,m,s,i,j,k,l,d,g[N + 2][N + 2],f[N + 2][N + 2][S + 2];
int em,e[M + 2],ls[N + 2],nx[M + 2],cs[M + 2];
void insert(int x,int y,int z) {
	e[++em]=y;
	nx[em]=ls[x];
	cs[em]=z;
	ls[x]=em;
}
int main() {
	freopen("treasure.in","r",stdin);
	freopen("treasure.out","w",stdout);
	scanf("%d%d",&n,&m);
	s=1<<n;
	memset(g,0x3f,sizeof(g));
	for(i=1; i<=n; ++i)
		g[i][i]=0;
	for(i=1; i<=m; ++i) {
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		if(w<g[u][v])
			g[u][v]=g[v][u]=w;
	}
	memset(f,0x3f,sizeof(f));
#define pw2(x) (1<<((x)-1))
	for(i=1; i<=n; ++i)
		for(j=1; j<=n; ++j) {
			f[i][j][pw2(i)]=0;
			if(i!=j&&g[i][j]<0x3f3f3f3f)
				insert(i,j,g[i][j]);
		}
	for(i=1; i<s; ++i)
		for(j=(i-1)&i; j; j=(j-1)&i)
			for(k=1; k<=n; ++k)
				if((i^j)&pw2(k))
					for(l=ls[k]; l; l=nx[l])
						if(j&pw2(e[l]))
							for(d=1; d<n; ++d)
								f[k][d][i]=min(f[k][d][i],f[k][d][i^j]+f[e[l]][d+1][j]+d*cs[l]);
	int ans=1e9;
	for(i=1; i<=n; ++i)
		ans=min(ans,f[i][1][s-1]);
	printf("%d",ans);
	return 0;
}