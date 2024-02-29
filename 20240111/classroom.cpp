#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
using db = double;
const int N = 2e3, M = 2e3;
const db inf = 1e20;
int n,m,i,j,v,e,c[N + 2],d[N + 2];
db k[N + 2],f[N + 2][M + 2][2],ans=inf;
namespace Graph {
	const int V = 3e2, E = 9e4;
	int floyd[V + 2][V + 2];
	void init() {
		memset(floyd,0x3f,sizeof(floyd));
		for(int i=1; i<=v; ++i)
			floyd[i][i]=0;
	}
	void read() {
		int a,b,w;
		scanf("%d%d%d",&a,&b,&w);
		if(w<floyd[a][b])
			floyd[a][b]=floyd[b][a]=w;
	}
	void get_dis() {
		for(int k=1; k<=v; ++k)
			for(int i=1; i<=v; ++i)
				for(int j=1; j<=v; ++j)
					floyd[i][j]=min(floyd[i][j],floyd[i][k]+floyd[k][j]);
	}
}
int main() {
	freopen("classroom.in","r",stdin);
	freopen("classroom.out","w",stdout);
	scanf("%d%d%d%d",&n,&m,&v,&e);
	for(i=1; i<=n; ++i)
		scanf("%d",&c[i]);
	for(i=1; i<=n; ++i)
		scanf("%d",&d[i]);
	for(i=1; i<=n; ++i)
		scanf("%lf",&k[i]);
	Graph::init();
	for(i=1; i<=e; ++i)
		Graph::read();
	Graph::get_dis();
#define dis(x,y) Graph::floyd[x][y]
#define upd(x,y) x=min(x,y)
	memset(f,0x7f,sizeof(f));
	f[1][1][1]=f[1][0][0]=0;
	for(i=2; i<=n; ++i)
		for(j=0; j<=i&&j<=m; ++j) {
			upd(f[i][j][0],f[i-1][j][0]+dis(c[i-1],c[i]));
			upd(f[i][j][0],f[i-1][j][1]+wt(dis(d[i-1],c[i]),dis(c[i-1],c[i]),k[i-1]));
			if(j>0) {
				upd(f[i][j][1],f[i-1][j-1][0]+wt(dis(d[i],c[i-1]),dis(c[i],c[i-1]),k[i]));
				upd(f[i][j][1],f[i-1][j-1][1]+
				    dis(d[i],d[i-1])*k[i]*k[i-1]+
				    dis(c[i],d[i-1])*(1-k[i])*k[i-1]+
				    dis(d[i],c[i-1])*k[i]*(1-k[i-1])+
				    dis(c[i],c[i-1])*(1-k[i])*(1-k[i-1])
				   );
			}
		}
	for(i=0; i<=n&&i<=m; ++i)
		ans=min(ans,min(f[n][i][0],f[n][i][1]));
	printf("%.2lf",ans);
	return 0;
}