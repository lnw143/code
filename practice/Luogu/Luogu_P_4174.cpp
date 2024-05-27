#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
constexpr int N = 5e3, M = 5e4, K = N + M + 30, inf = 1 << 30;
int n,m,p[N + 2],d[N + 2],ans;
namespace netflow {
	int tot;
	int newnode() { return ++tot; }
	struct edge { int v,w,id; };
	vector<edge> e[K];
	void insert(int u,int v,int w) {
		int uid=e[u].size(),vid=e[v].size();
		e[u].push_back(edge{v,w,vid});
		e[v].push_back(edge{u,0,uid});
	}
	int S=newnode(),T=newnode(),dep[K],cur[K];
	bool bfs() {
		static int q[K];
		int h=1,t=1;
		q[1]=S;
		memset(dep,-1,sizeof(dep));
		dep[S]=0;
		while(h<=t) {
			int u=q[h];
			cur[u]=0;
			for(auto [v,w,id] : e[u])
				if(w&&dep[v]==-1) {
					dep[v]=dep[u]+1;
					q[++t]=v;
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
	scanf("%d%d",&n,&m);
	using namespace netflow;
	for(int i=1; i<=n; ++i) {
		scanf("%d",&p[i]);
		d[i]=newnode();
		insert(S,d[i],p[i]);
	}
	for(int i=1; i<=m; ++i) {
		int a,b,c,t=newnode();
		scanf("%d%d%d",&a,&b,&c);
		ans+=c;
		insert(d[a],t,inf);
		insert(d[b],t,inf);
		insert(t,T,c);
	}
	while(bfs()) ans-=dfs(S,inf);
	printf("%d",ans);
	return 0;
}