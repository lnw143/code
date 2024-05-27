#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N = 1e4 + 2, M = 1e3 + 2, inf = 0x7f7f7f7f;
int n,m,k,i,j,x[N],y[N],p,l[N],h[N],g[M],f[2][M],ans;
int divup(int a,int b) {
	return a/b+(a%b>0);
}
int main() {
	freopen("bird1.in","r",stdin);
	freopen("bird1.out","w",stdout);
	scanf("%d%d%d",&n,&m,&k);
	for(i=1; i<=n; ++i)
		scanf("%d%d",&x[i],&y[i]);
	for(i=1; i<=k; ++i) {
		scanf("%d",&p);
		scanf("%d%d",&l[p],&h[p]);
	}
#define nw f[i&1]
#define pr f[(i&1)^1]
	for(i=1; i<=n; ++i) {
		memset(g,0x7f,sizeof(*g)*x[i]);
		bool flag=false;
		for(j=1; j<m; ++j) {
			if(j>x[i]) g[j%x[i]]=min(g[j%x[i]],pr[j-x[i]])+1;
			if(h[i]==0||(l[i]<j&&j<h[i])) {
				nw[j]=min(g[j%x[i]],j+y[i]<=m?pr[j+y[i]]:inf);
				if(nw[j]<inf) flag=true;
			} else nw[j]=inf;
		}
		nw[m]=inf;
		if(h[i]==0) {
			for(j=1; j<=m; ++j)
				nw[m]=min(nw[m],j==m?pr[j]+1:pr[j]+divup(m-j,x[i]));
			if(nw[m]<inf) flag=true;
		}
		if(!flag) {
			printf("0\n%d",ans);
			return 0;
		}
		if(h[i]) ++ans;
	}
#undef nw
#undef pr
	ans=inf;
	for(i=1; i<=m; ++i)
		ans=min(ans,f[n&1][i]);
	printf("1\n%d",ans);
	return 0;
}