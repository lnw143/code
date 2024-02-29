#include<cstdio>
using namespace std;
using ll = long long;
const int N = 5e3, P = 998244353;
int n,m,i,j,s,f[N + 2][N + 2],ans;
int main() {
	scanf("%d%d%d",&n,&m,&s);
	f[1][1]=s?1:m%P;
	for(i=2; i<=n; ++i) {
		scanf("%d",&s);
		for(j=1; j<=i&&j<=m+1; ++j)
			if(s)
				f[i][j]=f[i-1][j-1];
			else
				f[i][j]=((ll)f[i-1][j-1]*(m+1-j)%P+(ll)f[i-1][j]*j%P)%P;
	}
	for(i=1; i<=n; ++i)
		ans=(ans+f[n][i])%P;
	printf("%d",ans);
	return 0;
}