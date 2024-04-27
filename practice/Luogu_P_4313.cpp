#include<cstdio>
#include<vector>
#include<utility>
#include<cstring>
using namespace std;
constexpr int N = 1e2, M = N * N * 3 + 30, inf = 1 << 30;
int n,m,a[N + 2][N + 2],b[N + 2][N + 2],c[N + 2][N + 2],d[N + 2][N + 2],p[N + 2][N + 2],ans;
const vector<pair<int,int>> way{{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {0, 0}};
namespace netflow {
	struct edge { int v,w,id; };
	vector<edge> e[M];
	int tot,dep[M],cur[M];
	int newnode() { return ++tot; }
	int S=newnode(),T=newnode();
	void insert(int u,int v,int w) {
		int uid=e[u].size(),vid=e[v].size();
		e[u].push_back(edge{v,w,vid});
		e[v].push_back(edge{u,0,uid});
	}
	bool bfs() {
		static int que[M];
		memset(dep,-1,sizeof(dep));
		int h=0,t=1;
		que[++h]=S;
		dep[S]=0;
		while(h<=t) {
			int u=que[h];
			cur[u]=0;
			for(const auto& [v,w,id] : e[u])
				if(w&&dep[v]==-1) {
					dep[v]=dep[u]+1;
					que[++t]=v;
				}
			++h;
		}
		return dep[T]!=-1;
	}
	int dfs(int u,int flow) {
		if(u==T) return flow;
		int rem=flow;
		for(int &i=cur[u]; i<e[u].size(); ++i) {
			auto& [v,w,id]=e[u][i];
			if(dep[v]!=dep[u]+1||!w) continue;
			int r=dfs(v,min(rem,w));
			w-=r;
			e[v][id].w+=r;
			rem-=r;
			if(!rem) break;
		}
		return flow-rem;
	}
}
int main() {
	scanf("%d%d",&n,&m);
	for(auto v : {a,b,c,d})
		for(int i=1; i<=n; ++i)
			for(int j=1; j<=m; ++j)
				scanf("%d",&v[i][j]),ans+=v[i][j];
	using namespace netflow;
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j) {
			p[i][j]=newnode();
			insert(S,p[i][j],a[i][j]);
			insert(p[i][j],T,b[i][j]);
		}
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j) {
			int f=newnode(),g=newnode();
			insert(S,f,c[i][j]);
			insert(g,T,d[i][j]);
			for(auto [u,v] : way) {
				int x=u+i,y=v+j;
				if(x<1||x>n||y<1||y>m) continue;
				insert(f,p[x][y],inf);
				insert(p[x][y],g,inf);
			}
		}
	while(bfs()) ans-=dfs(S,inf);
	printf("%d",ans);
	return 0;
}