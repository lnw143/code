#include <bits/stdc++.h>

#include "testlib.h"
using namespace std;
#define pb push_back
#define mp make_pair
typedef pair<int,int> pii;
typedef vector<int> vi;
#define fi first
#define se second
#define fe first
int n,m,vc,dis[55][55],vis[55][55];
char u[55][55];
int dx[]= {-1,1,0,0},dy[]= {0,0,-1,1};
int bfs(int x,int y) {
	static pii qs[55*55*2];
	int h=55*55,t=h;
	qs[t++]=pii(x,y);
	dis[x][y]=0;
	int mx=0;
	while(h^t) {
		pii s=qs[h++];
		mx=max(mx,dis[s.fi][s.se]);
		if(vis[s.fi][s.se]==vc) continue;
		vis[s.fi][s.se]=vc;
		int p=u[s.fi][s.se];
		for(int k=0; k<4; ++k) {
			pii g(s.fi+dx[k],s.se+dy[k]);
			int q=u[g.fi][g.se];
			if(q!='0'&&q!='1') continue;
			if(q==p) {
				if(dis[g.fi][g.se]>dis[s.fi][s.se]) {
					dis[g.fi][g.se]=dis[s.fi][s.se];
					qs[--h]=g;
				}
			} else {
				if(dis[g.fi][g.se]>dis[s.fi][s.se]+1) {
					dis[g.fi][g.se]=dis[s.fi][s.se]+1;
					qs[t++]=g;
				}
			}
		}
	}
	return mx;
}
int cc[99][99],cnt;
void dfs(int x,int y) {
	cc[x][y]=cnt;
	for(int k=0; k<4; ++k) {
		int X=x+dx[k],Y=y+dy[k];
		if(u[X][Y]==u[x][y]&&cc[X][Y]!=cnt) dfs(X,Y);
	}
}
int main(int argc,char**argv) {
	registerTestlibCmd(argc,argv);
	int n=inf.readInt(),m=inf.readInt();
	for(int i=1; i<=n; ++i) {
		string w=inf.readToken();
		strcpy(u[i]+1,w.c_str());
	}
	int g=ans.readInt(0,1e9),h=ouf.readInt(0,1e9);
	if(h>g) quitf(_wa,"worse than std!");
	for(int o=0; o<h; ++o) {
		int x=ouf.readInt(1,n),y=ouf.readInt(1,m);
		if(u[x][y]=='x') quitf(_wa,"operated on x");
		++cnt;
		dfs(x,y);
		for(int i=1; i<=n; ++i)for(int j=1; j<=m; ++j)if(cc[i][j]==cnt) u[i][j]^=1;
	}
	while(!ouf.seekEof()) ouf.readToken();
	set<int> s;
	for(int i=1; i<=n; ++i)for(int j=1; j<=m; ++j) if(u[i][j]!='x')s.insert(u[i][j]);
	if(s.size()!=1) quitf(_wa,"not single-colored after operations!");
	if(h<g) quitf(_fail,"std is not optimal!");
	quitf(_ok,"gg");
}

