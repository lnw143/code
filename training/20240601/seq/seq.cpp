#include <cstdio>
using namespace std;
const int N = 70, M = 70, S = 20, P = 1e9 + 7;
using ll = long long;
int n,m,a[N + 2];
ll f[N + 2][N + 2][M + 2][S + 2];
int main() {
	freopen("seq.in","r",stdin);
	freopen("seq.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1; i<=n; ++i)
		scanf("%d",&a[i]);
	for(int i=1; i<=n; ++i)
		for(int j=i; j<=n; ++j)
			f[i][j][1][0]=1;
			
	printf("%lld",(dp::f[1][n]%P+P)%P);
	return 0;
}