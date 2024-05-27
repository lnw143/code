#include<cstdio>
#include<cstring>
using namespace std;
const int N(13), S(1 << N);
using ll = long long;
int T,n,m,s,i,j,k,l,v[N + 2],pw2[N + 2],f[S + 2][N + 2][N + 2];
ll g[S + 2][N + 2][N + 2];
bool e[N + 2][N + 2];
int trans(int x,int y,int z) {
	return v[z]+v[y]*v[z]+(e[x][z]?v[x]*v[y]*v[z]:0);
}
int main() {
	scanf("%d",&T);
	for(i=1; i<=N; ++i)
		pw2[i]=(1<<(i-1));
	while(T--) {
		memset(e,0,sizeof(e));
		memset(f,0x80,sizeof(f));
		scanf("%d%d",&n,&m);
		s=1<<n;
		for(i=1; i<=n; ++i)
			scanf("%d",&v[i]);
		for(i=1; i<=m; ++i) {
			static int x,y;
			scanf("%d%d",&x,&y);
			e[x][y]=e[y][x]=true;
		}
		if(n==1) {
			printf("%d %d\n",v[1],1);
			continue;
		}
		for(i=1; i<=n; ++i) {
			f[pw2[i]][0][i]=v[i];
			g[pw2[i]][0][i]=1;
		}
		for(i=1; i<s; ++i) {
			for(j=0; j<=n; ++j) if(j==0||(i&pw2[j]))
					for(k=1; k<=n; ++k) if(k!=j&&(i&pw2[k]))
							if(g[i][j][k]) {
								for(l=1; l<=n; ++l)
									if(!(i&pw2[l])&&e[k][l]) {
										if(f[i][j][k]+trans(j,k,l)>f[i|pw2[l]][k][l]) {
											f[i|pw2[l]][k][l]=f[i][j][k]+trans(j,k,l);
											g[i|pw2[l]][k][l]=g[i][j][k];
										} else if(f[i][j][k]+trans(j,k,l)==f[i|pw2[l]][k][l])
											g[i|pw2[l]][k][l]+=g[i][j][k];
									}
							}
		}
		int maxn=0;
		ll maxs=0;
		for(i=1; i<=n; ++i)
			for(j=1; j<=n; ++j) {
				if(f[s-1][i][j]>maxn)
					maxn=f[s-1][i][j],maxs=g[s-1][i][j];
				else if(f[s-1][i][j]==maxn)
					maxs+=g[s-1][i][j];
			}
		printf("%d %lld\n",maxn,maxs/2);
	}
	return 0;
}