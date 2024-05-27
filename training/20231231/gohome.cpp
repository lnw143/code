#include<cstdio>
#include<queue>
#define X first
#define Y second
using namespace std;
using pii = pair<int,int>;
const int N = 5e2 + 2, w[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
int n,m,i,j,sx,sy,ex,ey,dis[N][N],r,limit,clk,bz[N][N];
char s[N][N];
bool vis[N][N];
queue<pii> q;
void bfs() {
	while(!q.empty()) {
		int x=q.front().X,y=q.front().Y;
		q.pop();
		for(int i=0; i<4; ++i) {
			int u=x+w[i][0],v=y+w[i][1];
			if(u<1||u>n||v<1||v>m||vis[u][v]) continue;
			dis[u][v]=dis[x][y]+1;
			vis[u][v]=true;
			q.push(pii(u,v));
		}
		r=dis[x][y];
	}
}
bool dfs(int x,int y) {
	if(x<1||x>n||y<1||y>m||bz[x][y]==clk||dis[x][y]<limit) return false;
	if(x==ex&&y==ey) return true;
	bz[x][y]=clk;
	for(int i=0; i<4; ++i)
		if(dfs(x+w[i][0],y+w[i][1]))
			return true;
	return false;
}
bool ck(int lim) {
	limit=lim;
	++clk;
	return dfs(sx,sy);
}
int bin_ans(int l,int r) {
	int mid;
	while(l<r) {
		mid=(l+r)/2;
		if(ck(mid))
			l=mid+1;
		else
			r=mid;
	}
	return l-1;
}
int main() {
	scanf("%d%d",&n,&m);
	for(i=1; i<=n; ++i)
		for(j=1; j<=m; ++j) {
			do s[i][j]=getchar();
			while(s[i][j]!='.'&&s[i][j]!='+'&&s[i][j]!='V'&&s[i][j]!='J');
			switch(s[i][j]) {
				case 'V':
					sx=i,sy=j;
					break;
				case 'J':
					ex=i,ey=j;
					break;
				case '+':
					q.push(pii(i,j));
					vis[i][j]=true;
					dis[i][j]=0;
					break;
				default:
					break;
			}
		}
	bfs();
	printf("%d",bin_ans(1,r));
	return 0;
}