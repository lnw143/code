#include<cstdio>
#include<utility>
#include<cstring>
#include<queue>
using namespace std;
const int N = 60;
const int way[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
int n,i,j,l,dis[N + 2][N + 2][N + 2][N + 2],t;
char s[N + 2][N + 2];
struct Pos {
	int x,y;
	Pos move(int a,int b) {
		return Pos(x+a,y+b).check()?Pos(x+a,y+b):(*this);
	}
	bool check() {
		return 1<=x&&x<=n&&1<=y&&y<=n&&s[x][y]!='#';
	}
	Pos(int x_=0,int y_=0):x(x_),y(y_) {}
} p[2];
using ppp = pair<Pos,Pos>;
int bfs(Pos s,Pos s2) {
	memset(dis,0x3f,sizeof(dis));
	queue<ppp> q;
	q.push(ppp(s,s2));
	dis[s.x][s.y][s2.x][s2.y]=0;
	while(!q.empty()) {
		Pos x=q.front().first,y=q.front().second;
		q.pop();
		if(x.x==y.x&&x.y==y.y) return dis[x.x][x.y][y.x][y.y];
		for(int i=0; i<4; ++i) {
			Pos xx=x.move(way[i][0],way[i][1]),yy=y.move(way[i][0],way[i][1]);
			if(dis[x.x][x.y][y.x][y.y]+1<dis[xx.x][xx.y][yy.x][yy.y])
				dis[xx.x][xx.y][yy.x][yy.y]=dis[x.x][x.y][y.x][y.y]+1,
				                            q.push(ppp(xx,yy));
		}
	}
	return -1;
}
int main() {
	scanf("%d",&n);
	for(i=1; i<=n; ++i)
		for(j=1; j<=n; ++j) {
			scanf(" %c",&s[i][j]);
			if(s[i][j]=='P') p[l++]=Pos(i,j);
		}
	printf("%d",bfs(p[0],p[1]));
	return 0;
}