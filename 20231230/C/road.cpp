#include<cstdio>
#include<queue>
using namespace std;
const int N = 1e4 + 2, M = 2e5 + 2;
int n,m,i,j,u,v,dis[N];
bool vis[N],bz[N];
struct Graph {
	int em,e[M],ls[N],nx[M];
	void insert(int x,int y) {
		e[++em]=y;
		nx[em]=ls[x];
		ls[x]=em;
	}
} G,G_;
void bfs(Graph G,int s) {
	queue<int> q;
	q.push(s);
	vis[s]=true;
	while(!q.empty()) {
		int u=q.front();
		q.pop();
		for(int i=G.ls[u]; i; i=G.nx[i])
			if(!vis[G.e[i]]) {
				vis[G.e[i]]=true;
				q.push(G.e[i]);
			}
	}
}
void bfs2(Graph G,int s) {
	queue<int> q;
	for(int i=1; i<=n; ++i)
		dis[i]=-1;
	q.push(s);
	dis[s]=0;
	while(!q.empty()) {
		int u=q.front();
		q.pop();
		for(int i=G.ls[u]; i; i=G.nx[i])
			if(bz[G.e[i]]&&dis[G.e[i]]==-1) {
				dis[G.e[i]]=dis[u]+1;
				q.push(G.e[i]);
			}
	}
}
int main() {
	scanf("%d%d",&n,&m);
	for(i=1; i<=m; ++i) {
		scanf("%d%d",&u,&v);
		G.insert(u,v);
		G_.insert(v,u);
	}
	scanf("%d%d",&u,&v);
	bfs(G_,v);
	for(i=1; i<=n; ++i)
		if(vis[i]) {
			bz[i]=true;
			for(j=G.ls[i]; j; j=G.nx[j])
				if(!vis[G.e[j]]) {
					bz[i]=false;
					break;
				}
		}
	bfs2(G,u);
	printf("%d",dis[v]);
	return 0;
}