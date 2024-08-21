#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#include <utility>
#include <chrono>
#include <functional>
#include <ext/random>
#include <cmath>
using namespace std;
#define debug(format,args...) fprintf(stderr,format,##args)
const int N = 1e3, M = 1e5, K = 1;
using ll = long long;
int n,m,deg[N + 2],to[N + 2];
vector<pair<int,int>> e[N + 2];
ll tot;
struct shortest_path {
	int dis[N + 2],pre[N + 2];
	shortest_path()=default;
	shortest_path(int s) {
		priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> hp;
		for(int i=1; i<=n; ++i) dis[i]=1e9;
		dis[s]=pre[s]=0;
		hp.emplace(0,s);
		for(int i=1; i<n&&hp.size(); ) {
			auto [d,u]=hp.top();
			hp.pop();
			if(d!=dis[u]) continue;
			++i;
			for(auto [v,w] : e[u])
				if(d+w<dis[v]) {
					dis[v]=d+w;
					pre[v]=u;
					hp.emplace(d+w,v);
				}
		}
	}
} f[N + 2];
inline int dis(int x,int y) {
	return f[x].dis[y];
}
vector<int> p;
__gnu_cxx::sfmt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
inline int randint(int l,int r) {
	return uniform_int_distribution<int>(l,r)(rnd);
}
inline long double randpr() {
	return uniform_real_distribution<long double>(0,1)(rnd);
}
struct solution {
	ll sum;
	vector<pair<int,int>> x;
	void random() {
		if(x.size()<2) return ;
		int u=randint(0,x.size()-1),v=randint(0,x.size()-1);
		while(u==v) u=randint(0,x.size()-1),v=randint(0,x.size()-1);
		int &i=randint(0,1)?x[u].first:x[u].second,
			&j=randint(0,1)?x[v].first:x[v].second;
		sum-=dis(x[u].first,x[u].second)+dis(x[v].first,x[v].second);
		swap(i,j);
		sum+=dis(x[u].first,x[u].second)+dis(x[v].first,x[v].second);
	}
	solution():sum(0) {
		for(int i=0; i<p.size(); i+=2)
			x.emplace_back(p[i],p[i+1]),
			sum+=dis(p[i],p[i+1]);
	}
} ans;
void solve() {
	shuffle(p.begin(),p.end(),rnd);
	solution x;
	if(x.sum<ans.sum) ans=x;
	int cnt=0;
	for(long double temp=1e13l; temp>1e-14l; temp*=0.999999999l) {
		solution y=x;
		y.random();
		if(y.sum<x.sum||randpr()<expl((x.sum-y.sum)/temp)) x=y;
		if(x.sum<ans.sum) ans=x;
		if(++cnt==1e9) {
			cnt=0;
			debug("Current Temp: %.18Lf\n",temp);
		}
	}
}
namespace euler {
	bool vis[N + 2][N + 2],bz[N + 2];
	vector<int> stk;
	void print_path(int u,int v) {
		for(int i=f[v].pre[u]; i!=v; i=f[v].pre[i])
			stk.push_back(i);
	}
	void dfs(int u) {
		for(auto [v,w] : e[u])
			if(!vis[u][v]) {
				vis[u][v]=vis[v][u]=true;
				dfs(v);
			}
		if(to[u]&&!bz[u]) {
			bz[u]=bz[to[u]]=true;
			dfs(to[u]);
			print_path(to[u],u);
		}
		stk.push_back(u);
	}
	void output() {
		reverse(stk.begin(),stk.end());
		for(auto i : stk)
			printf("%d ",i);
	}
}
int main() {
	// freopen("postman7.in","r",stdin);
	// freopen("postman7.test","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1; i<=m; ++i) {
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		e[u].emplace_back(v,w);
		e[v].emplace_back(u,w);
		tot+=w;
	}
	for(int i=1; i<=n; ++i)
		f[i]=shortest_path(i);
	debug("dijkstra finished\n");
	for(int i=1; i<=n; ++i)
		if(e[i].size()&1)
			p.push_back(i);
	debug("Key Node: %d\n",p.size());
	debug("Begin.\n");
	ans.sum=1e18;
	for(int i=1; i<=K; ++i) {
		debug("Testing %d\n",i);
		solve();
	}
	debug("Finished.\nAnswer: %lld\n",ans.sum+tot);
	for(auto [u,v] : ans.x)
		to[u]=v,
		to[v]=u;
	euler::dfs(1);
	euler::output();
	return 0;
}