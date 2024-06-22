#include <cstdio>
#define popcnt __builtin_popcountll
using namespace std;
const int N = 20, M = 1 << N, P = 1e9 + 9;
int n,m,a[N + 2][M + 2],b[N + 2][M + 2],c[N + 2][M + 2];
void fmtOr(int *a,int n,int t) {
	for(int i=0; i<n; ++i)
		for(int j=0; j<(1<<n); ++j)
			if(j&(1<<i))
				(a[j]+=a[j^(1<<i)]*t)%=P;
}
int main() {
	scanf("%d",&n);
	m=1<<n;
	for(int i=0; i<m; ++i) scanf("%d",&a[popcnt(i)][i]);
	for(int i=0; i<m; ++i) scanf("%d",&b[popcnt(i)][i]);
	for(int i=0; i<=n; ++i) {
		fmtOr(a[i],n,1);
		fmtOr(b[i],n,1);
	}
	for(int i=0; i<=n; ++i)
		for(int j=0; j<=n-i; ++j)
			for(int k=0; k<m; ++k)
				(c[i+j][k]+=1ll*a[i][k]*b[j][k]%P)%=P;
	for(int i=0; i<=n; ++i)
		fmtOr(c[i],n,-1);
	for(int i=0; i<m; ++i)
		printf("%d ",(c[popcnt(i)][i]%P+P)%P);
	return 0;
}