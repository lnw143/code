#include<cstdio>
using namespace std;
const int N = 1e3 + 2;
using ll = long long;
int n,i,j,q,a,b,c,d,sum[N][N];
char ch;
bool p[N][N];
ll gs(ll x,ll y) {
	return sum[n][n]*(x/n)*(y/n)+(x/n)*sum[n][y%n]+(y/n)*sum[x%n][n]+sum[x%n][y%n];
}
int main() {
	scanf("%d%d",&n,&q);
	for(i=1; i<=n; ++i)
		for(j=1; j<=n; ++j) {
			scanf(" %c",&ch);
			p[i][j]=ch=='B';
			sum[i][j]=sum[i][j-1]+sum[i-1][j]-sum[i-1][j-1]+p[i][j];
		}
	for(i=1; i<=q; ++i)	{
		scanf("%d%d%d%d",&a,&b,&c,&d);
		printf("%lld\n",gs(c+1,d+1)-gs(c+1,b)-gs(a,d+1)+gs(a,b));
	}
	return 0;
}