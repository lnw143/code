#include<cstdio>
using namespace std;
using ll = long long;
const int N = 1e3, P = 998244353;
int T,n,m,c,f,i,j,r[N + 2][N + 2],d[N + 2][N + 2],ansc,ansf;
bool a[N + 2][N + 2];
int main() {
	freopen("plant.in","r",stdin);
	freopen("plant.out","w",stdout);
	scanf("%d%*d",&T);
	while(T--) {
		scanf("%d%d%d%d",&n,&m,&c,&f);
		for(i=1; i<=n; ++i)
			for(j=1; j<=m; ++j)
				scanf("%1d",&a[i][j]);
		for(i=1; i<=n; ++i) {
			r[i][m+1]=-1;
			for(j=m; j>=1; --j)
				r[i][j]=a[i][j]?-1:r[i][j+1]+1;
		}
		for(j=1; j<=m; ++j) {
			d[n+1][j]=-1;
			for(i=n; i>=1; --i)
				d[i][j]=a[i][j]?-1:d[i+1][j]+1;
		}
		ansc=ansf=0;
#define ad(x,y) x=((x)+(y))%P
		for(j=1; j<=m; ++j) {
			int sum=0;
			for(i=3; i<=n; ++i) {
				if(a[i][j]||a[i-1][j]||a[i-2][j]) {
					sum=0;
					continue;
				}
				sum+=r[i-2][j];
				ad(ansc,(ll)sum*r[i][j]%P);
				ad(ansf,(ll)sum*r[i][j]%P*d[i][j]%P);
			}
		}
		printf("%d %d\n",ansc*c,ansf*f);
	}
	return 0;
}