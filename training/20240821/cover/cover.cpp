#include <cstdio>
#include <algorithm>
using namespace std;
using ll = long long;
const int N = 5e3, P = 998244353;
int n,a[N + 2],b[N + 2],r,fac;
int s,t;
int f[N + 2][N + 2],g[N + 2][N + 2];
int main() {
	freopen("cover.in","r",stdin);
	freopen("cover.out","w",stdout);
	scanf("%d",&n);
	for(int i=1; i<=n; ++i)
		scanf("%d",&a[i]),
		b[a[i]]=max(b[a[i]],n-i+1),
		r=max(r,min(n-i+1,a[i]));
	for(int i=n-1; i>=1; --i) b[i]=max(b[i+1],b[i]);
	fac=1;
	for(int i=1; i<=r; ++i) fac=(ll)fac*i%P;
	for(int i=1; i<=n; ++i) {
		if(a[i]>r) s=max(s,n-i+1);
		if(n-i+1>r) t=max(t,a[i]);
	}
	f[0][s]=1;
	for(int i=0; i<r; ++i)
		for(int j=0; j<=s; ++j)	{
			(f[i+1][j]+=f[i][j]*ll(b[i+1]-j)%P)%=P;
			if(j>0) (f[i+1][j-1]+=(ll)f[i][j]*j%P)%=P;
		}
	g[0][t]=1;
	for(int i=0; i<r; ++i)
		for(int j=0; j<=t; ++j)	{
			(g[i+1][j]+=g[i][j]*ll(a[n-i]-j)%P)%=P;
			if(j>0) (g[i+1][j-1]+=(ll)g[i][j]*j%P)%=P;
		}
	printf("%d %d",r,(f[r][0]+g[r][0]-fac+P)%P);
	return 0;
}