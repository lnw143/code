#include <cstdio>
#include <cmath>
using namespace std;
const int N = 5e3, P = 1e9 + 7;
int T,n,h[N + 2],t[N + 2],p[N + 2],f[N + 2][N + 2],q[2][N + 2];
int main() {
	freopen("counting.in","r",stdin);
	freopen("counting.out","w",stdout);
	scanf("%d",&T);
	while(T--) {
		scanf("%d",&n);
		for(int i=1; i<=n; ++i)
			scanf("%d",&h[i]);
		int u,v;
		{
			int id[2]={0,0};
			for(int i=1; i<=n; ++i)
				q[h[i]&1][t[i]=++id[h[i]&1]]=i;
			u=id[0],v=id[1];
		}
		for(int i=1; i<=n; ++i) p[i]=0;
		for(int i=1; i<=n; ++i)
			for(int j=i+1; j<=n; ++j)
				if((h[i]-h[j])%2!=0&&abs(h[i]-h[j])>1)
					p[j]=i;
		for(int i=0; i<=u; ++i)
			for(int j=0; j<=v; ++j)
				f[i][j]=0;
		f[0][0]=1;
		for(int i=0; i<=u; ++i)
			for(int j=0; j<=v; ++j) {
				if(i<u&&p[q[0][i+1]]<=q[1][j]) (f[i+1][j]+=f[i][j])%=P;
				if(j<v&&p[q[1][j+1]]<=q[0][i]) (f[i][j+1]+=f[i][j])%=P;
			}
		printf("%d\n",f[u][v]);
	}
	return 0;
}