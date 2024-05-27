#include<cstdio>
#include<algorithm>
#include<utility>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;
const int N = 2e3;
using pos = pair<int,int>;
const vector<pos> e({pos(1, 1), pos(1, 0), pos(1, -1), pos(0, 1), pos(0, -1), pos(-1, 1), pos(-1, 0), pos(-1, -1)});
int n,m,i,j,l=1e9,r,ans=1e9;
char s[N + 2][N + 2];
pos ori;
#define X first
#define Y second
struct DisArray {
	int dis[N + 2][N + 2];
	DisArray() {
		memset(dis,0x3f,sizeof(dis));
	}
	int& operator [](pos x) {
		return dis[x.X][x.Y];
	}
} dis;
bool operator<(const pos a,const pos b) {
	return a.X<b.X||a.Y<b.Y;
}
bool operator>(const pos a,const pos b) {
	return a.X>b.X||a.Y>b.Y;
}
pos operator+(const pos a,const pos b) {
	return pos(a.X+b.X,a.Y+b.Y);
}
void bfs(pos x,pos left_top,pos right_bottom) {
	queue<pos> q;
	q.push(x),dis[x]=0;
	while(!q.empty()) {
		pos u=q.front();
		q.pop();
		for(pos w : e) {
			pos v=u+w;
			if(v<left_top||v>right_bottom||s[v.X][v.Y]=='X') continue;
			if(dis[u]+1<dis[v]) {
				dis[v]=dis[u]+1;
				q.push(v);
			}
		}
	}
	return ;
}
void solve(int k) {
	for(int i=1; i<=n&&s[i][k]!='X'; ++i)
		for(int j=n; j>=1&&s[j][k]!='X'; --j)
			ans=min(ans,dis[pos(i,k)]+dis[pos(j,k)]+j-i);
}
int main() {
	freopen("forest.in","r",stdin);
	freopen("forest.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(i=1; i<=n; ++i)
		scanf("%s",s[i]+1);
	for(i=1; i<=n; ++i)
		for(j=1; j<=m; ++j)
			if(s[i][j]=='X')
				l=min(l,j),r=max(r,j);
			else if(s[i][j]=='*')
				ori=pos(i,j);
	if(l<=ori.Y) {
		bfs(ori,pos(1,l),pos(n,m));
		solve(l);
	} else {
		bfs(ori,pos(1,1),pos(n,r));
		solve(r);
	}
	printf("%d",ans);
	return 0;
}