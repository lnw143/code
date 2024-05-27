#include<cstdio>
using namespace std;
const int N = 11, M = 1 << N;
int n,m,i,j,k,a[M + 2][M + 2],f[2][M + 2][M + 2],tot;
int g(int x) {
	if(x<1) return x+m;
	if(x>m) return x-m;
	return x;
}
int main() {
	freopen("set.in","r",stdin);
	freopen("set.out","w",stdout);
	scanf("%d",&n);
	m=1<<n;
	for(i=1; i<=m; ++i)
		for(j=1; j<=m; ++j)
			scanf("%d",&f[n&1][i][j]);
	for(k=n; k>1; --k) {
		int len=1<<(k-2),k1=k&1,k2=k1^1;
		for(i=1; i<=m; ++i)
			for(j=1; j<=m; ++j)
				f[k2][i][j]=0;
		for(i=1; i<=m; ++i)
			for(j=1; j<=m; ++j)
				if(f[k1][i][j]) {
					f[k2][g(i+len)][j]^=1;
					f[k2][g(i-len)][j]^=1;
					f[k2][i][g(j+len)]^=1;
					f[k2][i][g(j-len)]^=1;
					f[k2][i][j]^=1;
				}
	}
	for(i=1; i<=m; ++i)
		for(j=1; j<=m; ++j)
			tot+=f[1][i][j];
	printf("%d\n",tot);
	for(i=1; i<=m; ++i)
		for(j=1; j<=m; ++j)
			if(f[1][i][j])
				printf("%d %d\n",i-1,j-1);
	return 0;
}