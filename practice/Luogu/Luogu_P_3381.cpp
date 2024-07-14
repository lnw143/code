#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
#include <queue>
using namespace std;
const int N = 5e3, inf = 0x3f3f3f3f;
namespace netflow {
	int dis[N + 2],cur[N + 2];
	bool vis[N + 2];
	struct edge {
		int v,w,c,id;
	};
	vector<edge> e[N + 2];
	void insert(int u,int v,int w,int c) {
		int uid=e[u].size(),vid=e[v].size();
		e[u].push_back({v,w,c,vid});
		e[v].push_back({u,0,-c,uid});
	}
	bool spfa(int S,int T) {
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
	pair<int,int> dfs(int u,int f,const int T) {
		if(u==T) return {f,0};
		vis[u]=true;
		int rem=f,cost=0;
		for(int &i=cur[u]; i<e[u].size(); ++i) {
			auto& [v,w,c,id]=e[u][i];
			if(dis[v]!=dis[u]+c||!w||vis[v]) continue;
			auto [r,p]=dfs(v,min(rem,w),T);
			w-=r;
			e[v][id].w+=r;
			rem-=r;
			cost+=r*c+p;
			if(!rem) break;
		}
		vis[u]=false;
		return {f-rem,cost};
	}
}
int n,m,s,t,ans1,ans2;
int main() {
	scanf("%d%d%d%d",&n,&m,&s,&t);
	for(int i=1; i<=m; ++i) {
		int u,v,w,c;
		scanf("%d%d%d%d",&u,&v,&w,&c);
		netflow::insert(u,v,w,c);
	}
	while(netflow::spfa(s,t)) {
		auto [f,c]=netflow::dfs(s,inf,t);
		ans1+=f,ans2+=c;
	}
	printf("%d %d",ans1,ans2);
	return 0;
}