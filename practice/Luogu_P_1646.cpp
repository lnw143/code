#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
constexpr int N = 1e2, M = 6 * N * N + 50, inf = 1e9;
int n,m,v[N + 2][N + 2],ans;
namespace netflow {
	struct edge { int v,w,id; };
	vector<edge> e[M];
	int newnode() {
		static int tot;
		return ++tot;
	}
	void insert(int u,int v,int w) {
		int uid=e[u].size(),vid=e[v].size();
		e[u].push_back(edge{v,w,vid});
		e[v].push_back(edge{u,0,uid});
	}
	const int S=newnode(),T=newnode();
	int dep[M],cur[M];
	bool bfs() {
		static int que[M];
		int h=0,t=1;
		que[1]=S;
		memset(dep,-1,sizeof(dep));
		dep[S]=0;
		while(++h<=t) {
			int u=que[h];
			cur[u]=0;
			for(auto [v,w,id] : e[u])
				if(w&&dep[v]==-1) {
					dep[v]=dep[u]+1;
					que[++t]=v;
				}
		}
		return dep[T]!=-1;
	}
	int dfs(int u,int flow) {
		if(u==T) return flow;
		int rest=flow;
		for(int &i=cur[u]; i<e[u].size(); ++i) {
			auto &[v,w,id]=e[u][i];
			if(!w||dep[v]!=dep[u]+1) continue;
			int ret=dfs(v,min(rest,w));
			rest-=ret;
			w-=ret;
			e[v][id].w+=ret;
			if(!rest) break;
		}
		return flow-rest;
	}
}
int main() {
	scanf("%d%d",&n,&m);
	using namespace netflow;
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j)
			v[i][j]=newnode();
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j) {
			int x;
			scanf("%d",&x);
			insert(S,v[i][j],x);
			ans+=x;
		}
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j) {
			int x;
			scanf("%d",&x);
			insert(v[i][j],T,x);
			ans+=x;
		}
	for(int i=1; i<n; ++i)
		for(int j=1; j<=m; ++j) {
			int x,t=newnode();
			scanf("%d",&x);
			insert(S,t,x);
			insert(t,v[i][j],inf);
			insert(t,v[i+1][j],inf);
			ans+=x;
		}
	for(int i=1; i<n; ++i)
		for(int j=1; j<=m; ++j) {
			int x,t=newnode();
			scanf("%d",&x);
			insert(t,T,x);
			insert(v[i][j],t,inf);
			insert(v[i+1][j],t,inf);
			ans+=x;
		}
	for(int i=1; i<=n; ++i)
		for(int j=1; j<m; ++j) {
			int x,t=newnode();
			scanf("%d",&x);
			insert(S,t,x);
			insert(t,v[i][j],inf);
			insert(t,v[i][j+1],inf);
			ans+=x;
		}
	for(int i=1; i<=n; ++i)
		for(int j=1; j<m; ++j) {
			int x,t=newnode();
			scanf("%d",&x);
			insert(t,T,x);
			insert(v[i][j],t,inf);
			insert(v[i][j+1],t,inf);
			ans+=x;
		}
	while(bfs()) ans-=dfs(S,inf);
	printf("%d",ans);
	return 0;
}