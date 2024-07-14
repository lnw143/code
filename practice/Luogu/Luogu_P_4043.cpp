#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <utility>
using namespace std;
const int N = 3e2, inf = 0x3f3f3f3f;
int n,f[N + 2],ans;
struct Edge {
	int u,v,l,r,c;
};
vector<Edge> egs;
namespace netflow {
	const int K = N + 50;
	int S=N+1,T=N+2,dis[K],cur[K];
	bool vis[K];
	struct edge {
		int v,w,c,id;
	};
	vector<edge> e[K];
	void insert(int u,int v,int w,int c) {
		int uid=e[u].size(),vid=e[v].size();
		e[u].push_back({v,w,c,vid});
		e[v].push_back({u,0,-c,uid});
	}
	bool spfa() {
		memset(dis,0x3f,sizeof(dis));
		dis[S]=0;
		queue<int> Q;
		Q.push(S);
		while(Q.size()) {
			int u=Q.front();
			Q.pop();
			cur[u]=0;
			for(auto [v,w,c,id] : e[u])
				if(w&&dis[u]+c<dis[v]) {
					dis[v]=dis[u]+c;
					Q.push(v);
				}
		}
		return dis[T]<inf;
	}
	pair<int,int> dfs(int u,int f) {
		if(u==T) return {f,0};
		int rem=f,cost=0;
		vis[u]=true;
		for(int &i=cur[u]; i<e[u].size(); ++i) {
			auto& [v,w,c,id]=e[u][i];
			if(!w||dis[v]!=dis[u]+c||vis[v]) continue;
			auto [r,p]=dfs(v,min(w,rem));
			rem-=r;
			w-=r;
			e[v][id].w+=r;
			cost+=p+r*c;
			if(!rem) break;
		}
		vis[u]=false;
		return {f-rem,cost};
	}
}
int main() {
	scanf("%d",&n);
	for(int i=1; i<=n; ++i) {
		int k;
		scanf("%d",&k);
		for(int j=1; j<=k; ++j) {
			int v,c;
			scanf("%d%d",&v,&c);
			egs.push_back({i,v,1,inf,c});
		}
		if(i>1) egs.push_back({i,1,0,inf,0});
	}
	using namespace netflow;
	for(auto [u,v,l,r,c] : egs) {
		f[u]-=l,f[v]+=l;
		insert(u,v,r-l,c);
		ans+=l*c;
	}
	for(int i=1; i<=n; ++i)
		if(f[i]<0)
			insert(i,T,-f[i],0);
		else 
			insert(S,i,f[i],0);
	while(spfa()) ans+=dfs(S,inf).second;
	printf("%d",ans);
	return 0;
}