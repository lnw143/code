#include <cstdio>
#include <queue>
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;
const int N = 50;
int n,m,tot,col[N + 2][N + 2],dep[N * N + 2],ans=1e9,ansx,ansy;
int x[N * N + 2],y[N * N + 2];
char s[N + 2][N + 2];
vector<int> e[N * N + 2];
void dfs(int x,int y,char c) {
	if(x<1||x>n||y<1||y>m||col[x][y]||s[x][y]!=c) return ;
	col[x][y]=tot;
	dfs(x+1,y,c);
	dfs(x-1,y,c);
	dfs(x,y+1,c);
	dfs(x,y-1,c);
}
void bfs(int s) {
	for(int i=1; i<=tot; ++i) dep[i]=-1;
	dep[s]=0;
	queue<int> Q;
	Q.push(s);
	while(Q.size()) {
		int u=Q.front();
		Q.pop();
		for(auto v : e[u])
			if(dep[v]==-1)
				dep[v]=dep[u]+1,
				Q.push(v);
	}
	int res=*max_element(dep+1,dep+tot+1);
	if(res<ans) {
		ans=res;
		ansx=x[s];
		ansy=y[s];
	}
}
int main() {
	freopen("paint.in","r",stdin);
	freopen("paint.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1; i<=n; ++i)
		scanf("%s",s[i]+1);
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j)
			if(s[i][j]!='x'&&!col[i][j]) {
				++tot;
				x[tot]=i;
				y[tot]=j;
				dfs(i,j,s[i][j]);
			}
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j)
			for(auto [x,y] : vector<pair<int,int>>{{1,0}, {-1,0}, {0,1}, {0,-1}}) {
				int u=i+x,v=j+y;
				if(u<1||u>n||v<1||v>m||s[u][v]=='x') continue;
				if(col[u][v]!=col[i][j])
					e[col[u][v]].push_back(col[i][j]),
					e[col[i][j]].push_back(col[u][v]);
			}
	for(int i=1; i<=tot; ++i) {
		sort(e[i].begin(),e[i].end());
		e[i].erase(unique(e[i].begin(),e[i].end()),e[i].end());
	}
	for(int i=1; i<=tot; ++i) bfs(i);
	printf("%d\n",ans);
	for(int i=1; i<=ans; ++i)
		printf("%d %d\n",ansx,ansy);
	return 0;
}