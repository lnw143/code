#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
const int N = 3e3;
int n,dep[N + 2],p[N + 2],fa[N + 2];
int qdis(int u,int v) {
	printf("? %d %d\n",u,v);
	fflush(stdout);
	int d;
	scanf("%d",&d);
	return d;
}
namespace treecut {
	int siz[N + 2],wson[N + 2];
	int dfc,dfn[N + 2],low[N + 2],pos[N + 2];
	vector<int> e[N + 2];
	void dfs(int u,int p) {
		siz[u]=1;
		wson[u]=0;
		for(auto v : e[u])
			if(v!=p) {
				dfs(v,u);
				siz[u]+=siz[v];
				if(siz[v]>siz[wson[u]]) wson[u]=v;
			}
	}
	int dfs2(int u,int p) {
		pos[dfn[u]=++dfc]=u;
		if(wson[u]) low[u]=dfs2(wson[u],u);
		else low[u]=dfn[u];
		for(auto v : e[u])
			if(v!=wson[u]&&v!=p)	
				dfs2(v,u);
		return low[u];
	}
	int find(int u,int x) {
		int las=pos[low[u]],dis=qdis(las,x),depl=(dep[las]+dep[x]-dis)/2,lca=pos[low[u]-(dep[las]-depl)];
		if(lca==las) return lca;
		return find(e[lca][wson[lca]==e[lca][0]],x);
	}
}
int main() {
	scanf("%d",&n);
	for(int i=2; i<=n; ++i)
		dep[i]=qdis(1,i),p[i]=i;
	sort(p+2,p+n+1,[](int x,int y) { return dep[x]<dep[y]; });
	treecut::dfs(1,1);
	treecut::dfs2(1,1);
	for(int i=2; i<=n; ++i) {
		fa[p[i]]=treecut::find(1,p[i]);
		treecut::e[fa[p[i]]].push_back(p[i]);
		if(i<n&&dep[p[i]]!=dep[p[i+1]]) {
			treecut::dfc=0;
			treecut::dfs(1,1);
			treecut::dfs2(1,1);
		}
	}
	printf("!");
	for(int i=2; i<=n; ++i)
		printf(" %d",fa[i]);
	printf("\n");
	fflush(stdout);
	return 0;
}