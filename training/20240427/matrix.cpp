#include<cstdio>
using namespace std;
using llu = long long unsigned;
constexpr int N = 110, M = 1e7 + 19, K = 5;
const llu P = 131;
int n,m,ans;
char s[N + 2][N + 2];
llu powP[N + 2],a[N + 2][N + 2][N + 2],id[M];
bool hs[M];
void Hash(llu x) {
	int y=x%M;
	while(hs[y]&&id[y]!=x) (++y==M)&&(y=0);
	if(!hs[y]) {
		++ans;
		hs[y]=true;
		id[y]=x;
	}
}
int main() {
	// freopen("matrix.in","r",stdin);
	// freopen("matrix.out","w",stdout);
	powP[0]=1;
	powP[1]=P;
	for(int i=1; i<=N+1; ++i)
		powP[i]=powP[i-1]*P;
	scanf("%d%d",&n,&m);
	for(int i=1; i<=n; ++i)
		scanf("%s",s[i]+1);
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j) {
			a[i][j][1]=s[i][j];
			for(int k=2; j+k-1<=m; ++k)
				a[i][j][k]=a[i][j][k-1]*P+s[i][j+k-1];
		}
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j)
			for(int k=1; j+k-1<=m; ++k) {
				llu now=a[i][j][k];
				Hash(now);
				for(int l=2; i+l-1<=n; ++l) {
					now=now*powP[k+1]+a[i+l-1][j][k];
					Hash(now);
				}
			}
	printf("%d",ans);
	return 0;
}