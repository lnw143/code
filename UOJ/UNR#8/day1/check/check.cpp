#include <cstdio>
#include <set>
using namespace std;
const int L = 1e6, N = 10, M = 5e4;
int l,n,m,q,ans;
char s[L + 2],a[N + 2][M + 2];
set<int> bz[N + 2][M + 2];
void dfs(int x,int y,int p) {
	if(a[x][y]!=s[p]||x>n||x<1||y>m||y<1||bz[x][y].count(p)) return ;
	bz[x][y].insert(p);
	ans=max(ans,p);
	if(p>l) return ;
	dfs(x+1,y,p+1);
	dfs(x-1,y,p+1);
	dfs(x,y+1,p+1);
	dfs(x,y-1,p+1);
}
int main() {
	scanf("%d%d%d%d%s",&l,&n,&m,&q,s+1);
	for(int i=1; i<=n; ++i) scanf("%s",a[i]+1);
	for(int i=1; i<=q; ++i) {
		int x,y,p;
		scanf("%d%d%d",&x,&y,&p);
		ans=p+1;
		for(int j=1; j<=n; ++j) for(int k=1; k<=m; ++k) bz[i][j].clear();
		dfs(x,y,p);
		printf("%d\n",ans-p+1);
	}
	return 0;
}