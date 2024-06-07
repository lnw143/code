#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#include <tuple>
#include <utility>
using namespace std;
using ll = long long;
const int N = 1e5;
int n,m,c[N + 2],fa[N + 2];
struct edge { int v,w; };
vector<edge> e[N + 2];
ll dis[N + 2];
int find(int u) {
	return fa[u]==u?u:fa[u]=find(fa[u]);
}
int main() {
	scanf("%d%d",&n,&m);
	for(int i=1; i<=n; ++i)	scanf("%d",&c[i]);
	for(int i=1; i<=m; ++i) {
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		e[u].push_back({v,w});
		e[v].push_back({u,w});
	}
	for(int i=1; i<=n; ++i)
		if(c[i]) {
			e[n+1].push_back({i,0});
			e[i].push_back({n+1,0});
		}
	for(int i=1; i<=n; ++i) dis[i]=1ll<<60;
	priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<pair<ll,int>>> hp;
	hp.push({0,n+1});
	while(!hp.empty()) {
		auto [d,u]=hp.top();
		hp.pop();
		if(dis[u]!=d) continue;
		for(auto [v,w] : e[u])
			if(d+w<dis[v]) {
				dis[v]=d+w;
				hp.push({dis[v],v});
			}
	}
	for(int i=1; i<=n; ++i)
		if(dis[i]==(1ll<<60)) {
			printf("impossible\n");
			return 0;
		}
	vector<tuple<int,int,int>> r;
	for(int i=1; i<=n+1; ++i)
		for(auto [v,w] : e[i])
			if(dis[i]+w==dis[v])
				r.push_back({w,i,v});
	sort(r.begin(),r.end());
	for(int i=1; i<=n+1; ++i) fa[i]=i;
	ll ans=0;
	for(auto [w,u,v] : r)
		if(find(u)!=find(v)) {
			fa[find(u)]=find(v);
			ans+=w;
		}
	printf("%lld",ans);
	return 0;
}