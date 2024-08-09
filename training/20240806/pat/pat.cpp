#include <cstdio>
#include <cstring>
#define popcnt __builtin_popcount
using namespace std;
using ll = long long;
const int N = 7, M = 7, K = 500, S = 1 << N, P = 998244353;
int n,m,a[N + 2][K + 2],b[K + 2],pow2[K + 2],k[N + 2],s[M + 2],f[K + 2][S + 2][S + 2];
int ans;
char r[K + 2];
int main() {
	freopen("pat.in","r",stdin);
	freopen("pat.out","w",stdout);
	scanf("%d%d",&n,&m);
	pow2[0]=1;
	for(int i=1; i<=K; ++i) pow2[i]=pow2[i-1]*2ll%P;
	for(int i=1; i<=n; ++i) {
		scanf("%s",r+1);
		int k=strlen(r+1);
		for(int j=1; j<=k; ++j)
			a[i][j]=(a[i][j-1]+(r[k-j+1]-'0')*pow2[j-1])%P;
	}
	for(int i=K; i>0; --i)
		for(int j=0; j<(1<<n); ++j)
			for(int k=0; k<(1<<m); ++k) {
				if(!f[i][j][k]) continue;
				if(k==(1<<m)-1) {
					ll res=f[i][j][k];
					for(int p=1; p<=n; ++p)
						if((i>>(p-1))&1) (res*=pow2[i])%=P;
						else (res*=a[p][i]+1)%=P;
					ans=(ans+res)%P;
					continue;
				}
				// int lim=j|;
				
			}
	return 0;
}