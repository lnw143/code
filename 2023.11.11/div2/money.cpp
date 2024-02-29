#include<cstdio>
using namespace std;
const int M = 1e4 + 2, P = 1e9 + 2;
using ll = long long;
ll N;
int m,n,f[M][M];
int c(int n,int m) {
	for(int i=0; i<=n; ++i)
		f[i][0]=f[i][i]=1;
	for(int i=1; i<=n; ++i)
		for(int j=1; j<i; ++j)
			f[i][j]=(f[i-1][j]+f[i-1][j-1])%P;
	return f[n][m];
}
int main() {
	freopen("money.in","r",stdin);
	freopen("money.out","w",stdout);
	scanf("%lld%d",&N,&m);
	n=N/100%m;
	printf("%d",c(m,n));
	return 0;
}