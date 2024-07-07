#include <cstdio>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
#include <random>
#include <chrono>
#include <functional>
using namespace std;
using ll = long long;
const int N = 1e5;
int n,fa[N + 2];
vector<int> e[N + 2];
bool bz[N + 2];
void dfs(int u) {
	for(auto v : e[u])
		if(v!=fa[u]) {
			fa[v]=u;
			dfs(v);
		}
}
struct node {
	ll f,g;
	pair<ll,ll> pp() const {
		return make_pair(g,f);
	}
} p[N + 2];
bool operator<(const node &x,const node &y) {
	if((x.f>=0)!=(y.f>=0)) return x.f>=0;
	return x.f>=0?x.pp()>y.pp():x.g-x.f<y.g-y.f;
}
node operator-(const node &x,const node &y) {
	return {x.f+y.f,min(x.g,x.f+y.g)};
}
bool operator!=(const node &x,const node &y) {
	return x.f!=y.f||x.g!=y.g;
}
namespace dsu {
	int par[N + 2];
	void init() {
		for(int i=1; i<=n; ++i) par[i]=i;
	}
	int find(int u) {
		return par[u]==u?u:par[u]=find(par[u]);
	}
	void merge(int u,int v) {
		par[find(u)]=find(v);
	}
}
int main() {
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	scanf("%d",&n);
	for(int i=2; i<=n; ++i) {
		int a,b;
		scanf("%d%d",&a,&b),
		p[i].f=b-a;
		p[i].g=-a;
	}
	for(int i=1; i<n; ++i) {
		int x,y;
		scanf("%d%d",&x,&y);
		e[x].push_back(y);
		e[y].push_back(x);
	}
	dfs(1);
	dsu::init();
	priority_queue<pair<node,int>,vector<pair<node,int>>,greater<pair<node,int>>> hp;
	for(int i=2; i<=n; ++i) hp.emplace(p[i],i);
	while(!hp.empty()) {
		auto [v,u]=hp.top();
		hp.pop();
		if(bz[u]||p[u]!=v) continue;
		bz[u]=true;
		int f=dsu::find(fa[u]);
		p[f]=p[f]-v;
		dsu::merge(u,f);
		if(f!=1) hp.emplace(p[f],f);
	}
	printf("%lld",-p[1].g);
	return 0;
}