#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
using ll = long long;
const int N = 150, P = 1e9 + 7;
int n,s[N + 2][N + 2];
ll f[2][2][N + 2][N + 2],g[2][2][N + 2][N + 2],ans;
bool check(int u,int l,int r) {
	return s[u][r]-s[u][l-1]==r-l+1;
}
template<int p,int q> inline ll sum(int u,int v,int x,int y) {
	if(u>v||x>y) return 0;
	return ((g[p][q][v][y]-g[p][q][u-1][y]-g[p][q][v][x-1]+g[p][q][u-1][x-1])%P+P)%P;
}
int main() {
	// freopen("subset.in","r",stdin);
	// freopen("subset.out","w",stdout);
	scanf("%d",&n);
	for(int i=1; i<=n; ++i)	
		for(int j=1; j<=n; ++j) {
			char c;
			scanf(" %c",&c);
			s[i][j]=s[i][j-1]+(c=='G');
		}
	for(int i=1; i<=n; ++i) {
		memset(f,0,sizeof(f));
		for(int j=1; j<=n; ++j)
			for(int k=j; k<=n; ++k)
				if(check(i,j,k)) {
					++f[0][0][j][k]%=P;
					(f[0][0][j][k]+=sum<0,0>(j,k,j,k))%=P;
					(f[0][1][j][k]+=sum<0,1>(j,k,k,n)+sum<0,0>(j,k,k+1,n))%=P;
					(f[1][0][j][k]+=sum<1,0>(1,j,j,k)+sum<0,0>(1,j-1,j,k))%=P;
					(f[1][1][j][k]+=sum<1,1>(1,j,k,n)+sum<0,1>(1,j-1,k,n)+sum<1,0>(1,j,k+1,n)+sum<0,0>(1,j-1,k+1,n))%=P;
					(ans+=f[0][0][j][k]+f[0][1][j][k]+f[1][0][j][k]+f[1][1][j][k])%=P;
				}
		memset(g,0,sizeof(g));
		for(int p=0; p<2; ++p)
			for(int q=0; q<2; ++q)
				for(int i=1; i<=n; ++i)
					for(int j=1; j<=n; ++j)
						g[p][q][i][j]=((g[p][q][i-1][j]+g[p][q][i][j-1]-g[p][q][i-1][j-1]+f[p][q][i][j])%P+P)%P;

	}
	printf("%lld",ans);
	return 0;
}