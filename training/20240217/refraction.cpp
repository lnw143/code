#include<cstdio>
using namespace std;
using db = double;
const int N(2e2);
const db eps(1e-8);
int n,m,a[N + 2];
db e[N + 2][N + 2],p[N + 2],ans[N + 2];
void dfs(int u,db f) {
	if(f<eps) return ;
	ans[u]+=f*p[u];
	for(int i=1; i<=n; ++i)
		dfs(i,e[u][i]*f);
}
int main() {
	scanf("%d",&n);
	for(int i=1; i<=n; ++i)
		scanf("%d",&a[i]),p[i]=1;
	scanf("%d",&m);
	for(int i=1; i<=m; ++i) {
		static int x,y;
		static db z;
		scanf("%d%d%lf",&x,&y,&z);
		p[x]-=z;
		e[x][y]+=z;
	}
	for(int i=1; i<=n; ++i)
		dfs(i,a[i]);
	for(int i=1; i<=n; ++i)
		printf("%.6lf\n",ans[i]);
	return 0;
}