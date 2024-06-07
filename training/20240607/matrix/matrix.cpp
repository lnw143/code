#include <cstdio>
#include <algorithm>
using namespace std;
const int N = 1e3;
int n,m,a[N + 2][N + 2],s[N + 2][N + 2],ans;
int l[N + 2][N + 2],r[N + 2][N + 2];
bool bz[N + 2][N + 2];
int main() {
	scanf("%d%d",&n,&m);
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j)
			scanf("%d",&a[i][j]);
	for(int i=n-1; i>=1; --i)
		for(int j=1; j<m; ++j)
			if(a[i][j]+a[i+1][j+1]<=a[i+1][j]+a[i][j+1])
				s[i][j]=s[i+1][j]+1;
	for(int i=1; i<=n; ++i) {
		for(int j=1; j<=m; ++j) {
			l[i][j]=j;
			while(l[i][j]>1&&s[i][l[i][j]-1]>=s[i][j]) l[i][j]=l[i][l[i][j]-1];
		}
		for(int j=m; j>=1; --j) {
			r[i][j]=j;
			while(r[i][j]<m&&s[i][r[i][j]+1]>=s[i][j]) r[i][j]=r[i][r[i][j]+1];
		}
		for(int j=1; j<=m; ++j)
			ans=max(ans,(s[i][j]+1)*(r[i][j]-l[i][j]+2));
	}
	printf("%d\n",ans);
	return 0;
}