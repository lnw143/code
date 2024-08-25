#include <cstdio>
#include <queue>
#include <vector>
#include <utility>
using namespace std;
template<class T> using heap = priority_queue<T,vector<T>,greater<T>>;
const int N = 1e5, M = 2e5;
int n,m,p,d[N + 2],id[M + 2];
struct edge {
	int x,y,l,r;
} eg[M + 2];
vector<pair<int,int>> e[N + 2];
long long dis[N + 2];
void dij() {
	for(int i=1; i<n; ++i) dis[i]=1e18;
	dis[n]=0;
	heap<pair<long long,int>> hp;
	hp.emplace(0,n);
	while(hp.size()) {
		auto [d,u]=hp.top();
		hp.pop();
		if(d!=dis[u]) continue;
		for(auto [v,w] : e[u])
			if(d+w<dis[v]) {
				dis[v]=d+w;
				hp.emplace(dis[v],v);
			}
	}
}
bool check(int x) {
	for(int i=1; i<=m; ++i) {
		int u=eg[i].x,v=eg[i].y,w=id[i]&&id[i]<=x?eg[i].l:eg[i].r;
		e[u].emplace_back(v,w);
		e[v].emplace_back(u,w);
	}
	dij();
	bool res=true;
	int u=1;
	for(int i=1; i<=x; ++i) {
		int v=eg[d[i]].x==u?eg[d[i]].y:eg[d[i]].x;
		if(dis[u]!=dis[v]+eg[d[i]].l) {
			res=false;
			break;
		}
		u=v;
	}
	for(int i=1; i<=n; ++i) e[i].clear();
	return res;
}
int main() {
	freopen("shortcut.in","r",stdin);
	freopen("shortcut.out","w",stdout);
	int T;
	scanf("%d",&T);
	while(T--) {
		scanf("%d%d%d",&n,&m,&p);
		for(int i=1; i<=m; ++i)
			scanf("%d%d%d%d",&eg[i].x,&eg[i].y,&eg[i].l,&eg[i].r);
		for(int i=1; i<=p; ++i)
			scanf("%d",&d[i]),id[d[i]]=i;
		int ans;
		{
			int l=1,r=p;
			while(l<=r) {
				int mid=(l+r)/2;
				if(check(mid)) l=mid+1;
				else r=mid-1;
			}
			ans=l-1;
		}
		for(int i=1; i<=m; ++i) id[i]=0;
		printf("%d\n",ans);
	}
	return 0;
}