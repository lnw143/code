#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
using ll = long long;
const int N = 1e5;
int n,c[N + 2];
vector<int> e[N + 2];
ll ans[N + 2];
namespace divide {
	bool visited[N + 2];
	namespace locCent { // locate the cent
		int res,sz[N + 2],total,minn;
		void dfs(int u,int p) {
			sz[u]=1;
			for(auto v : e[u])
				if(v!=p&&!visited[v]) {
					dfs(v,u);
					sz[u]+=sz[v];
				}
		}
		void find(int u,int p) {
			int maxs=total-sz[u];
			for(auto v : e[u])
				if(v!=p&&!visited[v]) {
					find(v,u);
					maxs=max(maxs,sz[v]);
				}
			if(maxs<minn) {
				minn=maxs;
				res=u;
			}
		}
		int work(int u) {
			dfs(u,-1);
			minn=1e9;
			res=-1;
			total=sz[u];
			find(u,-1);
			return res;
		}
	}
	ll sum;
	int bz[N + 2],siz[N + 2],cnt[N + 2];
	void add(int col,ll num) {
		cnt[col]+=num;
		sum+=num;
	}
	void dfs(int u,int p) {
		siz[u]=1;
		for(auto v : e[u]) 
			if(v!=p&&!visited[v]) {
				dfs(v,u);
				siz[u]+=siz[v];
			}
	}
	void calc(int u,int p,int s) {
		++bz[c[u]];
		for(auto v : e[u])
			if(v!=p&&!visited[v])
				calc(v,u,s);
		--bz[c[u]];
		if(!bz[c[u]]) add(c[u],s*siz[u]);
	}
	void count(int u,int p,int oth) {
		int t=oth-cnt[c[u]];
		add(c[u],t);
		ans[u]+=sum;
		for(auto v : e[u]) 
			if(v!=p&&!visited[v])
				count(v,u,oth);
		add(c[u],-t);
	}
	void solve(int u) {
		u=locCent::work(u);
		dfs(u,-1);
		calc(u,-1,1);
		ans[u]+=sum;
		for(auto v : e[u])
			if(!visited[v]) {
				calc(v,u,-1);
				add(c[u],siz[u]-siz[v]-cnt[c[u]]);
				count(v,u,siz[u]-siz[v]);
				calc(v,u,1);
			}
		calc(u,-1,-1);
		add(c[u],-cnt[c[u]]);
		visited[u]=true;
		for(auto v : e[u])
			if(!visited[v])
				solve(v);
	}
}
int main() {
	scanf("%d",&n);
	for(int i=1; i<=n; ++i) scanf("%d",&c[i]);
	for(int i=1; i<n; ++i) {
		int x,y;
		scanf("%d%d",&x,&y);
		e[x].push_back(y);
		e[y].push_back(x);
	}
	divide::solve(1);
	for(int i=1; i<=n; ++i)
		printf("%lld\n",ans[i]);
	return 0;
}