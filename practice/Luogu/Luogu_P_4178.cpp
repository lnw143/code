#include<cstdio>
#include<vector>
#include<map>
using namespace std;
const int N(4e4), W(1e3);
int n,k,ans;
map<int,int> e[N + 2];
namespace treeDivide {
	namespace fenwick {
		const int S(N * W);
		int tr[S + 2];
		void add(int x,int f) {
			while(x<=S) {
				tr[x]+=f;
				x+=x&(-x);
			}
			return ;
		}
		int query(int x) {
			int r=0;
			while(x) {
				r+=tr[x];
				x&=x-1;
			}
			return r;
		}
	}
	int siz,cent,minn;
	bool bz[N + 2];
	vector<int> z;
	int dfs(int u) {
		bz[u]=true;
		int sz=1;
		for(auto [v,w] : e[u]) 
			if(!bz[v])
				sz+=dfs(v);
		bz[u]=false;
		return sz;
	}
	int dfs2(int u) {
		bz[u]=true;
		int sz=1,maxn=0;
		for(auto [v,w] : e[u])
			if(!bz[v]) {
				int s=dfs2(v);
				maxn=max(maxn,s);
				sz+=s;
			}
		maxn=max(maxn,siz-sz);
		if(maxn<minn) minn=maxn,cent=u;
		bz[u]=false;
		return sz;
	}
	void cnt(int u,int dep) {
		if(dep>k) return ;
		bz[u]=true;
		z.push_back(dep);
		ans+=fenwick::query(k-dep)+1;
		for(auto [v,w] : e[u])
			if(!bz[v])
				cnt(v,dep+w);
		bz[u]=false;
	}
	void findCent(int u) {
		siz=dfs(u);
		minn=1e9;
		cent=u;
		dfs2(u);
	}
	void solve(int u) {
		findCent(u);
		u=cent;
		z.clear();
		int i=0;
		bz[u]=true;
		for(auto [v,w] : e[u])
			if(!bz[v]) {
				cnt(v,w);
				while(i<z.size()) fenwick::add(z[i++],1);
			}
		for(int x : z)
			fenwick::add(x,-1);
		for(auto [v,w] : e[u])
			if(!bz[v])
				solve(v);
	}
}
int main() {
	scanf("%d",&n);
	for(int i=1; i<n; ++i) {
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		e[u][v]=e[v][u]=w;
	}
	scanf("%d",&k);
	treeDivide::solve(1);
	printf("%d",ans);
	return 0;
}