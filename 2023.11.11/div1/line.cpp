#include<cstdio>
#include<cstring>
using namespace std;
const int N = 1e2 + 2;
int T,n,a[N],f[N][N],g[N][N],fm[N],gm[N],i,j,k,ans;
int max(int a,int b) {
	return a<b?b:a;
}
int main() {
	freopen("line.in","r",stdin);
	freopen("line.out","w",stdout);
	scanf("%d",&T);
	while(T--) {
		scanf("%d",&n);
		for(i=1; i<=n; ++i)
			scanf("%d",&a[i]),fm[i]=gm[i]=0;
		memset(f,0,sizeof(f));
		memset(g,0,sizeof(g));
		for(i=1; i<=n; ++i)
			for(j=0; j<i; ++j)
				if(a[j]<a[i]||j==0) {
					f[i][j]=1;
					for(k=0; k<j; ++k)
						if(a[j]-a[k]<a[i]-a[j]||k==0)
							f[i][j]=max(f[i][j],f[j][k]+1);
					fm[i]=max(fm[i],f[i][j]);
				}
		for(i=1,j=n; i<j; ++i,--j)
			a[i]^=a[j]^=a[i]^=a[j];
		for(i=1; i<=n; ++i)
			for(j=0; j<i; ++j)
				if(a[j]<a[i]||j==0) {
					g[i][j]=1;
					for(k=0; k<j; ++k)
						if(a[j]-a[k]<a[i]-a[j]||k==0)
							g[i][j]=max(g[i][j],g[j][k]+1);
					gm[i]=max(gm[i],g[i][j]);
				}
		ans=0;
		for(i=1; i<=n; ++i)
			ans=max(ans,fm[i]+gm[n-i+1]-1);
		printf("%d\n",ans);
	}
	return 0;
}