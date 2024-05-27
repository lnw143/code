#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
const int N = 1e5, M = 2e5, K = 50;
int T,n,m,k,p,i,f[N + 2][K + 2];
bool vis[N + 2][K + 2];
struct Node {
	int x,d;
	bool operator<(const Node t) const {
		return d>t.d;
	}
};
struct Graph {
	int em,e[M + 2],ls[N + 2],nx[M + 2],cs[M + 2],dis[N + 2];
	void insert(int x,int y,int z) {
		e[++em]=y;
		nx[em]=ls[x];
		cs[em]=z;
		ls[x]=em;
	}
	void dij(int s) {
		priority_queue<Node> q;
		memset(dis,0x3f,sizeof(dis));
		dis[s]=0;
		q.push({s,0});
		for(int i=1; i<n&&!q.empty(); ++i) {
			Node u=q.top();
			q.pop();
			while(!q.empty()&&dis[u.x]!=u.d) u=q.top(),q.pop();
			if(dis[u.x]!=u.d) break;
			for(int j=ls[u.x]; j; j=nx[j])
				if(u.d+cs[j]<dis[e[j]]) {
					dis[e[j]]=u.d+cs[j];
					q.push({e[j],dis[e[j]]});
				}
		}
	}
} G,G_;
int *e=G_.e,*ls=G_.ls,*nx=G_.nx,*cs=G_.cs,*dis=G_.dis;
#define ad(x,y) (x+=y)%=p
int dfs(int x,int y) {
	if(y<0||y>k) return 0;
	if(vis[x][y]) return -1;
	if(~f[x][y]) return f[x][y];
	vis[x][y]=true;
	f[x][y]=x==1;
	for(int i=ls[x]; i; i=nx[i]) {
		int r=dfs(e[i],y+dis[x]+cs[i]-dis[e[i]]);
		if(r==-1) return -1;
		ad(f[x][y],r);
	}
	vis[x][y]=false;
	return f[x][y];
}
int main() {
	freopen("park.in","r",stdin);
	freopen("park.out","w",stdout);
	scanf("%d",&T);
	while(T--) {
		scanf("%d%d%d%d",&n,&m,&k,&p);
		memset(f,-1,sizeof(f));
		memset(vis,0,sizeof(vis));
		for(i=1; i<=n; ++i)
			G.ls[i]=G_.ls[i]=0;
		G.em=G_.em=0;
		for(i=1; i<=m; ++i) {
			int u,v,w;
			scanf("%d%d%d",&u,&v,&w);
			G.insert(u,v,w);
			G_.insert(v,u,w);
		}
		G.dij(1);
		G_.dij(n);
		printf("%d\n",dfs(n,0));
	}
	return 0;
}