#include <cstdio>
using namespace std;
const int N = 5e3, P = 998244353;
int n,k,a[N + 2];
int f[N + 2][N + 2][2];
int main() {
	scanf("%d%d",&n,&k);
	for(int i=1; i<=n; ++i)
		scanf("%1d",&a[i]);
	f[0][0][0]=1;
	for(int i=1; i<=n; ++i)
		for(int j=0; j<=k; ++j) {
			if(a[i]==0) {
				(f[i][j][0]+=(f[i-1][j][0]+f[i-1][j][1])%P)%=P;
				if(j>0) (f[i][j][1]+=f[i-1][j-1][0])%=P;
			} else {
				if(j>0) (f[i][j][0]+=(f[i-1][j-1][0]+f[i-1][j-1][1])%P)%=P;
				(f[i][j][1]+=f[i-1][j][0])%=P;
			}
		}
	int z=0,ans=0;
	for(int i=n; i>=0; --i) {
		for(int j=0; j<=k-z; ++j)
			(ans+=f[i][j][0])%=P;
		z+=!a[i];
	}
	printf("%d",ans);
	return 0;
}