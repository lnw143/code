#include<cstdio>
#include<algorithm>
#define rep(i,l,r) for(int i(l); i<=(r); ++i)
#define per(i,r,l) for(int i(r); i>=(l); --i)
using namespace std;
const int N = 1500;
int n,m,k,a[N + 2][N + 2],b[N + 2][N + 2],s[N + 2][N + 2];
int lu[N + 2][N + 2],ru[N + 2][N + 2],ld[N + 2][N + 2],rd[N + 2][N + 2];
int ans;
int rect_sum(int x1,int y1,int x2,int y2) {
	return s[x2][y2]-s[x1-1][y2]-s[x2][y1-1]+s[x1-1][y1-1];
}
int main() {
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j) {
			scanf("%d",&a[i][j]);
			s[i][j]=s[i-1][j]+s[i][j-1]-s[i-1][j-1]+a[i][j];
		}
	rep(i,1,n-k+1)
		rep(j,1,m-k+1)
			b[i][j]=rect_sum(i,j,i+k-1,j+k-1);
	rep(i,1,n) {
		rep(j,1,m) lu[i][j]=max({lu[i-1][j],lu[i][j-1],b[i][j]});
		per(j,m,1) ru[i][j]=max({ru[i-1][j],ru[i][j+1],b[i][j]});
	}
	per(i,n,1) {
		rep(j,1,m) ld[i][j]=max({ld[i+1][j],ld[i][j-1],b[i][j]});
		per(j,m,1) rd[i][j]=max({rd[i+1][j],rd[i][j+1],b[i][j]});
	}
	rep(i,k,n-k)
		rep(j,k,m-k) {
			ans=max(ans,lu[i-k+1][j-k+1]+ru[i-k+1][j+1]+rd[i+1][1]);
			ans=max(ans,lu[i-k+1][j-k+1]+ld[i+1][j-k+1]+rd[1][j+1]);
			ans=max(ans,lu[i-k+1][m-k+1]+ld[i+1][j-k+1]+rd[i+1][j+1]);
			ans=max(ans,lu[n-k+1][j-k+1]+ru[i-k+1][j+1]+rd[i+1][j+1]);
			ans=max(ans,lu[n-k+1][j-k+1]+b[i+1][j+1]+rd[1][j+k+1]);
			ans=max(ans,lu[i-k+1][m-k+1]+b[i+1][j+1]+rd[i+k+1][1]);
		}
	printf("%d",ans);
	return 0;
}