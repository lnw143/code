#include <cstdio>
using namespace std;
const int N = 5e2;
int n,m,id,x,y,z;
int ans[N + 2][N + 2];
int main() {
	freopen("matrix.in","r",stdin);
	freopen("matrix.out","w",stdout);
	scanf("%d%d%d",&n,&m,&id);
	if(id) scanf("%d%d%d",&x,&y,&z);
	else x=y=z=1;
	int cnt=0;
	for(int i=1; i+1<=n; i+=2) {
		for(int j=1; j<=m; ++j)
			if(j&1) {
				ans[i][j]=++cnt;
				ans[i+1][j]=++cnt;
			} else {
				ans[i+1][j]=++cnt;
				ans[i][j]=++cnt;
			}
	}
	if(n&1)
		for(int j=1; j<=m; ++j)
			ans[n][j]=++cnt;
	printf("Yes\n");
	int delta=z-ans[x][y];
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j)
			printf("%d%c",(ans[i][j]+delta+n*m-1)%(n*m)+1," \n"[j==m]);
	return 0;
}