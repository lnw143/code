#include<cstdio>
#include<vector>
#include<cstring>
using namespace std;
const int N = 1e4, M = 1e2, K = 1e7;
int n,m,k[M + 2],i;
bool ans[M + 2];
namespace Graph {
	int em,e[N * 2],ls[N + 2],nx[N * 2],cs[N * 2],sumsz;
	int cent,minn;
	bool bz[N + 2],w[K + 2];
	void insert(int x,int y,int z) {
		e[++em]=y;
		nx[em]=ls[x];
		cs[em]=z;
		ls[x]=em;
	}
	int get_sz(int x,int fa) {
		if(bz[x]) return 0;
		int sz=1;
		for(int i=ls[x]; i; i=nx[i])
			if(e[i]!=fa)
				sz+=get_sz(e[i],x);
		return sz;
	}
	int find_cent(int x,int fa) {
		if(bz[x]) return 0;
		int sz=1,maxs=0;
		for(int i=ls[x]; i; i=nx[i])
			if(e[i]!=fa) {
				int r=find_cent(e[i],x);
				maxs=max(maxs,r);
				sz+=r;
			}
		maxs=max(maxs,sumsz-sz);
		if(maxs<minn) {
			minn=maxs;
			cent=x;
		}
		return sz;
	}
	vector<int> t;
	void dfs(int x,int fa,int dep) {
		if(dep>K||bz[x]) return ;
		for(int i=1; i<=m; ++i)
			if(dep<=k[i]&&w[k[i]-dep])
				ans[i]=true;
		t.push_back(dep);
		for(int i=ls[x]; i; i=nx[i])
			if(e[i]!=fa)
				dfs(e[i],x,dep+cs[i]);
	}
	void solve(int x) {
		t.clear();
		int las=0;
		w[0]=true;
		for(int i=ls[x]; i; i=nx[i]) {
			dfs(e[i],x,cs[i]);
			while(las<t.size())
				w[t[las++]]=true;
		}
		for(int y : t)
			w[y]=false;
	}
	void work() {
		bool flag=true;
		while(flag) {
			flag=false;
			for(int i=1; i<=n; ++i)
				if(!bz[i]) {
					sumsz=get_sz(i,-1);
					minn=1e9;
					find_cent(i,-1);
					solve(cent);
					bz[cent]=flag=true;
				}
		}
	}
}
int main() {
	scanf("%d%d",&n,&m);
	for(i=1; i<n; ++i) {
		static int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		Graph::insert(u,v,w);
		Graph::insert(v,u,w);
	}
	for(i=1; i<=m; ++i)
		scanf("%d",&k[i]);
	Graph::work();
	for(i=1; i<=m; ++i)
		printf(ans[i]?"AYE\n":"NAY\n");
	return 0;
}