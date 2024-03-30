#include<cstdio>
#include<algorithm>
using ll = long long;
using namespace std;
const int N = 5e2, P = 1e9 + 7;
int n,a[N + 2],b[N + 2],f[N + 2][N + 2],g[N + 2][N + 2],u[N + 2],v[N + 2][N + 2];
ll su[N + 2],sv[N + 2];
int main() {
	scanf("%d",&n);
	for(int i=1; i<=n; ++i)
		scanf("%d",&a[i]),su[i]=su[i-1]+a[i];
	for(int i=1; i<=n; ++i)
		scanf("%d",&b[i]),sv[i]=sv[i-1]+b[i];
	f[0][0]=1;
	for(int i=1; i<=n; ++i) {
		for(int j=0; j<i; ++j)
			v[i][j]=j;
		sort(v[i],v[i]+i,[&](int x,int y) {
			return (sv[i]-sv[x])*(i-y)<(sv[i]-sv[y])*(i-x);
		});
	}
	for(int i=1; i<=n; ++i) {
		for(int j=0; j<i; ++j)
			u[j]=j;
		sort(u,u+i,[&](int x,int y) {
			return (su[i]-su[x])*(i-y)<(su[i]-su[y])*(i-x);
		});
		for(int j=1; j<=n; ++j) {
			g[j-1][0]=0;
			for(int k=1; k<=i; ++k) {
				g[j-1][k]=g[j-1][k-1]+f[u[k-1]][j-1];
				if(g[j-1][k]>=P) g[j-1][k]-=P;
			}
			for(int k=0,l=0; k<j; ++k) {
				while(l<i&&(su[i]-su[u[l]])*(j-v[j][k])<=(sv[j]-sv[v[j][k]])*(i-u[l])) ++l;
				f[i][j]+=g[v[j][k]][l];
				if(f[i][j]>=P) f[i][j]-=P;
			}
		}
	}
	printf("%d",f[n][n]);
	return 0;
}