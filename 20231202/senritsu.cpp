#include<cstdio>
using namespace std;
const int N = 1e3 + 2, P = 1e9 + 7;
int n,m,x,y,i,j,a[N],f[N],tot,que[N],deg[N],h,t,mx,ans;
bool e[N][N];
int main() {
	scanf("%d%d",&n,&m);
	for(i=1; i<=m; ++i) {
		scanf("%d%d",&x,&y);
		if(x<y) e[x][y]=true;
		else e[y][x]=true;
	}
	for(i=1; i<=n; ++i)
		for(j=i+1; j<=n; ++j)
			if(!e[i][j]) e[j][i]=true;
	tot=n;
	for(i=1; i<=n; ++i) {
		for(j=1; j<=n; ++j)
			deg[i]+=e[j][i];
		if(deg[i]==0)
			que[++t]=i;
	}
	while(h<t) {
		++h;
		a[que[h]]=tot--;
		for(i=1; i<=n; ++i) if(deg[i]>0) {
				deg[i]-=e[que[h]][i];
				if(deg[i]==0)
					que[++t]=i;
			}
	}
	f[1]=1;
	for(i=2; i<=n; ++i) {
		for(j=i-1,mx=0; j>=1; --j) if(a[j]<a[i]&&a[j]>mx) {
				mx=a[j];
				(f[i]+=f[j])%=P;
			}
		if(f[i]==0) f[i]=1;
	}
	for(i=n,mx=0; i>=1; --i) if(a[i]>mx) {
			mx=a[i];
			(ans+=f[i])%=P;
		}
	printf("%d",ans);
	return 0;
}