#include<cstdio>
#include<vector>
#include<cstring>
using namespace std;
constexpr int N = 1e4, M = 2e3, inf = 1 << 30;
int n,m,g,a[N + 2],v[N + 2],p[N + 2],ans;
namespace netflow {
	int tot;
	int newnode() { return ++tot; }
	struct edge { int v,w,id; };
	constexpr int S_ = 2 * N + M + 30;
	int S=newnode(),T=newnode(),dep[S_],cur[S_];
	vector<edge> e[S_];
	void insert(int u,int v,int w) {
		int uid=e[u].size(),vid=e[v].size();
		e[u].push_back(edge{v,w,vid});
		e[v].push_back(edge{u,0,uid});
	}
	bool bfs() {
		static int que[S_];
		int h=1,t=1;
		memset(dep,-1,sizeof(dep));
		que[1]=S;
		dep[S]=0;
		while(h<=t) {
			int u=que[h];
			cur[u]=0;
			for(auto [v,w,id] : e[u])
				if(dep[v]==-1&&w) {
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
			if(!w||dep[v]!=dep[u]+1) continue;
			int r=dfs(v,min(rem,w));
			w-=r;
			rem-=r;
			e[v][id].w+=r;
			if(!rem) break;
		}
		return flow-rem;
	}
}
int main() {
	scanf("%d%d%d",&n,&m,&g);
	for(int i=1; i<=n; ++i)	
		scanf("%d",&a[i]);
	using namespace netflow;
	for(int i=1; i<=n; ++i)	{
		scanf("%d",&v[i]);
		p[i]=newnode();
		a[i]?insert(p[i],T,v[i]):insert(S,p[i],v[i]);
	}
	for(int i=1; i<=m; ++i) {
		int x,w,k,fr,t=newnode();
		scanf("%d%d%d",&x,&w,&k);
		ans+=w;
		for(int i=1; i<=k; ++i) {
			int u;
			scanf("%d",&u);
			x?insert(p[u],t,inf):insert(t,p[u],inf);
		}
		scanf("%d",&fr);
		if(fr) w+=g;
		x?insert(t,T,w):insert(S,t,w);
	}
	while(bfs()) ans-=dfs(S,inf);
	printf("%d",ans);
	return 0;
}