#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <utility>
using namespace std;
using ll = long long;
const int N = 1e3, inf = 0x3f3f3f3f;
const ll infl = 0x3f3f3f3f3f3f3f3fll;
int n,k,min_et,min_sp,et[N + 2],sp[N + 2];
int a[N + 2],b[N + 2],c[N + 2],f[N + 2];
ll ans;
namespace netflow {
	const int K = N * 5 + 100;
	int tot,cur[K];
	ll dis[K];
	bool vis[K];
	inline int newnode() {
		return ++tot;
	}
	const int S=newnode(),T=newnode(),P=newnode(),Q=newnode();
	struct edge {
		int v,w,c,id;
	};
	vector<edge> e[K];
	void insert(int u,int v,int w,int c) {
		int uid=e[u].size(),vid=e[v].size();
		if(w) printf("%d %d %d\n",u,v,w);
		e[u].push_back({v,w,c,vid});
		e[v].push_back({u,0,-c,uid});
	}
	bool spfa(int S,int T) {
		memset(dis,0x3f,sizeof(dis));
		queue<int> Q;
		dis[S]=0;
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
		return dis[T]<infl;
	}
	pair<int,ll> dfs(int u,int f,const int T) {
		if(u==T) return {f,0};
		int rem=f;
		ll cost=0;
		vis[u]=true;
		for(int &i=cur[u]; i<e[u].size(); ++i) {
			auto& [v,w,c,id]=e[u][i];
			if(dis[u]+c!=dis[v]||vis[v]||!w) continue;
			auto [r,p]=dfs(v,min(w,rem),T);
			rem-=r;
			w-=r;
			e[v][id].w+=r;
			cost+=p+(ll)r*c;
			if(!rem) break;
		}
		vis[u]=false;
		return {f-rem,cost};
	}
}
struct Edge {
	int u,v,l,r,c;
};
vector<Edge> egs;
int main() {
	freopen("cat.in","r",stdin);
	freopen("cat.out","w",stdout);
	scanf("%d%d%d%d",&n,&k,&min_sp,&min_et);
	for(int i=1; i<=n; ++i) scanf("%d",&sp[i]);
	for(int i=1; i<=n; ++i) scanf("%d",&et[i]);
	using namespace netflow;
	for(int i=1; i<=n; ++i) {
		a[i]=newnode(),b[i]=newnode(),c[i]=newnode();
		egs.push_back({S,a[i],1,1,0});
		egs.push_back({a[i],b[i],0,1,-sp[i]});
		egs.push_back({a[i],c[i],0,1,-et[i]});
	}
	for(int i=1; i<=n-k+1; ++i) {
		int x=newnode(),y=newnode();
		for(int j=0; j<k; ++j)
			egs.push_back({b[i+j],x,0,1,0}),
			egs.push_back({c[i+j],y,0,1,0});
		egs.push_back({x,T,min_sp,k,0});
		egs.push_back({y,T,min_et,k,0});
	}
	egs.push_back({T,S,0,inf,0});
	for(auto [u,v,l,r,c] : egs) {
		insert(u,v,r-l,c);
		f[u]-=l;
		f[v]+=l;
	}
	for(int i=1; i<=tot; ++i)
		if(i!=P&&i!=Q) {
			if(f[i]<0) insert(i,Q,-f[i],0);
			else insert(P,i,f[i],0);
		}
	while(spfa(P,Q)) ans+=dfs(P,inf,Q).second;
	printf("%lld\n",-ans);
	for(int i=1; i<=n; ++i) {
		for(auto [v,w,c,id] : e[a[i]])
			if(v==b[i])
				printf(w?"E":"S");
	}
	return 0;
}